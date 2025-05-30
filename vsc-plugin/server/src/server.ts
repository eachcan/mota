import {
  createConnection,
  TextDocuments,
  Diagnostic,
  DiagnosticSeverity,
  ProposedFeatures,
  InitializeParams,
  DidChangeConfigurationNotification,
  CompletionItem,
  CompletionItemKind,
  TextDocumentPositionParams,
  TextDocumentSyncKind,
  InitializeResult,
  Definition,
  Location,
  ReferenceParams,
  PrepareRenameParams,
  RenameParams,
  WorkspaceEdit,
  TextEdit,
  Range
} from 'vscode-languageserver/node';

import {
  TextDocument
} from 'vscode-languageserver-textdocument';

// 创建连接
const connection = createConnection(ProposedFeatures.all);

// 创建文档管理器
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

// 存储所有符号的定义和引用
interface SymbolInfo {
  name: string;
  kind: string; // enum, struct, block, annotation, field, etc.
  uri: string;
  range: Range;
  references: Location[];
}

// 存储所有文档中的符号
const symbols: Map<string, SymbolInfo> = new Map();

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
  validateTextDocument(change.document);
});

// 解析文档，提取符号信息
async function validateTextDocument(textDocument: TextDocument): Promise<void> {
  const text = textDocument.getText();
  const uri = textDocument.uri;
  
  // 清除此文档中的旧符号
  clearSymbolsForDocument(uri);
  
  // 解析文档，提取符号信息
  parseDocument(text, uri);
  
  // 发送诊断信息
  const diagnostics: Diagnostic[] = [];
  connection.sendDiagnostics({ uri, diagnostics });
}

// 清除指定文档中的所有符号
function clearSymbolsForDocument(uri: string): void {
  for (const [key, symbol] of symbols.entries()) {
    if (symbol.uri === uri) {
      symbols.delete(key);
    } else {
      // 移除引用中属于该文档的引用
      symbol.references = symbol.references.filter(ref => ref.uri !== uri);
    }
  }
}

// 解析文档，提取符号信息
function parseDocument(text: string, uri: string): void {
  // 这里是简化版的解析逻辑，实际实现需要更复杂的语法分析
  
  // 按行分割文本
  const lines = text.split(/\r?\n/);
  
  // 定义正则表达式来匹配各种符号
  const enumRegex = /enum\s+(\w+)\s*\{/g;
  const structRegex = /struct\s+(\w+)(?:\s*:\s*(\w+))?\s*\{/g;
  const blockRegex = /block\s+(\w+)\s*\{/g;
  const annotationRegex = /annotation\s+(\w+)(?:\s*\{|\s*;)/g;
  const fieldRegex = /(?:optional\s+|repeated\s+|map\s+)?(\w+(?:\.\w+)*)\s+(\w+)\s*(?:=|;)/g;
  const annotationUsageRegex = /@(\w+(?:\.\w+)*)/g;
  
  // 逐行解析
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];
    
    // 匹配枚举定义
    let match;
    while ((match = enumRegex.exec(line)) !== null) {
      const name = match[1];
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(name, 'enum', uri, range);
    }
    
    // 匹配结构体定义
    enumRegex.lastIndex = 0; // 重置正则表达式
    while ((match = structRegex.exec(line)) !== null) {
      const name = match[1];
      const baseType = match[2]; // 可能是 undefined
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(name, 'struct', uri, range);
      
      // 如果有基类型，添加引用
      if (baseType) {
        addReference(baseType, uri, {
          start: { line: i, character: match.index + match[0].indexOf(baseType) },
          end: { line: i, character: match.index + match[0].indexOf(baseType) + baseType.length }
        });
      }
    }
    
    // 匹配块定义
    structRegex.lastIndex = 0;
    while ((match = blockRegex.exec(line)) !== null) {
      const name = match[1];
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(name, 'block', uri, range);
    }
    
    // 匹配注解定义
    blockRegex.lastIndex = 0;
    while ((match = annotationRegex.exec(line)) !== null) {
      const name = match[1];
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(name, 'annotation', uri, range);
    }
    
    // 匹配字段定义
    annotationRegex.lastIndex = 0;
    while ((match = fieldRegex.exec(line)) !== null) {
      const type = match[1];
      const name = match[2];
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(name, 'field', uri, range);
      
      // 添加类型引用
      addReference(type, uri, {
        start: { line: i, character: match.index + match[0].indexOf(type) },
        end: { line: i, character: match.index + match[0].indexOf(type) + type.length }
      });
    }
    
    // 匹配注解使用
    fieldRegex.lastIndex = 0;
    while ((match = annotationUsageRegex.exec(line)) !== null) {
      const name = match[1];
      
      // 添加注解引用
      addReference(name, uri, {
        start: { line: i, character: match.index + 1 }, // +1 跳过 @ 符号
        end: { line: i, character: match.index + match[0].length }
      });
    }
  }
}

// 添加符号定义
function addSymbol(name: string, kind: string, uri: string, range: Range): void {
  symbols.set(name, {
    name,
    kind,
    uri,
    range,
    references: []
  });
}

// 添加符号引用
function addReference(name: string, uri: string, range: Range): void {
  const symbol = symbols.get(name);
  if (symbol) {
    symbol.references.push({
      uri,
      range
    });
  }
}

// 处理跳转到定义请求
connection.onDefinition((params: TextDocumentPositionParams): Definition | null => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, params.position);
  if (!word) {
    return null;
  }
  
  // 查找符号定义
  const symbol = symbols.get(word);
  if (symbol) {
    return {
      uri: symbol.uri,
      range: symbol.range
    };
  }
  
  return null;
});

