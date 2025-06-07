"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const node_1 = require("vscode-languageserver/node");
const vscode_languageserver_textdocument_1 = require("vscode-languageserver-textdocument");
// 导入模块
const diagnostics_1 = require("./modules/diagnostics");
const completions_1 = require("./modules/completions");
const definitions_1 = require("./modules/definitions");
const formatting_1 = require("./modules/formatting");
const hover_1 = require("./modules/hover");
const rename_1 = require("./modules/rename");
// 创建连接
const connection = (0, node_1.createConnection)(node_1.ProposedFeatures.all);
// 创建文档管理器
const documents = new node_1.TextDocuments(vscode_languageserver_textdocument_1.TextDocument);
connection.onInitialize((params) => {
    const result = {
        capabilities: {
            textDocumentSync: node_1.TextDocumentSyncKind.Incremental,
            // 启用代码补全功能
            completionProvider: {
                resolveProvider: true,
                triggerCharacters: ['.', '@']
            },
            // 启用跳转到定义功能
            definitionProvider: true,
            // 启用查找引用功能
            referencesProvider: true,
            // 启用重命名功能
            renameProvider: {
                prepareProvider: true
            },
            // 启用悬停提示功能
            hoverProvider: true,
            // 启用代码格式化功能
            documentFormattingProvider: true
        }
    };
    return result;
});
// 当文档内容变化时，重新解析文档
documents.onDidChangeContent(change => {
    validateTextDocumentAndSendDiagnostics(change.document);
});
// 验证文档并生成诊断信息
async function validateTextDocumentAndSendDiagnostics(textDocument) {
    // 使用模块化的验证函数
    const diagnostics = await (0, diagnostics_1.validateTextDocument)(textDocument);
    // 发送诊断信息
    connection.sendDiagnostics({ uri: textDocument.uri, diagnostics });
}
// 使用模块化的符号管理功能
// 使用模块化的文档解析功能
// 处理跳转到定义请求
connection.onDefinition((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return null;
    }
    return (0, definitions_1.provideDefinition)(document, params);
});
// 处理查找引用请求
connection.onReferences((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return [];
    }
    return (0, definitions_1.provideReferences)(document, params);
});
// 处理准备重命名请求
connection.onPrepareRename((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return null;
    }
    return (0, rename_1.prepareRename)(document, params);
});
// 处理重命名请求
connection.onRenameRequest((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return { changes: {} };
    }
    return (0, rename_1.performRename)(document, params);
});
// 使用模块化的文本处理功能
// 处理挂停提示请求
connection.onHover((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return null;
    }
    return (0, hover_1.provideHover)(document, params.position);
});
// 处理代码补全请求
connection.onCompletion((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return [];
    }
    return (0, completions_1.provideCompletions)(document, params);
});
// 处理代码补全项解析
connection.onCompletionResolve((item) => {
    return (0, completions_1.resolveCompletion)(item);
});
// 处理代码格式化请求
connection.onDocumentFormatting((params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) {
        return null;
    }
    return (0, formatting_1.formatDocument)(document);
});
// 监听文档变化
documents.listen(connection);
// 监听连接
connection.listen();
//# sourceMappingURL=server.js.map