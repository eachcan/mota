import * as path from 'path';
import { workspace, ExtensionContext, languages, Position, Location, Uri, TextDocument, CancellationToken, ProviderResult, window, OutputChannel } from 'vscode';

import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind
} from 'vscode-languageclient/node';

let client: LanguageClient;
let outputChannel: OutputChannel;

// MOTA模板定义跳转提供器
class MotaTemplateDefinitionProvider {
  
  provideDefinition(
    document: TextDocument, 
    position: Position, 
    token: CancellationToken
  ): ProviderResult<Location | Location[]> {
    
    const line = document.lineAt(position).text;
    const wordRange = document.getWordRangeAtPosition(position);
    
    if (!wordRange) {
      return null;
    }
    
    const word = document.getText(wordRange);
    
    // 检查是否在<%call xxx%>标签中
    const callMatch = line.match(/<%\s*call\s+(\w+)\s*%>/);
    if (callMatch && callMatch[1] === word) {
      const functionName = callMatch[1];
      outputChannel.appendLine(`[模板跳转] 查找函数定义: ${functionName}`);
      return this.findMiscDefinition(document, functionName);
    }
    
    return null;
  }
  
  private async findMiscDefinition(document: TextDocument, functionName: string): Promise<Location[]> {
    const text = document.getText();
    const lines = text.split('\n');
    const locations: Location[] = [];
    
    // 搜索<%misc functionName%>定义
    const miscRegex = new RegExp(`<%\\s*misc\\s+${functionName}\\s*%>`, 'g');
    
    for (let i = 0; i < lines.length; i++) {
      const line = lines[i];
      const match = miscRegex.exec(line);
      if (match) {
        const location = new Location(document.uri, new Position(i, match.index + match[0].indexOf(functionName)));
        locations.push(location);
        miscRegex.lastIndex = 0; // 重置正则表达式状态
      }
    }
    
    // 如果当前文档没找到，搜索工作区内的其他.template文件
    if (locations.length === 0) {
      outputChannel.appendLine(`[模板跳转] 在当前文档未找到 ${functionName}，搜索工作区...`);
      const workspaceLocations = await this.findMiscDefinitionInWorkspace(functionName);
      locations.push(...workspaceLocations);
    }
    
    outputChannel.appendLine(`[模板跳转] 找到 ${locations.length} 个定义位置`);
    return locations;
  }
  
  private async findMiscDefinitionInWorkspace(functionName: string): Promise<Location[]> {
    const locations: Location[] = [];
    
    // 搜索工作区内的所有.template文件
    const files = await workspace.findFiles('**/*.template', '**/node_modules/**');
    
    for (const file of files) {
      try {
        const document = await workspace.openTextDocument(file);
        const text = document.getText();
        const lines = text.split('\n');
        
        const miscRegex = new RegExp(`<%\\s*misc\\s+${functionName}\\s*%>`, 'g');
        
        for (let i = 0; i < lines.length; i++) {
          const line = lines[i];
          const match = miscRegex.exec(line);
          if (match) {
            const location = new Location(file, new Position(i, match.index + match[0].indexOf(functionName)));
            locations.push(location);
            miscRegex.lastIndex = 0;
          }
        }
      } catch (error) {
        outputChannel.appendLine(`[模板跳转] 读取文件出错 ${file.fsPath}: ${error}`);
      }
    }
    
    return locations;
  }
}

export function activate(context: ExtensionContext) {
  console.log('Mota 插件正在激活...');
  
  // 创建输出通道
  outputChannel = window.createOutputChannel('Mota');
  context.subscriptions.push(outputChannel);
  
  // 立即显示输出通道并写入初始信息
  outputChannel.show(true);
  outputChannel.appendLine('=== Mota 语言插件已激活 ===');
  outputChannel.appendLine(`时间: ${new Date().toLocaleString()}`);
  outputChannel.appendLine(`VSCode版本: ${window.activeTextEditor?.document.version || 'unknown'}`);
  outputChannel.appendLine('正在初始化语言服务...');
  
  console.log('输出通道已创建');
  
  // 注册MOTA模板的定义提供器
  const templateDefinitionProvider = languages.registerDefinitionProvider(
    { scheme: 'file', language: 'mota-template' },
    new MotaTemplateDefinitionProvider()
  );
  
  context.subscriptions.push(templateDefinitionProvider);
  outputChannel.appendLine('模板定义提供器已注册');
  
  // 服务器模块的路径
  const serverModule = context.asAbsolutePath(
    path.join('server', 'out', 'server.js')
  );
  
  outputChannel.appendLine(`服务器模块路径: ${serverModule}`);
  
  // 服务器的调试选项
  const debugOptions = { execArgv: ['--nolazy', '--inspect=6009'] };

  // 服务器选项
  const serverOptions: ServerOptions = {
    run: { module: serverModule, transport: TransportKind.ipc },
    debug: {
      module: serverModule,
      transport: TransportKind.ipc,
      options: debugOptions
    }
  };

  // 客户端选项
  const clientOptions: LanguageClientOptions = {
    // 注册 Mota 语言的服务器
    documentSelector: [
      { scheme: 'file', language: 'mota' },
      { scheme: 'file', language: 'mota-template' }
    ],
    synchronize: {
      // 监听配置变化
      configurationSection: 'motaLanguageServer',
      // 监听工作区文件变化
      fileEvents: workspace.createFileSystemWatcher('**/*.{mota,template}')
    },
    // 将服务端日志重定向到输出通道
    outputChannel: outputChannel
  };

  outputChannel.appendLine('客户端配置完成');

  // 创建语言客户端并启动
  client = new LanguageClient(
    'motaLanguageServer',
    'Mota Language Server',
    serverOptions,
    clientOptions
  );

  outputChannel.appendLine('正在启动 Mota 语言服务器...');
  
  // 启动客户端并输出调试信息
  client.start().then(() => {
    outputChannel.appendLine('✅ Mota 语言服务器启动成功!');
    outputChannel.appendLine('现在可以使用以下功能:');
    outputChannel.appendLine('- 按 F12 进行定义跳转');
    outputChannel.appendLine('- 悬停查看符号信息');
    outputChannel.appendLine('- 代码自动补全');
    console.log('Mota 语言服务器启动成功');
  }).catch(error => {
    outputChannel.appendLine(`❌ Mota 语言服务器启动失败: ${error}`);
    outputChannel.appendLine(`错误详情: ${JSON.stringify(error, null, 2)}`);
    console.error('Mota 语言服务器启动失败:', error);
  });
  
  console.log('Mota 插件激活完成');
}

export function deactivate(): Thenable<void> | undefined {
  if (outputChannel) {
    outputChannel.appendLine('Mota 语言插件正在停用...');
  }
  
  if (!client) {
    return undefined;
  }
  return client.stop();
}
