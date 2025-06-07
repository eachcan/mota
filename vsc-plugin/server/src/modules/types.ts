import { Range, Location } from 'vscode-languageserver/node';

// 存储所有符号的定义和引用
export interface SymbolInfo {
  name: string;
  kind: string; // enum, struct, block, annotation, field, etc.
  uri: string;
  range: Range;
  references: Location[];
  // 额外信息，用于注解
  parameters?: string[]; // 注解参数列表
  description?: string;  // 描述信息
  fullName?: string;     // 完整名称（包含命名空间）
}

// 文档解析结果
export interface ParseResult {
  symbols: Map<string, SymbolInfo>;
  includes: string[];    // 包含的文件
  namespaces: string[];  // 命名空间
}

// 注解参数信息
export interface AnnotationParameter {
  name: string;
  type: string;
  description?: string;
  defaultValue?: string;
}
