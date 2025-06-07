import { TextDocument } from 'vscode-languageserver-textdocument';
import { Range } from 'vscode-languageserver/node';
import { ParseResult } from './types';
import { addSymbol, addReference, symbols } from './symbols';

// 解析文档，提取符号信息
export function parseDocument(text: string, uri: string): ParseResult {
  // 按行分割文本
  const lines = text.split(/\r?\n/);
  
  // 存储包含的文件和命名空间
  const includes: string[] = [];
  const namespaces: string[] = [];
  let currentNamespace = '';
  
  // 定义正则表达式来匹配各种符号
  const namespaceRegex = /namespace\s+([a-zA-Z0-9_.]+)\s*;/g;
  const includeRegex = /include\s+"([^"]+)"\s*;/g;
  const enumRegex = /enum\s+(\w+)\s*\{/g;
  const structRegex = /struct\s+(\w+)(?:\s*:\s*(\w+))?\s*\{/g;
  const blockRegex = /block\s+(\w+)\s*\{/g;
  const annotationRegex = /annotation\s+(\w+)(?:\s*\{|\s*;)/g;
  const fieldRegex = /(?:optional\s+|repeated\s+|map\s+)?(\w+(?:\.\w+)*)\s+(\w+)\s*(?:=|;)/g;
  const annotationUsageRegex = /@(\w+(?:\.\w+)*)/g;
  const annotationParamRegex = /(\w+)\s*=\s*([^,)]+)/g;
  
  // 逐行解析
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];
    
    // 匹配命名空间
    let match;
    while ((match = namespaceRegex.exec(line)) !== null) {
      currentNamespace = match[1];
      namespaces.push(currentNamespace);
    }
    
    // 匹配包含语句
    namespaceRegex.lastIndex = 0;
    while ((match = includeRegex.exec(line)) !== null) {
      includes.push(match[1]);
    }
    
    // 匹配枚举定义
    includeRegex.lastIndex = 0;
    while ((match = enumRegex.exec(line)) !== null) {
      const name = match[1];
      const fullName = currentNamespace ? `${currentNamespace}.${name}` : name;
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(fullName, 'enum', uri, range);
    }
    
    // 匹配结构体定义
    enumRegex.lastIndex = 0;
    while ((match = structRegex.exec(line)) !== null) {
      const name = match[1];
      const baseType = match[2]; // 可能是 undefined
      const fullName = currentNamespace ? `${currentNamespace}.${name}` : name;
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(fullName, 'struct', uri, range);
      
      // 如果有基类型，添加引用
      if (baseType) {
        const baseFullName = currentNamespace ? `${currentNamespace}.${baseType}` : baseType;
        addReference(baseFullName, uri, {
          start: { line: i, character: match.index + match[0].indexOf(baseType) },
          end: { line: i, character: match.index + match[0].indexOf(baseType) + baseType.length }
        });
      }
    }
    
    // 匹配块定义
    structRegex.lastIndex = 0;
    while ((match = blockRegex.exec(line)) !== null) {
      const name = match[1];
      const fullName = currentNamespace ? `${currentNamespace}.${name}` : name;
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(fullName, 'block', uri, range);
    }
    
    // 匹配注解定义
    blockRegex.lastIndex = 0;
    while ((match = annotationRegex.exec(line)) !== null) {
      const name = match[1];
      const fullName = currentNamespace ? `${currentNamespace}.${name}` : name;
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      // 解析注解参数
      const parameters: string[] = [];
      
      // 如果注解有参数定义（带有大括号），尝试解析参数
      if (match[0].includes('{')) {
        // 查找注解定义的结束位置
        let braceCount = 1;
        let endLine = i;
        let annotationBody = '';
        
        // 收集注解体
        for (let j = i; j < lines.length; j++) {
          const currentLine = j === i ? lines[j].substring(match[0].length) : lines[j];
          
          for (let k = 0; k < currentLine.length; k++) {
            if (currentLine[k] === '{') braceCount++;
            if (currentLine[k] === '}') braceCount--;
            
            if (braceCount === 0) {
              endLine = j;
              annotationBody += currentLine.substring(0, k);
              break;
            }
          }
          
          if (braceCount === 0) break;
          annotationBody += currentLine + '\n';
        }
        
        // 解析注解体中的参数
        const paramRegex = /(\w+)\s+(\w+)(?:\s*=\s*([^;]+))?\s*;/g;
        let paramMatch;
        while ((paramMatch = paramRegex.exec(annotationBody)) !== null) {
          parameters.push(paramMatch[1]);
        }
      }
      
      addSymbol(fullName, 'annotation', uri, range, parameters);
    }
    
    // 匹配字段定义
    annotationRegex.lastIndex = 0;
    while ((match = fieldRegex.exec(line)) !== null) {
      const type = match[1];
      const name = match[2];
      const fullName = currentNamespace ? `${currentNamespace}.${name}` : name;
      const range = {
        start: { line: i, character: match.index },
        end: { line: i, character: match.index + match[0].length }
      };
      
      addSymbol(fullName, 'field', uri, range);
      
      // 添加类型引用
      const typeFullName = type.includes('.') ? type : (currentNamespace ? `${currentNamespace}.${type}` : type);
      addReference(typeFullName, uri, {
        start: { line: i, character: match.index + match[0].indexOf(type) },
        end: { line: i, character: match.index + match[0].indexOf(type) + type.length }
      });
    }
    
    // 匹配注解使用
    fieldRegex.lastIndex = 0;
    while ((match = annotationUsageRegex.exec(line)) !== null) {
      const annotationName = match[1];
      const annotationFullName = annotationName.includes('.') ? annotationName : (currentNamespace ? `${currentNamespace}.${annotationName}` : annotationName);
      
      // 添加注解引用
      addReference(annotationFullName, uri, {
        start: { line: i, character: match.index + 1 }, // +1 跳过 @
        end: { line: i, character: match.index + match[0].length }
      });
      
      // 解析注解参数
      const paramStart = line.indexOf('(', match.index + match[0].length);
      if (paramStart !== -1) {
        const paramEnd = line.indexOf(')', paramStart);
        if (paramEnd !== -1) {
          const paramText = line.substring(paramStart + 1, paramEnd);
          let paramMatch;
          while ((paramMatch = annotationParamRegex.exec(paramText)) !== null) {
            const paramName = paramMatch[1];
            const paramValue = paramMatch[2];
            
            // 这里可以添加参数处理逻辑
          }
        }
      }
    }
  }
  
  return {
    symbols,
    includes,
    namespaces
  };
}

// 解析文档中的单词
export function getWordAtPosition(document: TextDocument, position: { line: number, character: number }): string | null {
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
export function getWordRangeAtPosition(document: TextDocument, position: { line: number, character: number }): Range | null {
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
