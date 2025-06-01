import { Range, Location } from 'vscode-languageserver/node';
import { SymbolInfo } from './types';

// 存储所有文档中的符号
export const symbols: Map<string, SymbolInfo> = new Map();

// 添加符号定义
export function addSymbol(name: string, kind: string, uri: string, range: Range, parameters?: string[], description?: string): void {
  const symbol: SymbolInfo = {
    name,
    kind,
    uri,
    range,
    references: [],
    parameters,
    description
  };
  
  symbols.set(name, symbol);
}

// 添加符号引用
export function addReference(name: string, uri: string, range: Range): void {
  const symbol = symbols.get(name);
  if (symbol) {
    symbol.references.push({
      uri,
      range
    });
  }
}

// 清除指定文档中的所有符号
export function clearSymbolsForDocument(uri: string): void {
  for (const [key, symbol] of symbols.entries()) {
    if (symbol.uri === uri) {
      symbols.delete(key);
    } else {
      // 移除引用中属于该文档的引用
      symbol.references = symbol.references.filter(ref => ref.uri !== uri);
    }
  }
}

// 获取所有注解符号
export function getAllAnnotations(): SymbolInfo[] {
  const annotations: SymbolInfo[] = [];
  for (const symbol of symbols.values()) {
    if (symbol.kind === 'annotation') {
      annotations.push(symbol);
    }
  }
  return annotations;
}

// 获取指定类型的所有符号
export function getSymbolsByKind(kind: string): SymbolInfo[] {
  const result: SymbolInfo[] = [];
  for (const symbol of symbols.values()) {
    if (symbol.kind === kind) {
      result.push(symbol);
    }
  }
  return result;
}

// 获取符号的完整名称（包含命名空间）
export function getFullName(name: string, namespace: string): string {
  return namespace ? `${namespace}.${name}` : name;
}
