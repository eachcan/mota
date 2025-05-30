#include "lexer.h"
#include <cctype>
#include <unordered_map>
#include <stdexcept>

namespace mota {
namespace lexer {

// 关键字映射
static const std::unordered_map<std::string, TokenType> keywords = {
    // 类型关键字
    {"int8", TokenType::Int8},
    {"int16", TokenType::Int16},
    {"int32", TokenType::Int32},
    {"int64", TokenType::Int64},
    {"float32", TokenType::Float32},
    {"float64", TokenType::Float64},
    {"string", TokenType::StringType},
    {"bytes", TokenType::Bytes},
    {"bool", TokenType::Bool},
    
    // 容器类型
    {"repeated", TokenType::Repeated},
    {"map", TokenType::Map},
    {"optional", TokenType::Optional},
    
    // 声明关键字
    {"namespace", TokenType::Namespace},
    {"include", TokenType::Include},
    {"struct", TokenType::Struct},
    {"enum", TokenType::Enum},
    {"block", TokenType::Block},
    {"annotation", TokenType::Annotation}
};

Lexer::Lexer(const std::string& source, const std::string& filename)
    : source_(source),
      filename_(filename),
      start_(0),
      current_(0),
      line_(1),
      lineStart_(0) {}

Token Lexer::nextToken() {
    // 如果有lookahead token，先返回它
    if (lookahead_.has_value()) {
        Token token = lookahead_.value();
        lookahead_.reset();
        return token;
    }
    
    skipWhitespace();
    start_ = current_;
    
    if (isAtEnd()) {
        return Token(TokenType::Eof, "", line_, getColumn());
    }
    
    char c = advance();
    
    // 处理标识符和关键字
    if (isAlpha(c) || c == '_') {
        return identifierOrKeyword();
    }
    
    // 处理数字
    if (isDigit(c)) {
        return number();
    }
    
    // 处理字符串
    if (c == '"') {
        return string();
    }
    
    // 处理注释
    if (c == '/') {
        if (peek() == '/') {
            // 检查是否是UI注释
            advance(); // 消耗第二个'/'
            if (peek() == '@') {
                return uiComment();
            } else {
                // 回退一步，让lineComment方法处理
                current_--;
                return lineComment();
            }
        } else if (peek() == '*') {
            return blockComment();
        }
        return Token(TokenType::Slash, "/", line_, getColumn() - 1);
    }
    
    // 处理其他单字符和复合操作符
    switch (c) {
        case '{': return Token(TokenType::LeftBrace, "{", line_, getColumn());
        case '}': return Token(TokenType::RightBrace, "}", line_, getColumn());
        case '(': return Token(TokenType::LeftParen, "(", line_, getColumn());
        case ')': return Token(TokenType::RightParen, ")", line_, getColumn());
        case '[': return Token(TokenType::LeftBracket, "[", line_, getColumn());
        case ']': return Token(TokenType::RightBracket, "]", line_, getColumn());
        
        // 复合操作符
        case '<': 
            if (match('=')) {
                return Token(TokenType::LessEqual, "<=", line_, getColumn() - 2);
            }
            return Token(TokenType::Less, "<", line_, getColumn() - 1);  // 使用Less而不是LeftAngle
            
        case '>': 
            if (match('=')) {
                return Token(TokenType::GreaterEqual, ">=", line_, getColumn() - 2);
            }
            return Token(TokenType::Greater, ">", line_, getColumn() - 1);  // 使用Greater而不是RightAngle
            
        case '=': 
            if (match('=')) {
                return Token(TokenType::EqualEqual, "==", line_, getColumn() - 2);
            }
            return Token(TokenType::Equal, "=", line_, getColumn() - 1);
            
        case '!': 
            if (match('=')) {
                return Token(TokenType::BangEqual, "!=", line_, getColumn() - 2);
            }
            // 支持单独的'!'操作符
            return Token(TokenType::Bang, "!", line_, getColumn() - 1);
            
        case ';': return Token(TokenType::Semicolon, ";", line_, getColumn());
        case ',': return Token(TokenType::Comma, ",", line_, getColumn());
        case '.': return Token(TokenType::Dot, ".", line_, getColumn());
        
        // 逻辑操作符
        case '&': 
            if (match('&')) {
                return Token(TokenType::And, "&&", line_, getColumn() - 2);
            }
            return Token(TokenType::Error, "Unexpected character '&'", line_, getColumn() - 1);
            
        case '|': 
            if (match('|')) {
                return Token(TokenType::Or, "||", line_, getColumn() - 2);
            }
            return Token(TokenType::Error, "Unexpected character '|'", line_, getColumn() - 1);
        case ':': return Token(TokenType::Colon, ":", line_, getColumn());
        case '@': return Token(TokenType::At, "@", line_, getColumn());
        case '+': return Token(TokenType::Plus, "+", line_, getColumn());
        case '-': return Token(TokenType::Minus, "-", line_, getColumn());
        case '*': return Token(TokenType::Star, "*", line_, getColumn());
        case '%': return Token(TokenType::Percent, "%", line_, getColumn());
    }
    
    // 未识别的字符
    return Token(TokenType::Error, std::string("Unexpected character '") + c + "'", line_, getColumn() - 1);
}

Token Lexer::peekToken() {
    if (!lookahead_.has_value()) {
        lookahead_ = nextToken();
    }
    return lookahead_.value();
}

char Lexer::advance() {
    return source_[current_++];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || source_[current_] != expected) {
        return false;
    }
    current_++;
    return true;
}

char Lexer::peek() const {
    return isAtEnd() ? '\0' : source_[current_];
}

char Lexer::peekNext() const {
    return (current_ + 1 >= source_.length()) ? '\0' : source_[current_ + 1];
}

bool Lexer::isAtEnd() const {
    return current_ >= source_.length();
}

bool Lexer::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

bool Lexer::isHexDigit(char c) const {
    return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

void Lexer::skipWhitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\t':
            case '\r':
                advance();
                break;
            case '\n':
                line_++;
                lineStart_ = current_ + 1;
                advance();
                break;
            default:
                return;
        }
    }
}

