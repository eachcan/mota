#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

// ===== 声明解析 =====

std::unique_ptr<ast::Node> Parser::declaration() {
    // 跳过注释 token
    while (check(lexer::TokenType::LineComment) ||
           check(lexer::TokenType::BlockComment) ||
           check(lexer::TokenType::UIComment)) {
        advance();
    }
    auto firstToken = peek();
    std::cout << "declaration() 开始解析，当前token: " << firstToken.lexeme << ", 类型: " << static_cast<int>(firstToken.type) << std::endl;
    
    std::unique_ptr<ast::Node> node;
    
    // 处理注解
    std::vector<std::unique_ptr<ast::Annotation>> annotations;
    while (check(lexer::TokenType::At)) {
        // 不捕获异常，让异常传递给测试用例
        std::cout << "declaration() 开始解析注解" << std::endl;
        auto ann = annotation();
        std::cout << "declaration() 解析到注解: " << ann->name << std::endl;
        annotations.push_back(std::move(ann));
    }
    
    // 根据当前词法单元类型选择解析方法
    // 不捕获异常，让异常传播到测试函数中
    auto nowToken = peek();
    if (consume(lexer::TokenType::Struct)) {
        node = structDeclaration();
    } else if (consume(lexer::TokenType::Enum)) {
        node = enumDeclaration();
    } else if (consume(lexer::TokenType::Block)) {
        node = blockDeclaration();
    } else if (consume(lexer::TokenType::Annotation)) {
        node = annotationDeclaration();
    } else if (consume(lexer::TokenType::Include)) {
        node = includeDeclaration();
    } else if (consume(lexer::TokenType::Namespace)) {
        node = namespaceDeclaration();
    } else {
        error(nowToken, "Expected declaration");
        return nullptr;
    }
    
    // 将注解添加到节点
    if (node) {
        // 根据节点类型添加注解
        if (auto* structNode = dynamic_cast<ast::Struct*>(node.get())) {
            for (auto& ann : annotations) {
                structNode->annotations.push_back(std::move(ann));
            }
        } else if (auto* enumNode = dynamic_cast<ast::Enum*>(node.get())) {
            for (auto& ann : annotations) {
                enumNode->annotations.push_back(std::move(ann));
            }
        } else if (auto* blockNode = dynamic_cast<ast::Block*>(node.get())) {
            for (auto& ann : annotations) {
                blockNode->annotations.push_back(std::move(ann));
            }
        } else if (!annotations.empty()) {
            error(nowToken, "Unexpected annotations");
            return nullptr;
        }
    } else {
        error(nowToken, "Unexpected annotations");
        return nullptr;
    }
    
    return node;
}

std::unique_ptr<ast::Annotation> Parser::annotation() {
    auto nowToken = peek();
    std::cout << "annotation() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 消耗 @ 符号
    if (nowToken.type == lexer::TokenType::At) {
        advance();
        std::cout << "annotation() 消耗了 @ 符号" << std::endl;
    }
    
    // 解析注解名称（标识符或带点的路径）
    std::string name;
    name = consume(lexer::TokenType::Identifier, "Expected annotation name").lexeme;
    std::cout << "annotation() 解析到注解名称的第一部分: " << name << std::endl;
    
    while (consume(lexer::TokenType::Dot)) {
        name += ".";
        auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
        name += identToken.lexeme;
        std::cout << "annotation() 解析到注解名称的下一部分: " << identToken.lexeme << ", 当前完整名称: " << name << std::endl;
    }
    
    // 解析注解参数
    std::vector<ast::AnnotationArgument> args;
    if (consume(lexer::TokenType::LeftParen)) {
        args = annotationArguments();
        consume(lexer::TokenType::RightParen, "Expected ')' after annotation arguments");
    }
    
    return makeNode<ast::Annotation>(name, std::move(args));
}

std::vector<ast::AnnotationArgument> Parser::annotationArguments() {
    auto nowToken = peek();
    std::cout << "annotationArguments() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    std::vector<ast::AnnotationArgument> args;
    
    if (!check(lexer::TokenType::RightParen)) {
        do {
            auto arg = annotationArgument();
            std::cout << "annotationArguments() 解析到一个参数: " << arg.name << " = [value]" << std::endl;
            args.push_back(std::move(arg));
        } while (consume(lexer::TokenType::Comma));
    }
    
    std::cout << "annotationArguments() 共解析到 " << args.size() << " 个参数" << std::endl;
    return args;
}

