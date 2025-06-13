#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

// 解析声明前缀，包括混合的注释、UI注释和注解
std::pair<std::string, std::vector<std::shared_ptr<ast::Annotation>>> Parser::parseDeclarationPrefix() {
    std::vector<std::string> uiComments;
    std::vector<std::shared_ptr<ast::Annotation>> annotations;
    
    while (!isAtEnd()) {
        if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
            advance(); // 跳过普通注释
        } else if (check(lexer::TokenType::UIComment)) {
            // 收集UI注释
            std::string comment = current_.lexeme;
            
            // 去掉//@ 前缀
            if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                comment = comment.substr(3);
                // 去掉前导空格
                while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                    comment = comment.substr(1);
                }
            }
            
            if (!comment.empty()) {
                uiComments.push_back(comment);
            }
            advance();
        } else if (check(lexer::TokenType::At)) {
            // 解析注解
            auto ann = annotation();
            annotations.push_back(ann);
        } else {
            // 遇到其他token，结束前缀解析
            break;
        }
    }
    
    // 合并UI注释
    std::string mergedComment;
    for (size_t i = 0; i < uiComments.size(); ++i) {
        if (i > 0) mergedComment += "\n";
        mergedComment += uiComments[i];
    }
    
    return {mergedComment, annotations};
}

// 仅解析UI注释前缀（用于字段和枚举值）
std::string Parser::parseUICommentsPrefix() {
    std::vector<std::string> uiComments;
    
    while (!isAtEnd()) {
        if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
            advance(); // 跳过普通注释
        } else if (check(lexer::TokenType::UIComment)) {
            // 收集UI注释
            std::string comment = current_.lexeme;
            
            // 去掉//@ 前缀
            if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                comment = comment.substr(3);
                // 去掉前导空格
                while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                    comment = comment.substr(1);
                }
            }
            
            if (!comment.empty()) {
                uiComments.push_back(comment);
            }
            advance();
        } else {
            // 遇到其他token（包括@），结束UI注释解析
            break;
        }
    }
    
    // 合并UI注释
    std::string result;
    for (size_t i = 0; i < uiComments.size(); ++i) {
        if (i > 0) result += "\n";
        result += uiComments[i];
    }
    
    return result;
}

// ===== 声明解析 =====

std::shared_ptr<ast::Node> Parser::declaration() {
    // 解析声明前缀（包括混合的注释、UI注释和注解）
    auto [uiComment, annotations] = parseDeclarationPrefix();
    
    std::shared_ptr<ast::Node> node;
    
    // 根据当前词法单元类型选择解析方法
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
    
    // 设置UI注释到节点
    if (node && !uiComment.empty()) {
        node->ui_comment = uiComment;
    }
    
    // 将注解添加到节点
    if (node) {
        // 根据节点类型添加注解
        if (auto* structNode = dynamic_cast<ast::Struct*>(node.get())) {
            for (auto& ann : annotations) {
                structNode->annotations.push_back(ann);
            }
        } else if (auto* enumNode = dynamic_cast<ast::Enum*>(node.get())) {
            for (auto& ann : annotations) {
                enumNode->annotations.push_back(ann);
            }
        } else if (auto* blockNode = dynamic_cast<ast::Block*>(node.get())) {
            for (auto& ann : annotations) {
                blockNode->annotations.push_back(ann);
            }
        } else if (!annotations.empty()) {
            error(nowToken, "Unexpected annotations");
            return nullptr;
        }
    } else if (!annotations.empty()) {
        error(nowToken, "Unexpected annotations");
        return nullptr;
    }
    
    return node;
}

std::shared_ptr<ast::Annotation> Parser::annotation() {
    auto nowToken = peek();
    
    // 消耗 @ 符号
    if (nowToken.type == lexer::TokenType::At) {
        advance();
    }
    
    // 解析注解名称（标识符或带点的路径）
    std::string name;
    name = consume(lexer::TokenType::Identifier, "Expected annotation name").lexeme;
    
    while (consume(lexer::TokenType::Dot)) {
        name += ".";
        auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
        name += identToken.lexeme;
    }
    
    // 解析注解参数
    std::vector<std::shared_ptr<ast::AnnotationArgument>> args;
    if (consume(lexer::TokenType::LeftParen)) {
        args = annotationArguments();
        consume(lexer::TokenType::RightParen, "Expected ')' after annotation arguments");
    }
    
    return makeNode<ast::Annotation>(name, args);
}

std::vector<std::shared_ptr<ast::AnnotationArgument>> Parser::annotationArguments() {
    std::vector<std::shared_ptr<ast::AnnotationArgument>> args;
    
    if (!check(lexer::TokenType::RightParen)) {
        do {
            auto arg = annotationArgument();
            args.push_back(arg);
        } while (consume(lexer::TokenType::Comma));
    }
    
    return args;
}

