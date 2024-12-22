#include "lexer.h"
#include <iostream>
#include <cctype>
#include <regex>

namespace mota {

Lexer::Lexer(const std::string& input) : input(input), pos(0), line(1), column(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    if (input.empty()) {
        return tokens;
    }

    if (input.length() > 3 && input.substr(0, 3) == "\xEF\xBB\xBF") {
        // 跳过 UTF-8 BOM
        pos += 3;
    }

    while (pos < input.length()) {
        char currentChar = input[pos];
        if (std::isspace(currentChar)) {
            handleWhitespace();
            continue;
        }
        if (currentChar == '/' && input[pos + 1] == '/') {
            // 跳过单行注释
            handleLineComment();
            continue;
        }
        if (currentChar == '/' && input[pos + 1] == '*') {
            // 处理块注释，作为注解Token保存
            tokens.push_back(handleBlockComment());
            continue;
        }
        if (isAlpha(currentChar)) {
            tokens.push_back(handleIdentifier());
            continue;
        }
        if (std::isdigit(currentChar)) {
            tokens.push_back(handleNumber());
            continue;
        }
        if (currentChar == '"') {
            tokens.push_back(handleString());
            continue;
        }
        if (isPunctuation(currentChar)) {
            tokens.push_back(handlePunctuation());
            continue;
        }
        if (currentChar == '@' && input[pos + 1] == '[') {
            auto tokensAnnotation = handleAnnotation();
            tokens.insert(tokens.end(), tokensAnnotation.begin(), tokensAnnotation.end());
            continue;
        }

        tokens.push_back({TokenType::Invalid, std::string(1, currentChar), line, column});
        advance();
    }
    tokens.push_back({TokenType::EndOfFile, "", line, column});
    return tokens;
}

void Lexer::advance() {
    pos++;
    column++;
}

void Lexer::handleWhitespace() {
    char currentChar = input[pos];
    if (currentChar == '\n') {
        line++;
        column = 1;
    }
    advance();
}

// 跳过单行注释
void Lexer::handleLineComment() {
    while (pos < input.length() && input[pos] != '\n') {
        advance();
    }
}

// 处理块注释，将注释作为 Token 存储
Token Lexer::handleBlockComment() {
    size_t start = pos;
    advance();  // 跳过第一个 '/'
    advance();  // 跳过第二个 '*'
    while (pos < input.length()) {
        if (input[pos] == '*' && input[pos + 1] == '/') {
            advance();  // 跳过 '*'
            advance();  // 跳过 '/'
            break;
        }
        advance();
    }

    std::string commentText = input.substr(start, pos - start);
    // 去除每行开头的空格和星号
    commentText = std::regex_replace(commentText, std::regex("(^|\\n)\\s*\\*"), "$1");

    return {TokenType::Comment, commentText, line, column};
}

// 处理标识符
Token Lexer::handleIdentifier() {
    size_t start = pos;
    while (pos < input.length() && (std::isalnum(input[pos]) || input[pos] == '_')) {
        advance();
    }
    std::string value = input.substr(start, pos - start);
    return {TokenType::Identifier, value, line, column};
}

// 处理数字常量
Token Lexer::handleNumber() {
    size_t start = pos;
    
    // 检查是否是十六进制、二进制或八进制
    if (input[pos] == '0' && pos + 1 < input.length()) {
        char prefix = std::tolower(input[pos + 1]);
        if (prefix == 'x') {  // 十六进制
            advance();  // 跳过 '0'
            advance();  // 跳过 'x'
            if (pos >= input.length() || !std::isxdigit(input[pos])) {
                throw std::runtime_error("Invalid hexadecimal number format");
            }
            while (pos < input.length() && std::isxdigit(input[pos])) {
                advance();
            }
            return {TokenType::Constant, input.substr(start, pos - start), line, column};
        }
        else if (prefix == 'b') {  // 二进制
            advance();  // 跳过 '0'
            advance();  // 跳过 'b'
            if (pos >= input.length() || (input[pos] != '0' && input[pos] != '1')) {
                throw std::runtime_error("Invalid binary number format");
            }
            while (pos < input.length() && (input[pos] == '0' || input[pos] == '1')) {
                advance();
            }
            return {TokenType::Constant, input.substr(start, pos - start), line, column};
        }
        else if (std::isdigit(prefix)) {  // 八进制
            advance();  // 跳过 '0'
            while (pos < input.length() && input[pos] >= '0' && input[pos] <= '7') {
                advance();
            }
            return {TokenType::Constant, input.substr(start, pos - start), line, column};
        }
    }
    
    // 处理十进制整数部分
    while (pos < input.length() && std::isdigit(input[pos])) {
        advance();
    }
    
    // 处理小数部分
    if (pos < input.length() && input[pos] == '.') {
        advance();  // 跳过小数点
        // 小数点后必须有数字
        if (!std::isdigit(input[pos])) {
            throw std::runtime_error("Invalid number format: expected digit after decimal point");
        }
        while (pos < input.length() && std::isdigit(input[pos])) {
            advance();
        }
    }
    
    return {TokenType::Constant, input.substr(start, pos - start), line, column};
}

// 处理字符串常量
Token Lexer::handleString() {
    size_t start = pos;
    advance();  // skip opening quote
    while (pos < input.length() && input[pos] != '"') {
        advance();
    }
    advance();  // skip closing quote

    std::string value = input.substr(start, pos - start);
    // 去掉转义
    value = std::regex_replace(value, std::regex("\\\\\""), "\"");

    return {TokenType::Constant, value, line, column};
}

// 处理标点符号
Token Lexer::handlePunctuation() {
    char currentChar = input[pos];
    std::string value(1, currentChar);
    advance();
    return {TokenType::Punctuation, value, line, column};
}

// 处理注解
std::vector<Token> Lexer::handleAnnotation() {
    size_t start = pos;
    advance();  // 跳过 '@'
    advance();  // 跳过 '['

    // 先返回 AnnotationStart
    std::vector<Token> annotationTokens;
    annotationTokens.push_back({TokenType::AnnotationStart, "@[", line, column});

    // 开始解析注解内容，直到遇到 "]"
    while (pos < input.length() && input[pos] != ']') {
        // 跳过空白字符
        if (std::isspace(input[pos])) {
            handleWhitespace();
            continue;
        }

        // 解析 key (标识符)
        if (isAlpha(input[pos])) {
            Token keyToken = handleIdentifier(); // 处理 key
            annotationTokens.push_back(keyToken);
        }
        // 跳过空白字符
        if (std::isspace(input[pos])) {
            handleWhitespace();
        }

        // 跳过 '='
        if (input[pos] == '=') {
            auto punctuation = handlePunctuation();
            annotationTokens.push_back(punctuation);
        }

        // 跳过空白字符
        if (std::isspace(input[pos])) {
            handleWhitespace();
        }

        // 解析 value (可能是标识符、字符串或数字)
        Token valueToken;
        if (isAlpha(input[pos])) {
            valueToken = handleIdentifier(); // 处理标识符类型的值
        } else if (input[pos] == '"') {
            valueToken = handleString(); // 处理字符串类型的值
        } else if (isdigit(input[pos]) || input[pos] == '-') {
            valueToken = handleNumber(); // 处理数字类型的值
        }
        
        // 添加值 token
        annotationTokens.push_back(valueToken);

        // 跳过空白字符
        if (std::isspace(input[pos])) {
            handleWhitespace();
        }

        // 如果遇到逗号，添加逗号token
        if (input[pos] == ',') {
            auto punctuation = handlePunctuation();
            annotationTokens.push_back(punctuation);
        }
    }

    // 添加注解结束标记
    advance();  // 跳过 ']'
    annotationTokens.push_back({TokenType::AnnotationEnd, "]", line, column});

    return annotationTokens;
}

bool Lexer::isAlpha(char c) {
    return std::isalpha(c) || c == '_';
}

bool Lexer::isPunctuation(char c) {
    static const std::string punctuations = "{}[]().,;=:";
    return punctuations.find(c) != std::string::npos;
}

// Token 类型的字符串表示
static const char* TokenTypeStrings[] = {
    "Keyword",
    "Identifier",
    "Constant",
    "Punctuation",
    "Operator",
    "Comment",
    "AnnotationStart",
    "AnnotationEnd",
    "EndOfFile",
    "Invalid"
};

const char* tokenTypeToString(TokenType type) {
    return TokenTypeStrings[static_cast<int>(type)];
}

}  // namespace mota
