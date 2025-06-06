#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

// ===== 类型解析 =====

std::unique_ptr<ast::Type> Parser::parseType() {
    std::cout << "parseType() 开始解析，当前token: " << peek().lexeme << ", 类型: " << static_cast<int>(peek().type) << std::endl;
    
    return containerType();
}

std::unique_ptr<ast::Type> Parser::primaryType() {
    std::cout << "primaryType() 开始解析，当前token: " << peek().lexeme << ", 类型: " << static_cast<int>(peek().type) << std::endl;
    // 允许 identifier 作为类型（包括注解名）
    bool isIdent = check(lexer::TokenType::Identifier);
    std::cout << "primaryType() check(Identifier) 结果: " << (isIdent ? "true" : "false") << std::endl;
    if (isIdent) {
        auto ident = advance();
        std::cout << "primaryType() 成功解析identifier类型: " << ident.lexeme << std::endl;
        return makeNode<ast::NamedType>(ident.lexeme);
    }
    
    // 解析基本类型
    auto token = advance();
    std::cout << "primaryType() 尝试解析基本类型，token: " << token.lexeme << ", 类型: " << static_cast<int>(token.type) << std::endl;
    
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
            std::cout << "primaryType() 成功解析基本类型: " << token.lexeme << std::endl;
            return makeNode<ast::NamedType>(token.lexeme);
        default:
            // 无效类型
            std::cout << "primaryType() 无效类型，准备抛出异常" << std::endl;
            error(token, "Expected type");
            throw ParseError("Expected type", token.line, token.column);
    }
}

std::unique_ptr<ast::Type> Parser::containerType() {
    std::cout << "containerType() 开始解析，当前token: " << peek().lexeme << ", 类型: " << static_cast<int>(peek().type) << std::endl;
    
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
