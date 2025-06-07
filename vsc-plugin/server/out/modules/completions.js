"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.provideCompletions = provideCompletions;
exports.resolveCompletion = resolveCompletion;
exports.createCompletionItem = createCompletionItem;
const node_1 = require("vscode-languageserver/node");
const symbols_1 = require("./symbols");
// 处理代码补全请求
function provideCompletions(document, position) {
    if (!document) {
        return [];
    }
    const text = document.getText();
    const line = text.split(/\r?\n/)[position.position.line];
    const linePrefix = line.substring(0, position.position.character);
    // 提供不同上下文的补全项
    const completionItems = [];
    // 1. 注解补全（在 @ 后）
    if (linePrefix.trimRight().endsWith('@')) {
        // 从符号表中获取所有注解
        const annotations = (0, symbols_1.getAllAnnotations)();
        for (const annotation of annotations) {
            completionItems.push(createCompletionItem(annotation.name, node_1.CompletionItemKind.Class, annotation.description || `${annotation.name}注解`));
        }
        // 如果没有找到注解，提供一些默认的注解
        if (completionItems.length === 0) {
            completionItems.push(createCompletionItem('Storage', node_1.CompletionItemKind.Class, '存储配置注解'), createCompletionItem('Window', node_1.CompletionItemKind.Class, '窗口配置注解'), createCompletionItem('Scope', node_1.CompletionItemKind.Class, '作用域注解'));
        }
    }
    // 2. 类型补全（在字段定义中）
    if (/\s+\w+$/.test(linePrefix)) {
        // 添加基本类型
        completionItems.push(createCompletionItem('int8', node_1.CompletionItemKind.Keyword, '8位整数类型'), createCompletionItem('int16', node_1.CompletionItemKind.Keyword, '16位整数类型'), createCompletionItem('int32', node_1.CompletionItemKind.Keyword, '32位整数类型'), createCompletionItem('int64', node_1.CompletionItemKind.Keyword, '64位整数类型'), createCompletionItem('float32', node_1.CompletionItemKind.Keyword, '32位浮点数类型'), createCompletionItem('float64', node_1.CompletionItemKind.Keyword, '64位浮点数类型'), createCompletionItem('string', node_1.CompletionItemKind.Keyword, '字符串类型'), createCompletionItem('bytes', node_1.CompletionItemKind.Keyword, '二进制数据类型'), createCompletionItem('bool', node_1.CompletionItemKind.Keyword, '布尔类型'), createCompletionItem('optional', node_1.CompletionItemKind.Keyword, '可选类型修饰符'), createCompletionItem('repeated', node_1.CompletionItemKind.Keyword, '数组类型修饰符'), createCompletionItem('map', node_1.CompletionItemKind.Keyword, '映射类型'));
        // 添加自定义类型（从符号表中获取）
        const customTypes = [
            ...(0, symbols_1.getSymbolsByKind)('enum'),
            ...(0, symbols_1.getSymbolsByKind)('struct'),
            ...(0, symbols_1.getSymbolsByKind)('block')
        ];
        for (const symbol of customTypes) {
            completionItems.push(createCompletionItem(symbol.name, node_1.CompletionItemKind.Class, `自定义${symbol.kind}类型`));
        }
    }
    // 3. 关键字补全
    if (linePrefix.trim() === '' || /^\s*\w*$/.test(linePrefix)) {
        completionItems.push(createCompletionItem('namespace', node_1.CompletionItemKind.Keyword, '命名空间定义'), createCompletionItem('include', node_1.CompletionItemKind.Keyword, '引入其他文件'), createCompletionItem('enum', node_1.CompletionItemKind.Keyword, '枚举类型定义'), createCompletionItem('struct', node_1.CompletionItemKind.Keyword, '结构体定义'), createCompletionItem('block', node_1.CompletionItemKind.Keyword, '块定义'), createCompletionItem('annotation', node_1.CompletionItemKind.Keyword, '注解定义'));
    }
    // 4. 注解参数补全（在注解内部）
    const annotationParamRegex = /@(\w+(?:\.\w+)*)\s*\(([^)]*)$/;
    const match = linePrefix.match(annotationParamRegex);
    if (match) {
        const annotationName = match[1];
        // 查找注解定义
        const annotations = (0, symbols_1.getAllAnnotations)();
        const annotation = annotations.find(a => a.name === annotationName);
        if (annotation && annotation.parameters) {
            // 根据注解定义提供参数补全
            for (const param of annotation.parameters) {
                completionItems.push(createCompletionItem(`${param} = `, node_1.CompletionItemKind.Property, `${annotationName}的${param}参数`));
            }
        }
        else {
            // 如果找不到注解定义，提供一些常见参数
            switch (annotationName) {
                case 'Storage':
                    completionItems.push(createCompletionItem('path = ""', node_1.CompletionItemKind.Property, '存储路径'), createCompletionItem('format = ""', node_1.CompletionItemKind.Property, '存储格式'));
                    break;
                case 'Window':
                    completionItems.push(createCompletionItem('title = ""', node_1.CompletionItemKind.Property, '窗口标题'), createCompletionItem('desc = ""', node_1.CompletionItemKind.Property, '窗口描述'));
                    break;
                case 'Scope':
                    completionItems.push(createCompletionItem('value = ""', node_1.CompletionItemKind.Property, '作用域值'));
                    break;
                case 'Int':
                case 'Float':
                    completionItems.push(createCompletionItem('min = ', node_1.CompletionItemKind.Property, '最小值'), createCompletionItem('max = ', node_1.CompletionItemKind.Property, '最大值'), createCompletionItem('step = ', node_1.CompletionItemKind.Property, '步长'), createCompletionItem('desc = ""', node_1.CompletionItemKind.Property, '描述'));
                    break;
                case 'Text':
                    completionItems.push(createCompletionItem('max_length = ', node_1.CompletionItemKind.Property, '最大长度'), createCompletionItem('desc = ""', node_1.CompletionItemKind.Property, '描述'), createCompletionItem('pattern = ""', node_1.CompletionItemKind.Property, '正则表达式'));
                    break;
                default:
                    completionItems.push(createCompletionItem('desc = ""', node_1.CompletionItemKind.Property, '描述'));
                    break;
            }
        }
    }
    return completionItems;
}
// 处理代码补全项解析
function resolveCompletion(item) {
    // 可以在这里添加更多的文档信息
    return item;
}
// 创建补全项辅助函数
function createCompletionItem(label, kind, detail) {
    return {
        label,
        kind,
        detail,
        data: { label }
    };
}
//# sourceMappingURL=completions.js.map