std::shared_ptr<ast::AnnotationArgument> Parser::annotationArgument() {
    std::string name;
    std::shared_ptr<ast::Expr> value;
    
    // 解析注解参数，支持以下语法：
    // 1. name = value (命名参数)
    // 2. value (匿名参数，默认为"value"参数)
    // 3. @Annotation (嵌套注解作为参数)
    // 4. [expr1, expr2, ...] (数组字面量)
    
    // 先尝试解析标识符，然后检查是否跟着等号
    if (check(lexer::TokenType::Identifier)) {
        // 保存当前位置，以便回退
        auto identToken = advance();
        
        if (consume(lexer::TokenType::Equal)) {
            // 这是 name = value 的形式
            name = identToken.lexeme;
            // 支持参数为嵌套注解
            if (check(lexer::TokenType::At)) {
                value = annotation();
            } else {
                value = expression();
            }
        } else {
            // 这只是一个值，没有等号，默认为 value 参数
            // 需要将标识符作为表达式处理
            name = "value";
            value = makeNode<ast::Identifier>(identToken.lexeme);
        }
    } else if (check(lexer::TokenType::At)) {
        // 允许匿名嵌套注解作为参数，默认为 value 参数
        name = "value";
        value = annotation();
    } else {
        // 没有指定参数名，默认为 value 参数（支持 @value 注解的简化语法）
        name = "value";
        value = expression();
    }
    return makeNode<ast::AnnotationArgument>(name, value);
}

std::shared_ptr<ast::Struct> Parser::structDeclaration() {
    
    // 解析结构体名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected struct name").lexeme;
    std::string baseName;
    // 解析继承（支持完全限定名）
    if (consume(lexer::TokenType::Colon)) {
        baseName = consume(lexer::TokenType::Identifier, "Expected base block name after ':'").lexeme;
        // 支持带点的基类名称
        while (consume(lexer::TokenType::Dot)) {
            baseName += ".";
            auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
            baseName += identToken.lexeme;
        }
    }
    // 解析结构体体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after struct name");
    
    std::vector<std::shared_ptr<ast::Field>> fields;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 解析字段前缀（包括注释、UI注释和注解）
        std::vector<std::shared_ptr<ast::Annotation>> annotations;
        std::vector<std::string> uiComments;
        
        // 处理混合的注释、UI注释和注解
        while (!isAtEnd()) {
            if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
                advance(); // 跳过普通注释
            } else if (check(lexer::TokenType::UIComment)) {
                // 收集UI注释
                std::string comment = current_.lexeme;
                
                // 去掉//@ 前缀
                if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                    comment = comment.substr(3);
                    // 去掉前导空格
                    while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                        comment = comment.substr(1);
                    }
                }
                
                if (!comment.empty()) {
                    uiComments.push_back(comment);
                }
                advance();
            } else if (check(lexer::TokenType::At)) {
                // 解析注解
                auto ann = annotation();
                annotations.push_back(ann);
            } else {
                // 遇到其他token，开始解析字段
                break;
            }
        }
        
        // 解析字段（不再调用parseUICommentsPrefix，因为已经在这里收集了）
        auto field = fieldDeclarationWithoutUIComment();
        
        // 设置UI注释
        if (!uiComments.empty()) {
            std::string mergedComment;
            for (size_t i = 0; i < uiComments.size(); ++i) {
                if (i > 0) mergedComment += "\n";
                mergedComment += uiComments[i];
            }
            field->ui_comment = mergedComment;
        }
        
        // 将注解添加到字段
        for (auto& ann : annotations) {
            field->annotations.push_back(ann);
        }
        
        fields.push_back(field);
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
    auto structNode = makeNode<ast::Struct>(name, baseName);
    structNode->fields = fields;
    return structNode;
}

std::shared_ptr<ast::Enum> Parser::enumDeclaration() {
    
    // 解析枚举名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected enum name").lexeme;
    
    // 解析枚举体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after enum name");
    
    std::vector<std::shared_ptr<ast::EnumValue>> values;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 解析枚举值前缀（包括注释、UI注释和注解）
        std::vector<std::shared_ptr<ast::Annotation>> annotations;
        std::vector<std::string> uiComments;
        
        // 处理混合的注释、UI注释和注解
        while (!isAtEnd()) {
            if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
                advance(); // 跳过普通注释
            } else if (check(lexer::TokenType::UIComment)) {
                // 收集UI注释
                std::string comment = current_.lexeme;
                
                // 去掉//@ 前缀
                if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                    comment = comment.substr(3);
                    // 去掉前导空格
                    while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                        comment = comment.substr(1);
                    }
                }
                
                if (!comment.empty()) {
                    uiComments.push_back(comment);
                }
                advance();
            } else if (check(lexer::TokenType::At)) {
                // 解析注解
                auto ann = annotation();
                annotations.push_back(ann);
            } else {
                // 遇到其他token，开始解析枚举值
                break;
            }
        }
        
        // 解析枚举值（不再调用parseUICommentsPrefix，因为已经在这里收集了）
        auto value = enumValueDeclarationWithoutUIComment();
        
        // 设置UI注释
        if (!uiComments.empty()) {
            std::string mergedComment;
            for (size_t i = 0; i < uiComments.size(); ++i) {
                if (i > 0) mergedComment += "\n";
                mergedComment += uiComments[i];
            }
            value->ui_comment = mergedComment;
        }
        
        // 将注解添加到枚举值
        for (auto& ann : annotations) {
            value->annotations.push_back(ann);
        }
        
        values.push_back(value);
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
    enumNode->values = values;
    return enumNode;
}

