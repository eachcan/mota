"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.symbols = void 0;
exports.addSymbol = addSymbol;
exports.addReference = addReference;
exports.clearSymbolsForDocument = clearSymbolsForDocument;
exports.getAllAnnotations = getAllAnnotations;
exports.getSymbolsByKind = getSymbolsByKind;
exports.getFullName = getFullName;
// 存储所有文档中的符号
exports.symbols = new Map();
// 添加符号定义
function addSymbol(name, kind, uri, range, parameters, description) {
    const symbol = {
        name,
        kind,
        uri,
        range,
        references: [],
        parameters,
        description
    };
    exports.symbols.set(name, symbol);
}
// 添加符号引用
function addReference(name, uri, range) {
    const symbol = exports.symbols.get(name);
    if (symbol) {
        symbol.references.push({
            uri,
            range
        });
    }
}
// 清除指定文档中的所有符号
function clearSymbolsForDocument(uri) {
    for (const [key, symbol] of exports.symbols.entries()) {
        if (symbol.uri === uri) {
            exports.symbols.delete(key);
        }
        else {
            // 移除引用中属于该文档的引用
            symbol.references = symbol.references.filter(ref => ref.uri !== uri);
        }
    }
}
// 获取所有注解符号
function getAllAnnotations() {
    const annotations = [];
    for (const symbol of exports.symbols.values()) {
        if (symbol.kind === 'annotation') {
            annotations.push(symbol);
        }
    }
    return annotations;
}
// 获取指定类型的所有符号
function getSymbolsByKind(kind) {
    const result = [];
    for (const symbol of exports.symbols.values()) {
        if (symbol.kind === kind) {
            result.push(symbol);
        }
    }
    return result;
}
// 获取符号的完整名称（包含命名空间）
function getFullName(name, namespace) {
    return namespace ? `${namespace}.${name}` : name;
}
//# sourceMappingURL=symbols.js.map