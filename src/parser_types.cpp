#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

// ===== 类型解析 =====

std::unique_ptr<ast::Type> Parser::parseType() {
    return containerType();
}

std::unique_ptr<ast::Type> Parser::primaryType() {
    // 处理容器类型（允许嵌套）
    if (check(lexer::TokenType::Optional) || check(lexer::TokenType::Repeated) || check(lexer::TokenType::Map)) {
        return containerType();
    }
    
    // 允许 identifier 作为类型（包括注解名）
    if (check(lexer::TokenType::Identifier)) {
        auto ident = advance();
        return makeNode<ast::NamedType>(ident.lexeme);
    }
    
    // 解析基本类型
    auto token = advance();
    
    switch (token.type) {
        case lexer::TokenType::Int8:
        case lexer::TokenType::Int16:
        case lexer::TokenType::Int32:
        case lexer::TokenType::Int64:
        case lexer::TokenType::Float32:
        case lexer::TokenType::Float64:
        case lexer::TokenType::Bool:
        case lexer::TokenType::StringType:
        case lexer::TokenType::Bytes:
    
            return makeNode<ast::NamedType>(token.lexeme);
        default:
            // 无效类型
            std::cout << "primaryType() 无效类型，准备抛出异常" << std::endl;
            error(token, "Expected type");
            throw ParseError("Expected type", token.line, token.column);
    }
}

std::unique_ptr<ast::Type> Parser::containerType() {
    
    if (consume(lexer::TokenType::Optional)) {
        // 解析可选类型
        auto valueType = primaryType();
        return makeNode<ast::ContainerType>(ast::ContainerType::Kind::Optional, std::move(valueType));
    } else if (consume(lexer::TokenType::Repeated)) {
        // 解析数组类型
        auto elementType = primaryType();
        return makeNode<ast::ContainerType>(ast::ContainerType::Kind::Array, std::move(elementType));
    } else if (consume(lexer::TokenType::Map)) {
        // 解析映射类型
        // 根据 Mota 语法文档，map 类型的语法是 map ValueType fieldName
        // 键类型固定为 string
        
        // 解析值类型
        auto valueType = primaryType();
        
        // 创建一个 Map 类型的 ContainerType
        auto containerType = makeNode<ast::ContainerType>(ast::ContainerType::Kind::Map, std::move(valueType));
        
        // 设置键类型为 string
        auto keyType = makeNode<ast::NamedType>("string");
        containerType->keyType = std::move(keyType);
        
        return containerType;
    } else {
        // 解析基本类型或用户定义类型
        return primaryType();
    }
}

} // namespace parser
} // namespace mota
