#include "../include/parser.h"
#include <stdexcept>
#include <iostream>

namespace mota {

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

std::shared_ptr<FileNode> Parser::parseFile() {
    auto file = std::make_shared<FileNode>();
    
    while (!isAtEnd()) {
        try {
            if (auto decl = parseDeclaration()) {
                file->declarations.push_back(decl);
            }
        } catch (const ParseError& error) {
            std::cerr << error.what() << std::endl;
            synchronize();
        }
    }
    
    return file;
}

DeclPtr Parser::parseDeclaration() {
    // 首先解析可能的注解
    std::vector<Annotation> annotations;
    std::string comment;
    
    if (peek().type == TokenType::Comment) {
        comment = parseComment();
    }
    
    if (peek().type == TokenType::AnnotationStart) {
        annotations = parseAnnotations();
    }
    
    Token token = peek();
    if (token.type != TokenType::Identifier) {
        return nullptr;
    }
    
    if (token.value == "include") {
        auto decl = parseInclude();
        decl->annotations = annotations;
        decl->comment = comment;
        return decl;
    }
    
    if (token.value == "namespace") {
        auto decl = parseNamespace();
        decl->annotations = annotations;
        decl->comment = comment;
        return decl;
    }
    
    if (token.value == "enum") {
        auto decl = parseEnum();
        decl->annotations = annotations;
        decl->comment = comment;
        return decl;
    }
    
    if (token.value == "struct") {
        auto decl = parseStruct();
        decl->annotations = annotations;
        decl->comment = comment;
        return decl;
    }
    
    if (token.value == "block") {
        auto decl = parseBlock();
        decl->annotations = annotations;
        decl->comment = comment;
        return decl;
    }
    
    throw ParseError("Expected declaration");
}

DeclPtr Parser::parseInclude() {
    consume(TokenType::Identifier, "Expected 'include'");
    Token path = consume(TokenType::Constant, "Expected string literal after 'include'");
    consume(TokenType::Punctuation, "Expected ';' after include path");
    
    auto include = std::make_shared<IncludeDecl>();
    include->path = path.value;
    return include;
}

DeclPtr Parser::parseNamespace() {
    consume(TokenType::Identifier, "Expected 'namespace'");
    auto ns = std::make_shared<NamespaceDecl>();
    
    do {
        Token name = consume(TokenType::Identifier, "Expected namespace name");
        ns->path.push_back(name.value);
        if (match(TokenType::Punctuation) && peek().value == ".") {
            advance();  // consume '.'
        } else {
            break;
        }
    } while (true);

    std::cout << "puctuation: " << peek().value << std::endl;
    
    consume(TokenType::Punctuation, "Expected ';' after namespace declaration");
    return ns;
}

DeclPtr Parser::parseEnum() {
    consume(TokenType::Identifier, "Expected 'enum'");
    Token name = consume(TokenType::Identifier, "Expected enum name");
    consume(TokenType::Punctuation, "Expected '{' after enum name");
    
    auto enumDecl = std::make_shared<EnumDecl>();
    enumDecl->name = name.value;
    
    while (!check(TokenType::Punctuation) || peek().value != "}") {
        enumDecl->values.push_back(parseEnumValue());
        if (!check(TokenType::Punctuation) || peek().value != "}") {
            consume(TokenType::Punctuation, "Expected ';' after enum value");
        }
    }
    
    consume(TokenType::Punctuation, "Expected '}' after enum values");
    return enumDecl;
}

std::shared_ptr<EnumValueDecl> Parser::parseEnumValue() {
    std::vector<Annotation> annotations;
    std::string comment;
    
    if (peek().type == TokenType::Comment) {
        comment = parseComment();
    }
    
    if (peek().type == TokenType::AnnotationStart) {
        annotations = parseAnnotations();
    }
    
    Token name = consume(TokenType::Identifier, "Expected enum value name");
    
    auto value = std::make_shared<EnumValueDecl>();
    value->name = name.value;
    value->annotations = annotations;
    value->comment = comment;
    
    if (match(TokenType::Punctuation) && peek().value == "=") {
        advance();  // consume '='
        value->value = parseExpression();
    }
    
    return value;
}

DeclPtr Parser::parseStruct() {
    consume(TokenType::Identifier, "Expected 'struct'");
    Token name = consume(TokenType::Identifier, "Expected struct name");
    consume(TokenType::Punctuation, "Expected '{' after struct name");
    
    auto structDecl = std::make_shared<StructDecl>();
    structDecl->name = name.value;
    
    while (!check(TokenType::Punctuation) || peek().value != "}") {
        structDecl->fields.push_back(parseField());
        if (!check(TokenType::Punctuation) || peek().value != "}") {
            consume(TokenType::Punctuation, "Expected ';' after field");
        }
    }
    
    consume(TokenType::Punctuation, "Expected '}' after struct fields");
    return structDecl;
}

DeclPtr Parser::parseBlock() {
    consume(TokenType::Identifier, "Expected 'block'");
    Token name = consume(TokenType::Identifier, "Expected block name");
    consume(TokenType::Punctuation, "Expected '{' after block name");
    
    auto blockDecl = std::make_shared<BlockDecl>();
    blockDecl->name = name.value;
    
    while (!check(TokenType::Punctuation) || peek().value != "}") {
        blockDecl->fields.push_back(parseField());
        if (!check(TokenType::Punctuation) || peek().value != "}") {
            consume(TokenType::Punctuation, "Expected ';' after field");
        }
    }
    
    consume(TokenType::Punctuation, "Expected '}' after block fields");
    return blockDecl;
}

std::shared_ptr<FieldDecl> Parser::parseField() {
    std::vector<Annotation> annotations;
    std::string comment;
    
    if (peek().type == TokenType::Comment) {
        comment = parseComment();
    }
    
    if (peek().type == TokenType::AnnotationStart) {
        annotations = parseAnnotations();
    }
    
    auto type = parseType();
    Token name = consume(TokenType::Identifier, "Expected field name");
    
    auto field = std::make_shared<FieldDecl>();
    field->type = type;
    field->name = name.value;
    field->annotations = annotations;
    field->comment = comment;
    
    if (match(TokenType::Punctuation) && peek().value == "=") {
        advance();  // consume '='
        field->defaultValue = parseExpression();
    }
    
    return field;
}

TypePtr Parser::parseType() {
    if (match(TokenType::Identifier)) {
        Token modifier = peek();
        if (modifier.value == "optional" || 
            modifier.value == "map" || 
            modifier.value == "repeated") {
            advance();  // consume modifier
            auto modifiedType = std::make_shared<ModifiedTypeNode>();
            if (modifier.value == "optional") {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Optional;
            } else if (modifier.value == "map") {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Map;
            } else {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Repeated;
            }
            modifiedType->baseType = parseType();
            return modifiedType;
        }
        
        // 检查是否是基本类型
        static const std::map<std::string, BasicType> basicTypes = {
            {"int8", BasicType::Int8},
            {"int16", BasicType::Int16},
            {"int32", BasicType::Int32},
            {"int64", BasicType::Int64},
            {"float32", BasicType::Float32},
            {"double64", BasicType::Double64},
            {"string", BasicType::String},
            {"bool", BasicType::Bool},
            {"bytes", BasicType::Bytes}
        };
        
        auto it = basicTypes.find(modifier.value);
        if (it != basicTypes.end()) {
            auto basicType = std::make_shared<BasicTypeNode>();
            basicType->type = it->second;
            return basicType;
        }
        
        // 自定义类型
        auto customType = std::make_shared<CustomTypeNode>();
        customType->name = modifier.value;
        return customType;
    }
    
    throw ParseError("Expected type");
}

ExprPtr Parser::parseExpression() {
    if (check(TokenType::Constant)) {
        return parseLiteral();
    }
    if (check(TokenType::Identifier)) {
        return parseIdentifier();
    }
    if (check(TokenType::Punctuation) && peek().value == "[") {
        return parseArray();
    }
    throw ParseError("Expected expression");
}

ExprPtr Parser::parseLiteral() {
    Token token = consume(TokenType::Constant, "Expected literal");
    auto literal = std::make_shared<LiteralExpr>();
    
    // 尝试解析不同类型的字面量
    try {
        if (token.value == "true") {
            literal->value = true;
        } else if (token.value == "false") {
            literal->value = false;
        } else if (token.value[0] == '"') {
            literal->value = token.value.substr(1, token.value.length() - 2);
        } else {
            // 尝试解析为整数或浮点数
            size_t pos;
            if (token.value.find('.') != std::string::npos) {
                literal->value = std::stod(token.value, &pos);
            } else {
                literal->value = std::stoll(token.value, &pos);
            }
        }
    } catch (...) {
        throw ParseError("Invalid literal value");
    }
    
    return literal;
}

ExprPtr Parser::parseIdentifier() {
    Token token = consume(TokenType::Identifier, "Expected identifier");
    auto identifier = std::make_shared<IdentifierExpr>();
    identifier->name = token.value;
    return identifier;
}

ExprPtr Parser::parseArray() {
    consume(TokenType::Punctuation, "Expected '['");
    auto array = std::make_shared<ArrayExpr>();
    
    if (!check(TokenType::Punctuation) || peek().value != "]") {
        do {
            array->elements.push_back(parseExpression());
        } while (match(TokenType::Punctuation) && peek().value == ",");
    }
    
    consume(TokenType::Punctuation, "Expected ']'");
    return array;
}

std::vector<Annotation> Parser::parseAnnotations() {
    std::vector<Annotation> annotations;
    
    while (match(TokenType::AnnotationStart)) {
        annotations.push_back(parseAnnotation());
    }
    
    return annotations;
}

Annotation Parser::parseAnnotation() {
    Annotation annotation;
    
    while (!check(TokenType::AnnotationEnd)) {
        Token key = consume(TokenType::Identifier, "Expected annotation key");
        consume(TokenType::Punctuation, "Expected '=' after annotation key");
        Token value = consume(TokenType::Constant, "Expected annotation value");
        
        annotation.attributes[key.value] = value.value;
        
        if (check(TokenType::Punctuation) && peek().value == ",") {
            advance();  // consume ','
        }
    }
    
    consume(TokenType::AnnotationEnd, "Expected ']' after annotation");
    return annotation;
}

std::string Parser::parseComment() {
    Token comment = consume(TokenType::Comment, "Expected comment");
    return comment.value;
}

Token Parser::peek() const {
    if (isAtEnd()) return {TokenType::EndOfFile, "", 0, 0};
    return tokens[current];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw ParseError(message);
}

bool Parser::isAtEnd() const {
    return current >= tokens.size() || tokens[current].type == TokenType::EndOfFile;
}

void Parser::synchronize() {
    advance();
    
    while (!isAtEnd()) {
        if (peek().type == TokenType::Punctuation && peek().value == ";") return;
        
        switch (peek().type) {
            case TokenType::Identifier:
                if (peek().value == "include" ||
                    peek().value == "namespace" ||
                    peek().value == "enum" ||
                    peek().value == "struct" ||
                    peek().value == "block") {
                    return;
                }
            default:
                advance();
        }
    }
}

}  // namespace mota