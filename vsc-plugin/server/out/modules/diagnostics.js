"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.validateTextDocument = validateTextDocument;
const node_1 = require("vscode-languageserver/node");
const parser_1 = require("./parser");
const symbols_1 = require("./symbols");
// 验证文档并生成诊断信息
async function validateTextDocument(document) {
    const text = document.getText();
    const uri = document.uri;
    // 清除此文档中的旧符号
    (0, symbols_1.clearSymbolsForDocument)(uri);
    // 解析文档，提取符号信息
    (0, parser_1.parseDocument)(text, uri);
    // 生成诊断信息
    const diagnostics = [];
    // 检查语法错误
    checkSyntaxErrors(text, diagnostics);
    // 检查引用错误
    checkReferenceErrors(text, uri, diagnostics);
    return diagnostics;
}
// 检查语法错误
function checkSyntaxErrors(text, diagnostics) {
    const lines = text.split(/\r?\n/);
    // 检查未闭合的括号
    let braceCount = 0;
    let parenCount = 0;
    let squareCount = 0;
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i];
        for (let j = 0; j < line.length; j++) {
            switch (line[j]) {
                case '{':
                    braceCount++;
                    break;
                case '}':
                    braceCount--;
                    break;
                case '(':
                    parenCount++;
                    break;
                case ')':
                    parenCount--;
                    break;
                case '[':
                    squareCount++;
                    break;
                case ']':
                    squareCount--;
                    break;
            }
            // 检查括号是否匹配
            if (braceCount < 0) {
                diagnostics.push({
                    severity: node_1.DiagnosticSeverity.Error,
                    range: {
                        start: { line: i, character: j },
                        end: { line: i, character: j + 1 }
                    },
                    message: '多余的右大括号',
                    source: 'mota'
                });
                braceCount = 0;
            }
            if (parenCount < 0) {
                diagnostics.push({
                    severity: node_1.DiagnosticSeverity.Error,
                    range: {
                        start: { line: i, character: j },
                        end: { line: i, character: j + 1 }
                    },
                    message: '多余的右小括号',
                    source: 'mota'
                });
                parenCount = 0;
            }
            if (squareCount < 0) {
                diagnostics.push({
                    severity: node_1.DiagnosticSeverity.Error,
                    range: {
                        start: { line: i, character: j },
                        end: { line: i, character: j + 1 }
                    },
                    message: '多余的右方括号',
                    source: 'mota'
                });
                squareCount = 0;
            }
        }
    }
    // 检查未闭合的括号
    if (braceCount > 0) {
        diagnostics.push({
            severity: node_1.DiagnosticSeverity.Error,
            range: {
                start: { line: lines.length - 1, character: 0 },
                end: { line: lines.length - 1, character: 1 }
            },
            message: `缺少 ${braceCount} 个右大括号`,
            source: 'mota'
        });
    }
    if (parenCount > 0) {
        diagnostics.push({
            severity: node_1.DiagnosticSeverity.Error,
            range: {
                start: { line: lines.length - 1, character: 0 },
                end: { line: lines.length - 1, character: 1 }
            },
            message: `缺少 ${parenCount} 个右小括号`,
            source: 'mota'
        });
    }
    if (squareCount > 0) {
        diagnostics.push({
            severity: node_1.DiagnosticSeverity.Error,
            range: {
                start: { line: lines.length - 1, character: 0 },
                end: { line: lines.length - 1, character: 1 }
            },
            message: `缺少 ${squareCount} 个右方括号`,
            source: 'mota'
        });
    }
}
// 检查引用错误
function checkReferenceErrors(text, uri, diagnostics) {
    // 这里可以添加更多的引用检查逻辑
    // 例如检查未定义的类型、未定义的注解等
}
//# sourceMappingURL=diagnostics.js.map