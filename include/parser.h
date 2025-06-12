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
    std::shared_ptr<ast::Document> parse();
    
private:
    // 辅助方法
    lexer::Token advance(); // 查看当前token然后下一个
    lexer::Token peek() const; // 查看当前token
    lexer::Token peekNext() const; // 下一个token 并查看
    bool check(lexer::TokenType type) const; // 查看当前 token 并检查是否为type
    bool consume(lexer::TokenType type); // 如果当前token是type，则移到下一个token
    bool isAtEnd() const; // 检查是否到达文件末尾
    
    // 错误处理
    lexer::Token consume(lexer::TokenType type, const std::string& message);
    ParseError error(const lexer::Token& token, const std::string& message);
    
    // 解析方法
    std::shared_ptr<ast::Node> declaration();
    std::shared_ptr<ast::Annotation> annotation();
    std::vector<std::shared_ptr<ast::AnnotationArgument>> annotationArguments();
    std::shared_ptr<ast::AnnotationArgument> annotationArgument();
    std::shared_ptr<ast::Node> typeDeclaration();
    std::shared_ptr<ast::Struct> structDeclaration();
    std::shared_ptr<ast::Enum> enumDeclaration();
    std::shared_ptr<ast::Block> blockDeclaration();
    std::shared_ptr<ast::AnnotationDecl> annotationDeclaration();
    std::shared_ptr<ast::Type> parseType();
    std::shared_ptr<ast::Type> primaryType();
    std::shared_ptr<ast::Type> containerType();
    std::shared_ptr<ast::Field> fieldDeclaration();
    std::shared_ptr<ast::EnumValue> enumValueDeclaration();
    std::shared_ptr<ast::Include> includeDeclaration();
    std::shared_ptr<ast::Namespace> namespaceDeclaration();
    
    // 表达式解析
    std::shared_ptr<ast::Expr> expression();
    std::shared_ptr<ast::Expr> assignment();
    std::shared_ptr<ast::Expr> logicalOr();
    std::shared_ptr<ast::Expr> logicalAnd();
    std::shared_ptr<ast::Expr> equality();
    std::shared_ptr<ast::Expr> comparison();
    std::shared_ptr<ast::Expr> term();
    std::shared_ptr<ast::Expr> factor();
    std::shared_ptr<ast::Expr> unary();
    std::shared_ptr<ast::Expr> primary();
    
    // 实用函数
    template<typename T, typename... Args>
    std::shared_ptr<T> makeNode(Args&&... args) {
        auto node = std::make_shared<T>(std::forward<Args>(args)...);
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