std::shared_ptr<ast::Block> Parser::blockDeclaration() {
    
    // 解析块名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected block name").lexeme;
    std::string baseName;
    // 解析继承（支持完全限定名）
    if (consume(lexer::TokenType::Colon)) {
        baseName = consume(lexer::TokenType::Identifier, "Expected base block name after ':'").lexeme;
        // 支持带点的基类名称
        while (consume(lexer::TokenType::Dot)) {
            baseName += ".";
            auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
            baseName += identToken.lexeme;
        }
    }
    // 解析块体
    consume(lexer::TokenType::LeftBrace, "Expected '{' after block name");
    
    std::vector<std::shared_ptr<ast::Field>> fields;
    
    while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
        // 解析字段前缀（包括注释、UI注释和注解）
        std::vector<std::shared_ptr<ast::Annotation>> annotations;
        std::vector<std::string> uiComments;
        
        // 处理混合的注释、UI注释和注解
        while (!isAtEnd()) {
            if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
                advance(); // 跳过普通注释
            } else if (check(lexer::TokenType::UIComment)) {
                // 收集UI注释
                std::string comment = current_.lexeme;
                
                // 去掉//@ 前缀
                if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                    comment = comment.substr(3);
                    // 去掉前导空格
                    while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                        comment = comment.substr(1);
                    }
                }
                
                if (!comment.empty()) {
                    uiComments.push_back(comment);
                }
                advance();
            } else if (check(lexer::TokenType::At)) {
                // 解析注解
                auto ann = annotation();
                annotations.push_back(ann);
            } else {
                // 遇到其他token，开始解析字段
                break;
            }
        }
        
        // 解析字段（不再调用parseUICommentsPrefix，因为已经在这里收集了）
        auto field = fieldDeclarationWithoutUIComment();
        
        // 设置UI注释
        if (!uiComments.empty()) {
            std::string mergedComment;
            for (size_t i = 0; i < uiComments.size(); ++i) {
                if (i > 0) mergedComment += "\n";
                mergedComment += uiComments[i];
            }
            field->ui_comment = mergedComment;
        }
        
        // 将注解添加到字段
        for (auto& ann : annotations) {
            field->annotations.push_back(ann);
        }
        
        fields.push_back(field);
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
    auto blockNode = makeNode<ast::Block>(name, baseName);
    blockNode->fields = fields;
    return blockNode;
}

