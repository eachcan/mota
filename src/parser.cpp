#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <memory>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentIndex(0) {}

Token Parser::currentToken() {
    return tokens[currentIndex];
}

void Parser::advance() {
    ++currentIndex;
}

bool Parser::match(TokenType type) {
    if (currentIndex < tokens.size() && tokens[currentIndex].type == type) {
        advance();
        return true;
    }
    return false;
}

void Parser::parse() {
    while (currentIndex < tokens.size()) {
        parseStatement();
    }
}

void Parser::parseStatement() {
    if (match(TokenType::Keyword)) {
        // 根据关键字来决定接下来的解析
        if (currentToken().value == "namespace") {
            parseNamespace();
        } else if (currentToken().value == "include") {
            parseInclude();
        } else if (currentToken().value == "struct") {
            parseStruct();
        } else if (currentToken().value == "block") {
            parseBlock();
        }
    }
}

void Parser::parseNamespace() {
    advance();
    if (match(TokenType::Identifier)) {
        std::cout << "Namespace: " << currentToken().value << std::endl;
    }
}

void Parser::parseInclude() {
    advance();
    if (match(TokenType::StringLiteral)) {
        std::cout << "Include: " << currentToken().value << std::endl;
    }
}

void Parser::parseStruct() {
    // 解析结构体定义
    std::cout << "Parsing struct" << std::endl;
}

void Parser::parseBlock() {
    // 解析块定义
    std::cout << "Parsing block" << std::endl;
}
