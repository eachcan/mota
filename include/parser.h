#pragma once

#include "ast.h"
#include "lexer.h"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

namespace mota {
namespace parser {

// 解析错误异常
class ParseError : public std::runtime_error {
public:
    ParseError(const std::string& message, uint32_t line, uint32_t column)
        : std::runtime_error(formatMessage(message, line, column)),
          line_(line),
          column_(column) {}
    
    uint32_t line() const { return line_; }
    uint32_t column() const { return column_; }
    
private:
    static std::string formatMessage(const std::string& message, uint32_t line, uint32_t column) {
        return "[" + std::to_string(line) + ":" + std::to_string(column) + "] " + message;
    }
    
    uint32_t line_;
    uint32_t column_;
};

// 语法分析器
class Parser {
public:
    explicit Parser(lexer::Lexer& lexer) : lexer_(lexer) {}
    
    // 解析整个文件
    std::unique_ptr<ast::Document> parse();
    
private:
    // 辅助方法
    const lexer::Token& advance();
    const lexer::Token& peek() const;
    const lexer::Token& peekNext() const;
    bool check(lexer::TokenType type) const;
    bool match(lexer::TokenType type);
    bool isAtEnd() const;
    
    // 错误处理
    lexer::Token consume(lexer::TokenType type, const std::string& message);
    ParseError error(const lexer::Token& token, const std::string& message);
    void synchronize();
    
    // 解析方法
    std::unique_ptr<ast::Node> declaration();
    std::unique_ptr<ast::Annotation> annotation();
    std::vector<ast::AnnotationArgument> annotationArguments();
    ast::AnnotationArgument annotationArgument();
    std::unique_ptr<ast::Node> typeDeclaration();
    std::unique_ptr<ast::Struct> structDeclaration();
    std::unique_ptr<ast::Enum> enumDeclaration();
    std::unique_ptr<ast::Block> blockDeclaration();
    std::unique_ptr<ast::Annotation> annotationDeclaration();
    std::unique_ptr<ast::Type> parseType();
    std::unique_ptr<ast::Type> primaryType();
    std::unique_ptr<ast::Type> containerType();
    std::unique_ptr<ast::Field> fieldDeclaration();
    std::unique_ptr<ast::EnumValue> enumValueDeclaration();
    std::unique_ptr<ast::Include> includeDeclaration();
    std::unique_ptr<ast::Namespace> namespaceDeclaration();
    
    // 表达式解析
    std::unique_ptr<ast::Expr> expression();
    std::unique_ptr<ast::Expr> assignment();
    std::unique_ptr<ast::Expr> logicalOr();
    std::unique_ptr<ast::Expr> logicalAnd();
    std::unique_ptr<ast::Expr> equality();
    std::unique_ptr<ast::Expr> comparison();
    std::unique_ptr<ast::Expr> term();
    std::unique_ptr<ast::Expr> factor();
    std::unique_ptr<ast::Expr> unary();
    std::unique_ptr<ast::Expr> primary();
    
    // 实用函数
    template<typename T, typename... Args>
    std::unique_ptr<T> makeNode(Args&&... args) {
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        node->location.filename = lexer_.getFilename();
        node->location.line = previous_.line;
        node->location.column = previous_.column;
        return node;
    }
    
    lexer::Lexer& lexer_;
    lexer::Token previous_;
    lexer::Token current_;
    bool hadError_ = false;
    bool panicMode_ = false;
};

} // namespace parser
} // namespace mota
