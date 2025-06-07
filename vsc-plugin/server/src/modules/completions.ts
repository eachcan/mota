import { 
  CompletionItem, 
  CompletionItemKind, 
  TextDocumentPositionParams 
} from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';
import { getAllAnnotations, getSymbolsByKind } from './symbols';
import { SymbolInfo } from './types';

// 处理代码补全请求
export function provideCompletions(document: TextDocument, position: TextDocumentPositionParams): CompletionItem[] {
  if (!document) {
    return [];
  }
  
  const text = document.getText();
  const line = text.split(/\r?\n/)[position.position.line];
  const linePrefix = line.substring(0, position.position.character);
  
  // 提供不同上下文的补全项
  const completionItems: CompletionItem[] = [];
  
  // 1. 注解补全（在 @ 后）
  if (linePrefix.trimRight().endsWith('@')) {
    // 从符号表中获取所有注解
    const annotations = getAllAnnotations();
    for (const annotation of annotations) {
      completionItems.push(
        createCompletionItem(
          annotation.name, 
          CompletionItemKind.Class, 
          annotation.description || `${annotation.name}注解`
        )
      );
    }
    
    // 如果没有找到注解，提供一些默认的注解
    if (completionItems.length === 0) {
      completionItems.push(
        createCompletionItem('Storage', CompletionItemKind.Class, '存储配置注解'),
        createCompletionItem('Window', CompletionItemKind.Class, '窗口配置注解'),
        createCompletionItem('Scope', CompletionItemKind.Class, '作用域注解')
      );
    }
  }
  
  // 2. 类型补全（在字段定义中）
  if (/\s+\w+$/.test(linePrefix)) {
    // 添加基本类型
    completionItems.push(
      createCompletionItem('int8', CompletionItemKind.Keyword, '8位整数类型'),
      createCompletionItem('int16', CompletionItemKind.Keyword, '16位整数类型'),
      createCompletionItem('int32', CompletionItemKind.Keyword, '32位整数类型'),
      createCompletionItem('int64', CompletionItemKind.Keyword, '64位整数类型'),
      createCompletionItem('float32', CompletionItemKind.Keyword, '32位浮点数类型'),
      createCompletionItem('float64', CompletionItemKind.Keyword, '64位浮点数类型'),
      createCompletionItem('string', CompletionItemKind.Keyword, '字符串类型'),
      createCompletionItem('bytes', CompletionItemKind.Keyword, '二进制数据类型'),
      createCompletionItem('bool', CompletionItemKind.Keyword, '布尔类型'),
      createCompletionItem('optional', CompletionItemKind.Keyword, '可选类型修饰符'),
      createCompletionItem('repeated', CompletionItemKind.Keyword, '数组类型修饰符'),
      createCompletionItem('map', CompletionItemKind.Keyword, '映射类型')
    );
    
    // 添加自定义类型（从符号表中获取）
    const customTypes = [
      ...getSymbolsByKind('enum'),
      ...getSymbolsByKind('struct'),
      ...getSymbolsByKind('block')
    ];
    
    for (const symbol of customTypes) {
      completionItems.push(
        createCompletionItem(
          symbol.name, 
          CompletionItemKind.Class, 
          `自定义${symbol.kind}类型`
        )
      );
    }
  }
  
  // 3. 关键字补全
  if (linePrefix.trim() === '' || /^\s*\w*$/.test(linePrefix)) {
    completionItems.push(
      createCompletionItem('namespace', CompletionItemKind.Keyword, '命名空间定义'),
      createCompletionItem('include', CompletionItemKind.Keyword, '引入其他文件'),
      createCompletionItem('enum', CompletionItemKind.Keyword, '枚举类型定义'),
      createCompletionItem('struct', CompletionItemKind.Keyword, '结构体定义'),
      createCompletionItem('block', CompletionItemKind.Keyword, '块定义'),
      createCompletionItem('annotation', CompletionItemKind.Keyword, '注解定义')
    );
  }
  
  // 4. 注解参数补全（在注解内部）
  const annotationParamRegex = /@(\w+(?:\.\w+)*)\s*\(([^)]*)$/;
  const match = linePrefix.match(annotationParamRegex);
  if (match) {
    const annotationName = match[1];
    
    // 查找注解定义
    const annotations = getAllAnnotations();
    const annotation = annotations.find(a => a.name === annotationName);
    
    if (annotation && annotation.parameters) {
      // 根据注解定义提供参数补全
      for (const param of annotation.parameters) {
        completionItems.push(
          createCompletionItem(`${param} = `, CompletionItemKind.Property, `${annotationName}的${param}参数`)
        );
      }
    } else {
      // 如果找不到注解定义，提供一些常见参数
      switch (annotationName) {
        case 'Storage':
          completionItems.push(
            createCompletionItem('path = ""', CompletionItemKind.Property, '存储路径'),
            createCompletionItem('format = ""', CompletionItemKind.Property, '存储格式')
          );
          break;
        case 'Window':
          completionItems.push(
            createCompletionItem('title = ""', CompletionItemKind.Property, '窗口标题'),
            createCompletionItem('desc = ""', CompletionItemKind.Property, '窗口描述')
          );
          break;
        case 'Scope':
          completionItems.push(
            createCompletionItem('value = ""', CompletionItemKind.Property, '作用域值')
          );
          break;
        case 'Int':
        case 'Float':
          completionItems.push(
            createCompletionItem('min = ', CompletionItemKind.Property, '最小值'),
            createCompletionItem('max = ', CompletionItemKind.Property, '最大值'),
            createCompletionItem('step = ', CompletionItemKind.Property, '步长'),
            createCompletionItem('desc = ""', CompletionItemKind.Property, '描述')
          );
          break;
        case 'Text':
          completionItems.push(
            createCompletionItem('max_length = ', CompletionItemKind.Property, '最大长度'),
            createCompletionItem('desc = ""', CompletionItemKind.Property, '描述'),
            createCompletionItem('pattern = ""', CompletionItemKind.Property, '正则表达式')
          );
          break;
        default:
          completionItems.push(
            createCompletionItem('desc = ""', CompletionItemKind.Property, '描述')
          );
          break;
      }
    }
  }
  
  return completionItems;
}

// 处理代码补全项解析
export function resolveCompletion(item: CompletionItem): CompletionItem {
  // 可以在这里添加更多的文档信息
  return item;
}

// 创建补全项辅助函数
export function createCompletionItem(label: string, kind: CompletionItemKind, detail: string): CompletionItem {
  return {
    label,
    kind,
    detail,
    data: { label }
  };
}
