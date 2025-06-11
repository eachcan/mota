#include "lexer.h"
#include <unordered_map>

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
    {"annotation", TokenType::Annotation},

    {"true", TokenType::True},
    {"false", TokenType::False},
};

Token Lexer::identifierOrKeyword() {
    while (isAlphaNumeric(peek()) || peek() == '_') {
        advance();
    }
    
    std::string text = source_.substr(start_, current_ - start_);
    auto it = keywords.find(text);
    TokenType type = (it != keywords.end()) ? it->second : TokenType::Identifier;
    
    return Token(type, text, line_, getColumn() - text.length());
}

} // namespace lexer
} // namespace mota
