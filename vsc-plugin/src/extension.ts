import * as path from 'path';
import { workspace, ExtensionContext, languages, Position, Location, Uri, TextDocument, CancellationToken, ProviderResult } from 'vscode';

import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind
} from 'vscode-languageclient/node';

let client: LanguageClient;

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
      const workspaceLocations = await this.findMiscDefinitionInWorkspace(functionName);
      locations.push(...workspaceLocations);
    }
    
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
        console.error(`Error reading file ${file.fsPath}:`, error);
      }
    }
    
    return locations;
  }
}

export function activate(context: ExtensionContext) {
  // 注册MOTA模板的定义提供器
  const templateDefinitionProvider = languages.registerDefinitionProvider(
    { scheme: 'file', language: 'mota-template' },
    new MotaTemplateDefinitionProvider()
  );
  
  context.subscriptions.push(templateDefinitionProvider);
  
  // 服务器模块的路径
  const serverModule = context.asAbsolutePath(
    path.join('server', 'out', 'server.js')
  );
  
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
    }
  };

  // 创建语言客户端并启动
  client = new LanguageClient(
    'motaLanguageServer',
    'Mota Language Server',
    serverOptions,
    clientOptions
  );

  // 启动客户端并输出调试信息
  console.log('Starting Mota Language Server...');
  client.start();
  console.log('Mota Language Server started.');
}

export function deactivate(): Thenable<void> | undefined {
  if (!client) {
    return undefined;
  }
  return client.stop();
}