Token Lexer::identifierOrKeyword() {
    while (isAlphaNumeric(peek()) || peek() == '_') {
        advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    auto it = keywords.find(text);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::Identifier;
    
    return Token(type, text, line_, getColumn() - text.length());
}

Token Lexer::number() {
    bool isFloat = false;
    
    // 先检查是否是0开头，可能是十六进制或二进制数字
    if (source_[start_] == '0') {
        // 如果是0x或者0X开头，则是十六进制数字
        if (current_ < source_.length() - 1 && (source_[start_ + 1] == 'x' || source_[start_ + 1] == 'X')) {
            current_ = start_ + 2; // 跳过'0x'或'0X'
            
            // 至少需要一个十六进制数字
            if (current_ >= source_.length() || !isHexDigit(source_[current_])) {
                return Token(TokenType::Error, "Invalid hexadecimal number", line_, getColumn());
            }
            
            // 消耗所有十六进制数字
            while (current_ < source_.length() && isHexDigit(source_[current_])) {
                current_++;
            }
            
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Integer, text, line_, getColumn() - text.length());
        }
        
        // 如果是0b或者0B开头，则是二进制数字
        if (current_ < source_.length() - 1 && (source_[start_ + 1] == 'b' || source_[start_ + 1] == 'B')) {
            current_ = start_ + 2; // 跳过'0b'或'0B'
            
            // 至少需要一个二进制数字
            if (current_ >= source_.length() || (source_[current_] != '0' && source_[current_] != '1')) {
                return Token(TokenType::Error, "Invalid binary number", line_, getColumn());
            }
            
            // 消耗所有二进制数字
            while (current_ < source_.length() && (source_[current_] == '0' || source_[current_] == '1')) {
                current_++;
            }
            
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Integer, text, line_, getColumn() - text.length());
        }
    }
    
    // 处理普通数字（整数或浮点数）
    while (isDigit(peek())) {
        advance();
    }
    
    // 处理小数部分
    if (peek() == '.' && isDigit(peekNext())) {
        isFloat = true;
        advance(); // 消耗点号
        
        while (isDigit(peek())) {
            advance();
        }
    }
    
    // 处理指数部分
    if (peek() == 'e' || peek() == 'E') {
        isFloat = true;
        advance(); // 消耗'e'或'E'
        
        if (peek() == '+' || peek() == '-') {
            advance(); // 消耗符号
        }
        
        if (!isDigit(peek())) {
            return Token(TokenType::Error, "Invalid number format", line_, getColumn());
        }
        
        while (isDigit(peek())) {
            advance();
        }
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    return Token(
        isFloat ? TokenType::Float : TokenType::Integer,
        text,
        line_,
        getColumn() - text.length()
    );
}

Token Lexer::string() {
    std::string value;
    
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line_++;
            lineStart_ = current_ + 1;
        } else if (peek() == '\\') {
            advance(); // 消耗反斜杠
            
            switch (peek()) {
                case '"': value += '"'; break;
                case '\\': value += '\\'; break;
                case 'n': value += '\n'; break;
                case 'r': value += '\r'; break;
                case 't': value += '\t'; break;
                default:
                    return Token(TokenType::Error, "Invalid escape sequence", line_, getColumn());
            }
        } else {
            value += peek();
        }
        
        advance();
    }
    
    if (isAtEnd()) {
        return Token(TokenType::Error, "Unterminated string", line_, getColumn());
    }
    
    // 消耗结束的双引号
    advance();
    
    return Token(TokenType::String, value, line_, getColumn() - value.length() - 2);
}

Token Lexer::lineComment() {
    advance(); // 消耗第二个'/'
    
    while (peek() != '\n' && !isAtEnd()) {
        advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    return Token(TokenType::LineComment, text, line_, getColumn() - text.length());
}

Token Lexer::uiComment() {
    advance(); // 消耗'@'
    
    while (peek() != '\n' && !isAtEnd()) {
        advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    return Token(TokenType::UIComment, text, line_, getColumn() - text.length());
}

Token Lexer::blockComment() {
    advance(); // 消耗第二个'/'
    advance(); // 消耗'*'
    
    uint32_t startLine = line_;
    
    while (!isAtEnd()) {
        if (peek() == '*' && peekNext() == '/') {
            advance(); // 消耗'*'
            advance(); // 消耗'/'
            break;
        }
        
        if (peek() == '\n') {
            line_++;
            lineStart_ = current_ + 1;
        }
        
        advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    return Token(TokenType::BlockComment, text, startLine, 0);
}

} // namespace lexer
} // namespace mota
