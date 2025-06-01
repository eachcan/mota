import {
  createConnection,
  TextDocuments,
  ProposedFeatures,
  InitializeParams,
  TextDocumentSyncKind,
  InitializeResult,
  TextDocumentPositionParams,
  DidChangeConfigurationNotification,
  Range,
  CompletionItem,
  CompletionItemKind,
  Definition,
  Location,
  ReferenceParams,
  PrepareRenameParams,
  RenameParams,
  WorkspaceEdit,
  TextEdit
} from 'vscode-languageserver/node';

import {
  TextDocument
} from 'vscode-languageserver-textdocument';

// 导入模块
import { validateTextDocument } from './modules/diagnostics';
import { provideCompletions, resolveCompletion } from './modules/completions';
import { provideDefinition, provideReferences } from './modules/definitions';
import { formatDocument } from './modules/formatting';
import { provideHover } from './modules/hover';
import { parseDocument, getWordAtPosition, getWordRangeAtPosition } from './modules/parser';
import { prepareRename, performRename } from './modules/rename';
import { symbols, clearSymbolsForDocument, addSymbol, addReference } from './modules/symbols';
import { SymbolInfo } from './modules/types';

// 创建连接
const connection = createConnection(ProposedFeatures.all);

// 创建文档管理器
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

connection.onInitialize((params: InitializeParams) => {
  const result: InitializeResult = {
    capabilities: {
      textDocumentSync: TextDocumentSyncKind.Incremental,
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
async function validateTextDocumentAndSendDiagnostics(textDocument: TextDocument): Promise<void> {
  // 使用模块化的验证函数
  const diagnostics = await validateTextDocument(textDocument);
  
  // 发送诊断信息
  connection.sendDiagnostics({ uri: textDocument.uri, diagnostics });
}

// 使用模块化的符号管理功能

// 使用模块化的文档解析功能

// 处理跳转到定义请求
connection.onDefinition((params: TextDocumentPositionParams): Definition | null => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  return provideDefinition(document, params);
});

// 处理查找引用请求
connection.onReferences((params: ReferenceParams): Location[] => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return [];
  }
  
  return provideReferences(document, params);
});

// 处理准备重命名请求
connection.onPrepareRename((params: PrepareRenameParams) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  return prepareRename(document, params);
});

// 处理重命名请求
connection.onRenameRequest((params: RenameParams): WorkspaceEdit => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return { changes: {} };
  }
  
  return performRename(document, params);
});

// 使用模块化的文本处理功能

// 处理挂停提示请求
connection.onHover((params) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  return provideHover(document, params.position);
});

// 处理代码补全请求
connection.onCompletion((params: TextDocumentPositionParams): CompletionItem[] => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return [];
  }
  return provideCompletions(document, params);
});

// 处理代码补全项解析
connection.onCompletionResolve((item: CompletionItem): CompletionItem => {
  return resolveCompletion(item);
});

// 处理代码格式化请求
connection.onDocumentFormatting((params) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  return formatDocument(document);
});

// 监听文档变化
documents.listen(connection);

// 监听连接
connection.listen();
