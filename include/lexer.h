#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>

namespace mota {
namespace lexer {

// 词法单元类型
enum class TokenType {
    // 文件结束
    Eof,
    
    // 标识符和字面量
    Identifier,
    Integer,
    Float,
    String,
    
    // 关键字
    Namespace,
    Include,
    Struct,
    Enum,
    Block,
    Annotation,
    
    // 类型
    Int8, Int16, Int32, Int64,
    Float32, Float64,
    StringType,
    Bytes,
    Bool,
    Repeated,
    Map,
    Optional,
    
    // 标点符号
    LeftBrace,      // {
    RightBrace,     // }
    LeftParen,      // (
    RightParen,     // )
    LeftBracket,    // [
    RightBracket,   // ]
    LeftAngle,      // <
    RightAngle,     // >
    Semicolon,      // ;
    Comma,          // ,
    Dot,            // .
    Colon,          // :
    Equal,          // =
    At,             // @
    
    // 操作符
    Plus,           // +
    Minus,          // -
    Star,           // *
    Slash,          // /
    Percent,        // %
    Bang,           // !
    And,            // &&
    Or,             // ||
    Less,           // <
    Greater,        // >
    
    // 布尔值
    True,           // true
    False,          // false
    
    // 复合操作符
    EqualEqual,     // ==
    BangEqual,      // !=
    LessEqual,      // <=
    GreaterEqual,   // >=
    
    // 注释
    LineComment,    // //
    BlockComment,   // /* */
    UIComment,      // //@
    
    // 其他
    Error
};

// 词法单元
struct Token {
    TokenType type;
    std::string lexeme;
    uint32_t line;
    uint32_t column;
    
    // 默认构造函数
    Token() : type(TokenType::Error), lexeme(""), line(0), column(0) {}
    
    Token(TokenType type, std::string lexeme, uint32_t line, uint32_t column)
        : type(type), lexeme(std::move(lexeme)), line(line), column(column) {}
};

// 词法分析器
class Lexer {
public:
    explicit Lexer(const std::string& source, const std::string& filename = "");
    
    // 获取下一个词法单元
    Token nextToken();
    
    // 查看下一个词法单元但不消费它
    Token peekToken();
    
    // 获取当前行号
    uint32_t getLine() const { return line_; }
    
    // 获取当前列号
    uint32_t getColumn() const { return current_ - lineStart_ + 1; }
    
    // 获取文件名
    const std::string& getFilename() const { return filename_; }
    
private:
    // 辅助函数
    char advance();
    bool match(char expected);
    char peek() const;
    char peekNext() const;
    bool isAtEnd() const;
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isAlphaNumeric(char c) const;
    bool isHexDigit(char c) const;
    void skipWhitespace();
    
    // 词法分析辅助函数
    Token identifierOrKeyword();
    Token number();
    Token string();
    Token lineComment();
    Token blockComment();
    Token uiComment();
    
    // 源文本和位置信息
    std::string source_;
    std::string filename_;
    size_t start_;
    size_t current_;
    uint32_t line_;
    size_t lineStart_;
    
    // 用于peekToken
    std::optional<Token> lookahead_;
};

} // namespace lexer
} // namespace mota
