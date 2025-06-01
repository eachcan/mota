import { Hover } from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { getWordAtPosition } from './parser';
import { symbols } from './symbols';

// 处理悬停提示请求
export function provideHover(document: TextDocument, position: { line: number, character: number }): Hover | null {
  if (!document) {
    return null;
  }
  
  // 获取光标位置的单词
  const word = getWordAtPosition(document, position);
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
}
