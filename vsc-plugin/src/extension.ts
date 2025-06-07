import * as path from 'path';
import { workspace, ExtensionContext } from 'vscode';

import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind
} from 'vscode-languageclient/node';

let client: LanguageClient;

export function activate(context: ExtensionContext) {
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
    documentSelector: [{ scheme: 'file', language: 'mota' }],
    synchronize: {
      // 监听配置变化
      configurationSection: 'motaLanguageServer',
      // 监听工作区文件变化
      fileEvents: workspace.createFileSystemWatcher('**/*.mota')
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
