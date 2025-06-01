import { WorkspaceEdit, TextEdit, PrepareRenameParams, RenameParams } from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { getWordAtPosition, getWordRangeAtPosition } from './parser';
import { symbols } from './symbols';

// 处理准备重命名请求
export function prepareRename(document: TextDocument, params: PrepareRenameParams) {
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
}

// 处理重命名请求
export function performRename(document: TextDocument, params: RenameParams): WorkspaceEdit {
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
}
