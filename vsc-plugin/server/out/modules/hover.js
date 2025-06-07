"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.provideHover = provideHover;
const parser_1 = require("./parser");
const symbols_1 = require("./symbols");
// 处理悬停提示请求
function provideHover(document, position) {
    if (!document) {
        return null;
    }
    // 获取光标位置的单词
    const word = (0, parser_1.getWordAtPosition)(document, position);
    if (!word) {
        return null;
    }
    // 查找符号
    const symbol = symbols_1.symbols.get(word);
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
//# sourceMappingURL=hover.js.map