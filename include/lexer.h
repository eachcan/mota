#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Token 类型定义
enum class TokenType {
    Keyword,      // 关键字
    Identifier,   // 标识符
    Constant,     // 常量
    Punctuation,  // 标点符号
    Operator,     // 操作符
    Comment,      // 注释
    AnnotationStart,   // 注解开始
    AnnotationEnd,     // 注解结束
    EndOfFile,    // 文件结束
    Invalid       // 无效字符
};

// 每个 Token 包含一个类型和它对应的值
struct Token {
    TokenType type;
    std::string value;
    size_t line;   // 行号
    size_t column; // 列号
};

// 词法分析器类
class Lexer {
public:
    Lexer(const std::string& input);

    // 开始词法分析
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;    // 当前字符的位置
    size_t line;   // 当前行号
    size_t column; // 当前列号

    void advance();
    void handleWhitespace();
    void handleLineComment();
    Token handleBlockComment();
    Token handleIdentifier();
    Token handleNumber();
    Token handleString();
    Token handlePunctuation();
    std::vector<Token> handleAnnotation();

    bool isAlpha(char c);
    bool isPunctuation(char c);
};

#endif // LEXER_H