ast::AnnotationArgument Parser::annotationArgument() {
    auto nowToken = peek();
    std::cout << "annotationArgument() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    std::string name;
    std::unique_ptr<ast::Expr> value;
    if (check(lexer::TokenType::Identifier)) {
        name = advance().lexeme;
        consume(lexer::TokenType::Equal, "Expected '=' after annotation argument name");
        // 支持参数为嵌套注解
        if (check(lexer::TokenType::At)) {
            value = annotation();
        } else {
            value = expression();
        }
    } else if (check(lexer::TokenType::At)) {
        // 允许匿名嵌套注解作为参数
        name = "value";
        value = annotation();
    } else {
        name = "value";
        value = expression();
    }
    std::cout << "annotationArgument() 解析到参数名称: " << name << std::endl;
    return ast::AnnotationArgument{name, std::move(value)};
}

std::unique_ptr<ast::Struct> Parser::structDeclaration() {
    auto nowToken = peek();
    std::cout << "structDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析结构体名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected struct name").lexeme;
    
    // 解析结构体体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after struct name");
    
    std::vector<std::unique_ptr<ast::Field>> fields;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 处理字段前的注解
        std::vector<std::unique_ptr<ast::Annotation>> annotations;
        while (consume(lexer::TokenType::At)) {
            annotations.push_back(annotation());
        }
        
        // 解析字段
        auto field = fieldDeclaration();
        
        // 将注解添加到字段
        for (auto& ann : annotations) {
            field->annotations.push_back(std::move(ann));
        }
        
        fields.push_back(std::move(field));
    }
    
    // 检查是否有右大括号，如果没有则抛出异常
    if (!check(lexer::TokenType::RightBrace)) {
        auto token = previous_;
        std::string errorMsg = "Expected '}' (right brace) after struct body";
        if (isAtEnd()) {
            errorMsg += " but reached end of file";
        }
        // error 函数会抛出异常，下面的代码不会执行
        error(token, errorMsg);
    }
    
    // 消耗右大括号
    consume(lexer::TokenType::RightBrace, "Expected '}' (right brace) after struct body");
    
    // 先创建 Struct 对象，然后再添加字段
    auto structNode = makeNode<ast::Struct>(name);
    structNode->fields = std::move(fields);
    return structNode;
}

std::unique_ptr<ast::Enum> Parser::enumDeclaration() {
    auto nowToken = peek();
    std::cout << "enumDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析枚举名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected enum name").lexeme;
    
    // 解析枚举体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after enum name");
    
    std::vector<std::unique_ptr<ast::EnumValue>> values;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 处理枚举值前的注解
        std::vector<std::unique_ptr<ast::Annotation>> annotations;
        while (consume(lexer::TokenType::At)) {
            annotations.push_back(annotation());
        }
        
        // 解析枚举值
        auto value = enumValueDeclaration();
        
        // 将注解添加到枚举值
        for (auto& ann : annotations) {
            value->annotations.push_back(std::move(ann));
        }
        
        values.push_back(std::move(value));
    }
    
    // 检查是否有右大括号，如果没有则抛出异常
    if (!check(lexer::TokenType::RightBrace)) {
        auto token = previous_;
        std::string errorMsg = "Expected '}' after enum body";
        if (isAtEnd()) {
            errorMsg += " but reached end of file";
        }
        // error 函数会抛出异常，下面的代码不会执行
        error(token, errorMsg);
    }
    
    // 消耗右大括号
    consume(lexer::TokenType::RightBrace, "Expected '}' after enum body");
    
    // 先创建 Enum 对象，然后再添加枚举值
    auto enumNode = makeNode<ast::Enum>(name);
    enumNode->values = std::move(values);
    return enumNode;
}

std::unique_ptr<ast::Block> Parser::blockDeclaration() {
    auto nowToken = peek();
    std::cout << "blockDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析块名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected block name").lexeme;
    
    // 解析块体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after block name");
    
    std::vector<std::unique_ptr<ast::Field>> fields;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 处理字段前的注解
        std::vector<std::unique_ptr<ast::Annotation>> annotations;
        while (consume(lexer::TokenType::At)) {
            annotations.push_back(annotation());
        }
        
        // 解析字段
        auto field = fieldDeclaration();
        
        // 将注解添加到字段
        for (auto& ann : annotations) {
            field->annotations.push_back(std::move(ann));
        }
        
        fields.push_back(std::move(field));
    }
    
    // 如果到达文件末尾但没有右大括号，抛出异常
    if (isAtEnd()) {
        auto token = previous_;
        // error 函数会抛出异常，下面的代码不会执行
        error(token, "Expected '}' after block body but reached end of file");
    }
    
    // 这里会在缺少右大括号时抛出异常
    consume(lexer::TokenType::RightBrace, "Expected '}' after block body");
    
    // 先创建 Block 对象，然后再添加字段
    auto blockNode = makeNode<ast::Block>(name);
    blockNode->fields = std::move(fields);
    return blockNode;
}

