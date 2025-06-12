"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.deactivate = exports.activate = void 0;
const path = require("path");
const vscode_1 = require("vscode");
const node_1 = require("vscode-languageclient/node");
let client;
// MOTA模板定义跳转提供器
class MotaTemplateDefinitionProvider {
    provideDefinition(document, position, token) {
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
    async findMiscDefinition(document, functionName) {
        const text = document.getText();
        const lines = text.split('\n');
        const locations = [];
        // 搜索<%misc functionName%>定义
        const miscRegex = new RegExp(`<%\\s*misc\\s+${functionName}\\s*%>`, 'g');
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i];
            const match = miscRegex.exec(line);
            if (match) {
                const location = new vscode_1.Location(document.uri, new vscode_1.Position(i, match.index + match[0].indexOf(functionName)));
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
    async findMiscDefinitionInWorkspace(functionName) {
        const locations = [];
        // 搜索工作区内的所有.template文件
        const files = await vscode_1.workspace.findFiles('**/*.template', '**/node_modules/**');
        for (const file of files) {
            try {
                const document = await vscode_1.workspace.openTextDocument(file);
                const text = document.getText();
                const lines = text.split('\n');
                const miscRegex = new RegExp(`<%\\s*misc\\s+${functionName}\\s*%>`, 'g');
                for (let i = 0; i < lines.length; i++) {
                    const line = lines[i];
                    const match = miscRegex.exec(line);
                    if (match) {
                        const location = new vscode_1.Location(file, new vscode_1.Position(i, match.index + match[0].indexOf(functionName)));
                        locations.push(location);
                        miscRegex.lastIndex = 0;
                    }
                }
            }
            catch (error) {
                console.error(`Error reading file ${file.fsPath}:`, error);
            }
        }
        return locations;
    }
}
function activate(context) {
    // 注册MOTA模板的定义提供器
    const templateDefinitionProvider = vscode_1.languages.registerDefinitionProvider({ scheme: 'file', language: 'mota-template' }, new MotaTemplateDefinitionProvider());
    context.subscriptions.push(templateDefinitionProvider);
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
        documentSelector: [
            { scheme: 'file', language: 'mota' },
            { scheme: 'file', language: 'mota-template' }
        ],
        synchronize: {
            // 监听配置变化
            configurationSection: 'motaLanguageServer',
            // 监听工作区文件变化
            fileEvents: vscode_1.workspace.createFileSystemWatcher('**/*.{mota,template}')
        }
    };
    // 创建语言客户端并启动
    client = new node_1.LanguageClient('motaLanguageServer', 'Mota Language Server', serverOptions, clientOptions);
    // 启动客户端并输出调试信息
    console.log('Starting Mota Language Server...');
    client.start();
    console.log('Mota Language Server started.');
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