#include "lexer.h"

namespace mota {
namespace lexer {

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
        uint32_t startColumn = getColumn() - 2; // 减去已消耗的'/*'
        
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
        
        // 检查是否到达文件末尾且没有找到注释结束标记
        if (isAtEnd() && !(text.length() >= 4 && 
                          text[text.length()-2] == '*' && 
                          text[text.length()-1] == '/')) {
            return Token(TokenType::Error, "Unterminated block comment", startLine, startColumn);
        }
        
        return Token(TokenType::BlockComment, text, startLine, startColumn);
    }

} // namespace lexer
} // namespace mota