// 处理查找引用请求
connection.onReferences((params: ReferenceParams): Location[] => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return [];
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, params.position);
  if (!word) {
    return [];
  }
  
  // 查找符号
  const symbol = symbols.get(word);
  if (symbol) {
    // 返回所有引用，包括定义
    return [
      { uri: symbol.uri, range: symbol.range },
      ...symbol.references
    ];
  }
  
  return [];
});

// 处理准备重命名请求
connection.onPrepareRename((params: PrepareRenameParams) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, params.position);
  if (!word) {
    return null;
  }
  
  // 查找符号
  const symbol = symbols.get(word);
  if (!symbol) {
    return null;
  }
  
  // 获取单词范围
  const range = getWordRangeAtPosition(document, params.position);
  if (!range) {
    return null;
  }
  
  // 返回可重命名的范围
  return {
    range: range,
    placeholder: word
  };
});

// 处理重命名请求
connection.onRenameRequest((params: RenameParams): WorkspaceEdit => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return { changes: {} };
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, params.position);
  if (!word) {
    return { changes: {} };
  }
  
  // 查找符号
  const symbol = symbols.get(word);
  if (!symbol) {
    return { changes: {} };
  }
  
  // 创建工作区编辑
  const changes: { [uri: string]: TextEdit[] } = {};
  
  // 添加定义的编辑
  if (!changes[symbol.uri]) {
    changes[symbol.uri] = [];
  }
  changes[symbol.uri].push({
    range: symbol.range,
    newText: params.newName
  });
  
  // 添加所有引用的编辑
  for (const reference of symbol.references) {
    if (!changes[reference.uri]) {
      changes[reference.uri] = [];
    }
    changes[reference.uri].push({
      range: reference.range,
      newText: params.newName
    });
  }
  
  return { changes };
});

// 获取指定位置的单词
function getWordAtPosition(document: TextDocument, position: { line: number, character: number }): string | null {
  const line = document.getText({
    start: { line: position.line, character: 0 },
    end: { line: position.line + 1, character: 0 }
  });
  
  // 查找光标位置的单词
  const wordRegex = /[a-zA-Z0-9_\.]+/g;
  let match;
  while ((match = wordRegex.exec(line)) !== null) {
    const start = match.index;
    const end = start + match[0].length;
    
    if (position.character >= start && position.character <= end) {
      return match[0];
    }
  }
  
  return null;
}

