import { Definition, Location, ReferenceParams, TextDocumentPositionParams } from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { getWordAtPosition } from './parser';
import { symbols } from './symbols';

// 处理跳转到定义请求
export function provideDefinition(document: TextDocument, params: TextDocumentPositionParams): Definition | null {
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
  
  // 返回符号定义的位置
  return {
    uri: symbol.uri,
    range: symbol.range
  };
}

// 处理查找引用请求
export function provideReferences(document: TextDocument, params: ReferenceParams): Location[] {
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
  if (!symbol) {
    return [];
  }
  
  // 如果包含声明，添加声明位置
  const locations: Location[] = [];
  if (params.context.includeDeclaration) {
    locations.push({
      uri: symbol.uri,
      range: symbol.range
    });
  }
  
  // 添加所有引用位置
  locations.push(...symbol.references);
  
  return locations;
}
