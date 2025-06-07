#include "lexer.h"

namespace mota {
namespace lexer {


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

} // namespace lexer
} // namespace mota