// 获取指定位置的单词范围
function getWordRangeAtPosition(document: TextDocument, position: { line: number, character: number }): Range | null {
  const line = document.getText({
    start: { line: position.line, character: 0 },
    end: { line: position.line + 1, character: 0 }
  });
  
  // 查找光标位置的单词
  const wordRegex = /[a-zA-Z0-9_\.]+/g;
  let match;
  while ((match = wordRegex.exec(line)) !== null) {
    const start = match.index;
    const end = start + match[0].length;
    
    if (position.character >= start && position.character <= end) {
      return {
        start: { line: position.line, character: start },
        end: { line: position.line, character: end }
      };
    }
  }
  
  return null;
}

// 处理悬停提示请求
connection.onHover((params) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, params.position);
  if (!word) {
    return null;
  }
  
  // 查找符号
  const symbol = symbols.get(word);
  if (!symbol) {
    return null;
  }
  
  // 根据符号类型生成不同的提示信息
  let content = '';
  switch (symbol.kind) {
    case 'enum':
      content = `**枚举类型**: ${symbol.name}`;
      break;
    case 'struct':
      content = `**结构体**: ${symbol.name}`;
      break;
    case 'block':
      content = `**块**: ${symbol.name}`;
      break;
    case 'annotation':
      content = `**注解**: ${symbol.name}`;
      break;
    case 'field':
      content = `**字段**: ${symbol.name}`;
      break;
    default:
      content = `**符号**: ${symbol.name}`;
  }
  
  // 添加引用计数
  content += `\n\n引用次数: ${symbol.references.length}`;
  
  return {
    contents: {
      kind: 'markdown',
      value: content
    }
  };
});

// 处理代码格式化请求
connection.onDocumentFormatting((params) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return null;
  }
  
  const text = document.getText();
  const lines = text.split(/\r?\n/);
  const edits: TextEdit[] = [];
  
  // 格式化规则：
  // 1. 缩进使用4个空格
  // 2. 在分号和逗号后添加空格
  // 3. 在大括号前后添加空格
  // 4. 保持空行的一致性
  
  let indentLevel = 0;
  let inComment = false;
  
  for (let i = 0; i < lines.length; i++) {
    let line = lines[i].trimLeft();
    
    // 跳过空行
    if (line.length === 0) {
      continue;
    }
    
    // 处理注释
    if (line.startsWith('/*')) {
      inComment = true;
    }
    if (inComment) {
      if (line.includes('*/')) {
        inComment = false;
      }
      continue;
    }
    if (line.startsWith('//')) {
      continue;
    }
    
    // 调整缩进级别
    if (line.startsWith('}')) {
      indentLevel = Math.max(0, indentLevel - 1);
    }
    
    // 创建正确的缩进
    const indent = ' '.repeat(indentLevel * 4);
    let formattedLine = indent + line;
    
    // 在分号和逗号后添加空格
    formattedLine = formattedLine.replace(/;(\S)/g, '; $1');
    formattedLine = formattedLine.replace(/,(\S)/g, ', $1');
    
    // 在等号前后添加空格
    formattedLine = formattedLine.replace(/([^=])=([^=])/g, '$1 = $2');
    
    // 在大括号前添加空格
    formattedLine = formattedLine.replace(/\S\{/g, ' {');
    
    // 如果当前行包含左大括号，增加缩进级别
    if (line.includes('{')) {
      indentLevel++;
    }
    
    // 如果当前行与原始行不同，创建一个编辑
    if (formattedLine !== lines[i]) {
      edits.push({
        range: {
          start: { line: i, character: 0 },
          end: { line: i, character: lines[i].length }
        },
        newText: formattedLine
      });
    }
  }
  
  return edits;
});

// 监听文档变化
documents.listen(connection);

// 监听连接
connection.listen();