std::unique_ptr<ast::Annotation> Parser::annotationDeclaration() {
    auto nowToken = peek();
    std::cout << "annotationDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    // 解析注解名称（支持带点的命名空间）
    std::string name = consume(lexer::TokenType::Identifier, "Expected annotation name").lexeme;
    while (consume(lexer::TokenType::Dot)) {
        name += ".";
        auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
        name += identToken.lexeme;
    }
    // 解析注解体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after annotation name");
    std::vector<std::unique_ptr<ast::Field>> fields;
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 处理字段前的注解
        std::vector<std::unique_ptr<ast::Annotation>> annotations;
        while (consume(lexer::TokenType::At)) {
            annotations.push_back(annotation());
        }
        // 解析字段
        auto field = fieldDeclaration();
        // 将注解添加到字段
        for (auto& ann : annotations) {
            field->annotations.push_back(std::move(ann));
        }
        fields.push_back(std::move(field));
    }
    // 如果到达文件末尾但没有右大括号，抛出异常
    if (isAtEnd()) {
        error(previous_, "Expected '}' after annotation body but reached end of file");
    }
    consume(lexer::TokenType::RightBrace, "Expected '}' after annotation body");
    // 创建 Annotation 对象
    auto annotationNode = makeNode<ast::Annotation>(name);
    // TODO: 需要在 AST 结构中为 annotation 存储 fields
    return annotationNode;
}

std::unique_ptr<ast::Field> Parser::fieldDeclaration() {
    // 解析类型
    if (!check(lexer::TokenType::Identifier) &&
        !check(lexer::TokenType::Int8) && !check(lexer::TokenType::Int16) && !check(lexer::TokenType::Int32) && !check(lexer::TokenType::Int64) &&
        !check(lexer::TokenType::Float32) && !check(lexer::TokenType::Float64) &&
        !check(lexer::TokenType::StringType) && !check(lexer::TokenType::Bytes) && !check(lexer::TokenType::Bool) &&
        !check(lexer::TokenType::Repeated) && !check(lexer::TokenType::Map) && !check(lexer::TokenType::Optional)) {
        error(peek(), "Expected type");
    }
    auto type = parseType();
    // 解析字段名
    std::string name = consume(lexer::TokenType::Identifier, "Expected field name").lexeme;
    
    // 解析可选的初始值
    std::unique_ptr<ast::Expr> initializer = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        initializer = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after field declaration");
    
    // 调整参数顺序为 name, type, initializer
    return makeNode<ast::Field>(name, std::move(type), std::move(initializer));
}

std::unique_ptr<ast::EnumValue> Parser::enumValueDeclaration() {
    auto nowToken = peek();
    std::cout << "enumValueDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析枚举值名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected enum value name").lexeme;
    
    // 解析枚举值
    std::unique_ptr<ast::Expr> value = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        value = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after enum value");
    
    return makeNode<ast::EnumValue>(name, std::move(value));
}

std::unique_ptr<ast::Include> Parser::includeDeclaration() {
    auto nowToken = peek();
    std::cout << "includeDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析包含路径
    auto path = consume(lexer::TokenType::String, "Expected string after 'include'");
    consume(lexer::TokenType::Semicolon, "Expected ';' after include statement");
    
    return makeNode<ast::Include>(path.lexeme);
}

std::unique_ptr<ast::Namespace> Parser::namespaceDeclaration() {
    auto nowToken = peek();
    std::cout << "namespaceDeclaration() 开始解析，当前token: " << nowToken.lexeme << ", 类型: " << static_cast<int>(nowToken.type) << std::endl;
    
    // 解析命名空间路径
    std::string fullPath;
    fullPath = consume(lexer::TokenType::Identifier, "Expected namespace name").lexeme;
    
    while (consume(lexer::TokenType::Dot)) {
        fullPath += ".";
        fullPath += consume(lexer::TokenType::Identifier, "Expected identifier after '.'").lexeme;
    }
    
    // 检查是否缺少分号
    if (!check(lexer::TokenType::Semicolon)) {
        // error 函数会抛出异常，下面的代码不会执行
        error(previous_, "Expected ';' after namespace declaration");
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after namespace declaration");
    
    // 将完整路径分割成字符串向量
    std::vector<std::string> pathParts;
    size_t start = 0;
    size_t end = fullPath.find('.');
    
    while (end != std::string::npos) {
        pathParts.push_back(fullPath.substr(start, end - start));
        start = end + 1;
        end = fullPath.find('.', start);
    }
    
    // 添加最后一部分
    pathParts.push_back(fullPath.substr(start));
    
    return makeNode<ast::Namespace>(std::move(pathParts));
}

} // namespace parser
} // namespace mota
