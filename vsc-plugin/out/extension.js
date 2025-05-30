"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.deactivate = exports.activate = void 0;
const path = require("path");
const vscode_1 = require("vscode");
const node_1 = require("vscode-languageclient/node");
let client;
function activate(context) {
    // 服务器模块的路径
    const serverModule = context.asAbsolutePath(path.join('server', 'out', 'server.js'));
    // 服务器的调试选项
    const debugOptions = { execArgv: ['--nolazy', '--inspect=6009'] };
    // 服务器选项
    const serverOptions = {
        run: { module: serverModule, transport: node_1.TransportKind.ipc },
        debug: {
            module: serverModule,
            transport: node_1.TransportKind.ipc,
            options: debugOptions
        }
    };
    // 客户端选项
    const clientOptions = {
        // 注册 Mota 语言的服务器
        documentSelector: [{ scheme: 'file', language: 'mota' }],
        synchronize: {
            // 监听配置变化
            configurationSection: 'motaLanguageServer',
            // 监听工作区文件变化
            fileEvents: vscode_1.workspace.createFileSystemWatcher('**/*.mota')
        }
    };
    // 创建语言客户端并启动
    client = new node_1.LanguageClient('motaLanguageServer', 'Mota Language Server', serverOptions, clientOptions);
    // 启动客户端
    client.start();
}
exports.activate = activate;
function deactivate() {
    if (!client) {
        return undefined;
    }
    return client.stop();
}
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map