"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.prepareRename = prepareRename;
exports.performRename = performRename;
const parser_1 = require("./parser");
const symbols_1 = require("./symbols");
// 处理准备重命名请求
function prepareRename(document, params) {
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
    // 获取单词范围
    const range = (0, parser_1.getWordRangeAtPosition)(document, params.position);
    if (!range) {
        return null;
    }
    // 返回可重命名的范围
    return {
        range: range,
        placeholder: word
    };
}
// 处理重命名请求
function performRename(document, params) {
    if (!document) {
        return { changes: {} };
    }
    // 获取光标位置的单词
    const word = (0, parser_1.getWordAtPosition)(document, params.position);
    if (!word) {
        return { changes: {} };
    }
    // 查找符号
    const symbol = symbols_1.symbols.get(word);
    if (!symbol) {
        return { changes: {} };
    }
    // 创建工作区编辑
    const changes = {};
    // 添加定义的编辑
    if (!changes[symbol.uri]) {
        changes[symbol.uri] = [];
    }
    changes[symbol.uri].push({
        range: symbol.range,
        newText: params.newName
    });
    // 添加所有引用的编辑
    for (const reference of symbol.references) {
        if (!changes[reference.uri]) {
            changes[reference.uri] = [];
        }
        changes[reference.uri].push({
            range: reference.range,
            newText: params.newName
        });
    }
    return { changes };
}
//# sourceMappingURL=rename.js.map