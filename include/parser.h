#pragma once
#include "lexer.h"
#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    void parse();

private:
    std::vector<Token> tokens;
    size_t currentIndex;

    Token currentToken();
    void advance();
    bool match(TokenType type);

    void parseStatement();
    void parseNamespace();
    void parseInclude();
    void parseStruct();
    void parseBlock();
};

