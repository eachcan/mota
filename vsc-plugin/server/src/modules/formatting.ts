import { TextEdit, Range } from 'vscode-languageserver/node';
import { TextDocument } from 'vscode-languageserver-textdocument';

// 处理代码格式化请求
export function formatDocument(document: TextDocument): TextEdit[] | null {
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
}
