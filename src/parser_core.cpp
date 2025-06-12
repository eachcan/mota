#include "parser.h"
#include <iostream>

namespace mota {
namespace parser {

std::shared_ptr<ast::Document> Parser::parse() {
    // 创建文档节点
    auto document = std::make_shared<ast::Document>();
    
    // 消耗第一个词法单元
    current_ = lexer_.nextToken();
    
    // 跳过开头的注释
    while (!isAtEnd() && (current_.type == lexer::TokenType::LineComment || 
                          current_.type == lexer::TokenType::BlockComment ||
                          current_.type == lexer::TokenType::UIComment)) {
        current_ = lexer_.nextToken();
    }
    
    bool hasDeclaration = false;
    // 解析所有声明
    while (!isAtEnd()) {
        auto decl = declaration();
        if (decl) {
            // 根据声明类型分别处理
            switch (decl->nodeType()) {
                case ast::NodeType::IncludeDecl: {
                    if (hasDeclaration) {
                        throw ParseError("Include declaration must appear before entity declarations", 
                                       current_.line, current_.column);
                    }
                    // include声明放入includes数组
                    auto includeDecl = std::static_pointer_cast<ast::Include>(decl);
                    document->includes.push_back(includeDecl);
                    break;
                }
                case ast::NodeType::NamespaceDecl: {
                    // namespace声明设置到m_namespace（只能有一个）
                    if (document->hasNamespace()) {
                        throw ParseError("Multiple namespace declarations in one file", 
                                       current_.line, current_.column);
                    }
                    if (hasDeclaration) {
                        throw ParseError("Namespace declaration must be the first declaration in the file", 
                                       current_.line, current_.column);
                    }
                    auto namespaceDecl = std::static_pointer_cast<ast::Namespace>(decl);
                    document->m_namespace = namespaceDecl;
                    break;
                }
                default: {
                    // 其他声明（struct、block、enum、annotation）放入declarations
                    document->declarations.push_back(decl);
                    hasDeclaration = true;
                    break;
                }
            }
        } else {
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
        
        // 自动跳过注释
        while (!isAtEnd() && (current_.type == lexer::TokenType::LineComment || 
                              current_.type == lexer::TokenType::BlockComment ||
                              current_.type == lexer::TokenType::UIComment)) {
            current_ = lexer_.nextToken();
        }
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



} // namespace parser
} // namespace mota
