#pragma once

#include <string>
#include <vector>

enum class TokenType {
    Identifier,       // 标识符
    IntegerLiteral,   // 整数常量
    StringLiteral,    // 字符串常量
    Keyword,          // 关键字
    Symbol,           // 符号（如 =, {, }, ; 等）
    Comment,          // 注释
    Annotation,       // 注解（如 @[ ... ]）
};

struct Token {
    TokenType type;   // token 类型
    std::string value; // token 值
    int line;          // 行号
    int column;        // 列号
};

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;  // 输入源代码
    size_t index;        // 当前索引
    int line;            // 当前行号
    int column;          // 当前列号

    char currentChar();
    void advance();
    void skipWhitespace();
    void skipComment();
    void collectAnnotation();
};