std::shared_ptr<ast::AnnotationDecl> Parser::annotationDeclaration() {
    // 解析注解名称（支持带点的命名空间）
    std::string name = consume(lexer::TokenType::Identifier, "Expected annotation name").lexeme;
    while (consume(lexer::TokenType::Dot)) {
        name += ".";
        auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
        name += identToken.lexeme;
    }
    
    // 解析继承（如果有的话）
    std::string baseName;
    if (consume(lexer::TokenType::Colon)) {
        baseName = consume(lexer::TokenType::Identifier, "Expected base annotation name after ':'").lexeme;
        // 支持带点的基注解名称
        while (consume(lexer::TokenType::Dot)) {
            baseName += ".";
            auto identToken = consume(lexer::TokenType::Identifier, "Expected identifier after '.'");
            baseName += identToken.lexeme;
        }
    }
    
    std::vector<std::shared_ptr<ast::Field>> fields;
    
    // 检查是否有注解体或者只是分号结尾
    if (consume(lexer::TokenType::LeftBrace)) {
        // 有注解体，解析字段
        while (!check(lexer::TokenType::RightBrace) && !isAtEnd()) {
            // 解析字段前缀（包括注释、UI注释和注解）
            std::vector<std::shared_ptr<ast::Annotation>> annotations;
            std::vector<std::string> uiComments;
            
            // 处理混合的注释、UI注释和注解
            while (!isAtEnd()) {
                if (check(lexer::TokenType::LineComment) || check(lexer::TokenType::BlockComment)) {
                    advance(); // 跳过普通注释
                } else if (check(lexer::TokenType::UIComment)) {
                    // 收集UI注释
                    std::string comment = current_.lexeme;
                    
                    // 去掉//@ 前缀
                    if (comment.length() > 3 && comment.substr(0, 3) == "//@") {
                        comment = comment.substr(3);
                        // 去掉前导空格
                        while (!comment.empty() && (comment[0] == ' ' || comment[0] == '\t')) {
                            comment = comment.substr(1);
                        }
                    }
                    
                    if (!comment.empty()) {
                        uiComments.push_back(comment);
                    }
                    advance();
                } else if (check(lexer::TokenType::At)) {
                    // 解析注解
                    auto ann = annotation();
                    annotations.push_back(ann);
                } else {
                    // 遇到其他token，开始解析字段
                    break;
                }
            }
            
            // 解析字段（不再调用parseUICommentsPrefix，因为已经在这里收集了）
            auto field = fieldDeclarationWithoutUIComment();
            
            // 设置UI注释
            if (!uiComments.empty()) {
                std::string mergedComment;
                for (size_t i = 0; i < uiComments.size(); ++i) {
                    if (i > 0) mergedComment += "\n";
                    mergedComment += uiComments[i];
                }
                field->ui_comment = mergedComment;
            }
            
            // 将注解添加到字段
            for (auto& ann : annotations) {
                field->annotations.push_back(ann);
            }
            
            fields.push_back(field);
        }
        // 如果到达文件末尾但没有右大括号，抛出异常
        if (isAtEnd()) {
            error(previous_, "Expected '}' after annotation body but reached end of file");
        }
        consume(lexer::TokenType::RightBrace, "Expected '}' after annotation body");
    } else {
        // 没有注解体，期望分号结尾
        consume(lexer::TokenType::Semicolon, "Expected ';' after annotation declaration");
    }
    
    // 创建 AnnotationDecl 对象，传入继承的基注解名称
    auto annotationNode = makeNode<ast::AnnotationDecl>(name, baseName);
    annotationNode->fields = fields;
    return annotationNode;
}

std::shared_ptr<ast::Field> Parser::fieldDeclaration() {
    // 收集前置的UI注释（字段的注解在调用方处理）
    std::string uiComment = parseUICommentsPrefix();
    
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
    std::shared_ptr<ast::Expr> initializer = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        initializer = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after field declaration");
    
    // 调整参数顺序为 name, type, initializer
    auto field = makeNode<ast::Field>(name, type, initializer);
    
    // 设置UI注释
    if (!uiComment.empty()) {
        field->ui_comment = uiComment;
    }
    
    return field;
}

std::shared_ptr<ast::Field> Parser::fieldDeclarationWithoutUIComment() {
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
    std::shared_ptr<ast::Expr> initializer = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        initializer = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after field declaration");
    
    // 调整参数顺序为 name, type, initializer
    auto field = makeNode<ast::Field>(name, type, initializer);
    
    return field;
}

std::shared_ptr<ast::EnumValue> Parser::enumValueDeclaration() {
    // 收集前置的UI注释（枚举值的注解在调用方处理）
    std::string uiComment = parseUICommentsPrefix();
    
    // 解析枚举值名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected enum value name").lexeme;
    
    // 解析枚举值
    std::shared_ptr<ast::Expr> value = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        value = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after enum value");
    
    auto enumValue = makeNode<ast::EnumValue>(name, value);
    
    // 设置UI注释
    if (!uiComment.empty()) {
        enumValue->ui_comment = uiComment;
    }
    
    return enumValue;
}

std::shared_ptr<ast::EnumValue> Parser::enumValueDeclarationWithoutUIComment() {
    // 解析枚举值名称
    std::string name = consume(lexer::TokenType::Identifier, "Expected enum value name").lexeme;
    
    // 解析枚举值
    std::shared_ptr<ast::Expr> value = nullptr;
    if (consume(lexer::TokenType::Equal)) {
        value = expression();
    }
    
    consume(lexer::TokenType::Semicolon, "Expected ';' after enum value");
    
    auto enumValue = makeNode<ast::EnumValue>(name, value);
    
    return enumValue;
}

std::shared_ptr<ast::Include> Parser::includeDeclaration() {
    
    // 解析包含路径
    auto path = consume(lexer::TokenType::String, "Expected string after 'include'");
    consume(lexer::TokenType::Semicolon, "Expected ';' after include statement");
    
    return makeNode<ast::Include>(path.lexeme);
}

std::shared_ptr<ast::Namespace> Parser::namespaceDeclaration() {
    
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
    
    return makeNode<ast::Namespace>(pathParts);
}

} // namespace parser
} // namespace mota
