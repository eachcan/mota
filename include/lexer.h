#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

namespace mota {

// Token 类型
enum class TokenType {
    Keyword,
    Identifier,
    Constant,
    Punctuation,
    Operator,
    Comment,
    AnnotationStart,
    AnnotationEnd,
    EndOfFile,
    Invalid
};

// Token 结构体，用于表示词法单元
struct Token {
    TokenType type;      // 词法单元类型
    std::string value;   // 词法单元的值
    int line;            // 行号
    int column;          // 列号
};

// 词法分析器类
class Lexer {
public:
    Lexer(const std::string& input);  // 构造函数

    // 分析输入字符串并返回所有的 tokens
    std::vector<Token> tokenize();    

private:
    std::string input;  // 输入的字符串
    size_t pos;         // 当前处理位置
    int line;           // 当前行号
    int column;         // 当前列号

    void advance();              // 向前移动
    void handleWhitespace();     // 处理空白字符
    void handleLineComment();    // 处理单行注释
    Token handleBlockComment();  // 处理块注释
    Token handleIdentifier();    // 处理标识符
    Token handleNumber();        // 处理数字常量
    Token handleString();        // 处理字符串常量
    Token handlePunctuation();   // 处理标点符号
    std::vector<Token> handleAnnotation();  // 处理注解

    // 辅助方法
    bool isAlpha(char c);      // 判断字符是否为字母或下划线
    bool isPunctuation(char c);  // 判断字符是否为标点符号
};

const char* tokenTypeToString(TokenType type);  // Token 类型的字符串表示

}  // namespace mota

#endif  // LEXER_H
