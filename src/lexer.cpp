#include "lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <regex>

Lexer::Lexer(const std::string& source) : source(source), index(0), line(1), column(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (index < source.size()) {
        char currentChar = source[index];

        if (isspace(currentChar)) {
            if (currentChar == '\n') {
                ++line;
                column = 1;
            }
            ++index;
            continue;
        }

        if (currentChar == '/') {
            if (index + 1 < source.size() && source[index + 1] == '/') {
                // 行注释
                while (index < source.size() && source[index] != '\n') {
                    ++index;
                }
                continue;
            } else if (index + 1 < source.size() && source[index + 1] == '*') {
                // 块注释
                index += 2;
                while (index < source.size() && !(source[index] == '*' && source[index + 1] == '/')) {
                    ++index;
                }
                index += 2;
                continue;
            }
        }

        if (isalpha(currentChar) || currentChar == '_') {
            std::string value;
            while (isalnum(source[index]) || source[index] == '_') {
                value.push_back(source[index]);
                ++index;
            }
            tokens.push_back({TokenType::Identifier, value, line, column});
        } else if (isdigit(currentChar)) {
            std::string value;
            while (isdigit(source[index])) {
                value.push_back(source[index]);
                ++index;
            }
            tokens.push_back({TokenType::IntegerLiteral, value, line, column});
        } else if (currentChar == '"') {
            ++index;
            std::string value;
            while (index < source.size() && source[index] != '"') {
                value.push_back(source[index]);
                ++index;
            }
            ++index; // skip closing quote
            tokens.push_back({TokenType::StringLiteral, value, line, column});
        } else if (currentChar == '=' || currentChar == ';' || currentChar == '{' || currentChar == '}' || currentChar == ',' || currentChar == '[' || currentChar == ']') {
            tokens.push_back({TokenType::Symbol, std::string(1, currentChar), line, column});
            ++index;
        } else {
            std::cerr << "Unknown character: " << currentChar << std::endl;
            ++index;
        }
    }

    return tokens;
}
