#include "lexer.h"

namespace mota {
namespace lexer {

Token Lexer::number() {
    bool isFloat = false;
    
    // 先检查是否是0开头，可能是十六进制或二进制数字
    if (source_[start_] == '0') {
        // 如果是0x或者0X开头，则是十六进制数字
        if (current_ < source_.length() && 
            (source_[current_] == 'x' || source_[current_] == 'X')) {
            advance(); // 跳过'x'或'X'
            
            // 消耗所有十六进制数字
            while (!isAtEnd() && isHexDigit(peek())) {
                advance();
            }
            
            // 检查是否有非法字符紧跟在十六进制数字后面
            if (!isAtEnd() && isAlphaNumeric(peek())) {
                // 收集无效的十六进制数字
                while (!isAtEnd() && isAlphaNumeric(peek())) {
                    advance();
                }
                std::string text = source_.substr(start_, current_ - start_);
                return Token(TokenType::Error, "Invalid hexadecimal number: " + text, line_, getColumn() - text.length());
            }

            if (current_ - start_ == 2) { // 0x后面没有数字
                std::string text = source_.substr(start_, current_ - start_);
                return Token(TokenType::Error, "Invalid hexadecimal number: " + text, line_, getColumn() - text.length());
            }
            
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Integer, text, line_, getColumn() - text.length());
        }
        
        // 如果是0b或者0B开头，则是二进制数字
        if (current_ < source_.length() && 
            (source_[current_] == 'b' || source_[current_] == 'B')) {
            advance(); // 跳过'b'或'B'
            
            // 消耗所有二进制数字
            while (!isAtEnd() && (peek() == '0' || peek() == '1')) {
                advance();
            }
            
            // 检查是否有非法字符紧跟在二进制数字后面
            if (!isAtEnd() && isAlphaNumeric(peek())) {
                // 收集无效的二进制数字
                while (!isAtEnd() && isAlphaNumeric(peek())) {
                    advance();
                }
                std::string text = source_.substr(start_, current_ - start_);
                return Token(TokenType::Error, "Invalid binary number: " + text, line_, getColumn() - text.length());
            }

            if (current_ - start_ == 2) { // 0b后面没有数字
                std::string text = source_.substr(start_, current_ - start_);
                return Token(TokenType::Error, "Invalid binary number: " + text, line_, getColumn() - text.length());
            }
            
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Integer, text, line_, getColumn() - text.length());
        }
        
        // 如果0后面紧跟着字母（非x或b），这是一个无效的数字
        if (!isAtEnd() && isAlpha(peek())) {
            // 收集无效的数字
            advance(); // 先消耗这个字母
            // 继续收集后续无效字符
            while (!isAtEnd() && isAlphaNumeric(peek())) {
                advance();
            }
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Error, "Invalid number: " + text, line_, getColumn() - text.length());
        }
    }
    
    // 处理普通数字（整数或浮点数）
    while (!isAtEnd() && isDigit(peek())) {
        advance();
    }
    
    // 处理小数部分
    if (peek() == '.' && !isAtEnd() && isDigit(peekNext())) {
        isFloat = true;
        advance(); // 消耗点号
        
        while (!isAtEnd() && isDigit(peek())) {
            advance();
        }
    }
    
    // 处理指数部分
    if (!isAtEnd() && (peek() == 'e' || peek() == 'E')) {
        isFloat = true;
        advance(); // 消耗'e'或'E'
        
        if (!isAtEnd() && (peek() == '+' || peek() == '-')) {
            advance(); // 消耗符号
        }
        
        while (!isAtEnd() && isDigit(peek())) {
            advance();
        }
        
        if (!isAtEnd() && isAlphaNumeric(peek())) {
            while (!isAtEnd() && isAlphaNumeric(peek())) {
                advance();
            }
            std::string text = source_.substr(start_, current_ - start_);
            return Token(TokenType::Error, "Invalid number format: " + text, line_, getColumn() - text.length());
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

} // namespace lexer
} // namespace mota
