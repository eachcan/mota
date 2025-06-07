"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.provideDefinition = provideDefinition;
exports.provideReferences = provideReferences;
const parser_1 = require("./parser");
const symbols_1 = require("./symbols");
// 处理跳转到定义请求
function provideDefinition(document, params) {
    if (!document) {
        return null;
    }
    // 获取光标位置的单词
    const word = (0, parser_1.getWordAtPosition)(document, params.position);
    if (!word) {
        return null;
    }
    // 查找符号
    const symbol = symbols_1.symbols.get(word);
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
function provideReferences(document, params) {
    if (!document) {
        return [];
    }
    // 获取光标位置的单词
    const word = (0, parser_1.getWordAtPosition)(document, params.position);
    if (!word) {
        return [];
    }
    // 查找符号
    const symbol = symbols_1.symbols.get(word);
    if (!symbol) {
        return [];
    }
    // 如果包含声明，添加声明位置
    const locations = [];
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
//# sourceMappingURL=definitions.js.map