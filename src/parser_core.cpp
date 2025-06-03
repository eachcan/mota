#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

std::unique_ptr<ast::Document> Parser::parse() {
    std::cout << "Parser::parse()" << std::endl;
    
    // 创建文档节点
    auto document = std::make_unique<ast::Document>();
    
    // 消耗第一个词法单元
    current_ = lexer_.nextToken();
    
    // 解析所有声明
    while (!isAtEnd()) {
        // 不在这里捕获异常，让它们传播到测试函数中
        // 这样测试可以验证是否正确抛出了异常
        auto decl = declaration();
        
        if (decl) {
            std::cout << "声明解析成功，添加到文档: token类型 = " << static_cast<int>(current_.type) 
                      << ", 是否结束 = " << (isAtEnd() ? "true" : "false") << std::endl;
            document->declarations.push_back(std::move(decl));
        } else {
            std::cout << "声明解析失败，跳过..." << std::endl;
            throw ParseError("Declaration expected", current_.line, current_.column);
            break;
        }
    }
    
    return document;
}

// ===== 辅助方法 =====

lexer::Token Parser::advance() {
    previous_ = current_;
    
    if (!isAtEnd()) {
        current_ = lexer_.nextToken();
    }
    
    return previous_;
}

lexer::Token Parser::peek() const {
    return current_;
}

lexer::Token Parser::peekNext() const {
    // 获取下一个词法单元
    lexer::Token nextToken = lexer_.nextToken();
    return nextToken;
}

bool Parser::check(lexer::TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::consume(lexer::TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

bool Parser::isAtEnd() const {
    return current_.type == lexer::TokenType::Eof;
}

lexer::Token Parser::consume(lexer::TokenType type, const std::string& message) {
    if (check(type)) return advance();
    
    // 直接调用 error 方法，它会抛出异常
    error(peek(), message);
    
    // 这行代码永远不会执行，因为 error 会抛出异常
    return peek();
}

ParseError Parser::error(const lexer::Token& token, const std::string& message) {
    hadError_ = true;
    // 打印调试信息
    std::cout << "\n抛出异常: " << message << " at line " << token.line << ", column " << token.column << std::endl;
    // 创建并直接抛出异常
    throw ParseError(message, token.line, token.column);
}

void Parser::synchronize() {
    panicMode_ = true;
    
    advance();
    
    while (!isAtEnd()) {
        if (previous_.type == lexer::TokenType::Semicolon) return;
        
        switch (current_.type) {
            case lexer::TokenType::Struct:
            case lexer::TokenType::Enum:
            case lexer::TokenType::Block:
            case lexer::TokenType::Annotation:
            case lexer::TokenType::Include:
            case lexer::TokenType::Namespace:
                return;
            default:
                break;
        }
        
        advance();
    }
}

} // namespace parser
} // namespace mota
