#include "../include/parser.h"
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "parser.h"

namespace mota {

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

bool Parser::isAtEnd() const {
    return current >= tokens.size() - 1;
}

Token Parser::peek() const {
    if (isAtEnd()) {
        return Token{TokenType::EndOfFile, "", 0};
    }
    return tokens[current];
}

Token Parser::previous() const {
    if (current == 0) {
        return Token{TokenType::EndOfFile, "", 0};
    }
    return tokens[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) {
        current++;
    }
    return previous();
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) {
        return false;
    }
    return peek().type == type;
}

bool Parser::check(TokenType type, const std::string &value) const
{
    if (isAtEnd()) {
        return false;
    }
    auto token = peek();
    return token.type == type && token.value == value;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return advance();
    }
    throw ParseError(message);
}

Token Parser::consume(TokenType type, const std::string &value, const std::string &message)
{
    auto token = peek();
    if (check(type, value)) {
        return advance();
    }
    throw ParseError(message);
}
void Parser::synchronize()
{
    advance();
    while (!isAtEnd()) {
        if (previous().type == TokenType::Punctuation && previous().value == ";") {
            return;
        }
        switch (peek().type) {
            case TokenType::Identifier:
                if (peek().value == "struct" || 
                    peek().value == "block" || 
                    peek().value == "enum" || 
                    peek().value == "namespace" || 
                    peek().value == "include") {
                    return;
                }
                break;
            default:
                break;
        }
        advance();
    }
}

bool Parser::isDeclaredType(const std::string& name, const std::string& kind) {
    for (const auto& type : declaredTypes) {
        if (type.name == name && type.kind == kind) {
            return true;
        }
    }
    return false;
}

bool Parser::isTypeNameUsed(const std::string& name) {
    for (const auto& type : declaredTypes) {
        if (type.name == name) {
            return true;
        }
    }
    return false;
}

bool Parser::isFieldNameUsed(const std::string& typeName, const std::string& fieldName) {
    for (auto& type : declaredTypes) {
        if (type.name == typeName) {
            for (const auto& field : type.fieldNames) {
                if (field == fieldName) {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

void Parser::addDeclaredType(const std::string& name, const std::string& kind) {
    if (isTypeNameUsed(name)) {
        throw ParseError("Type name '" + name + "' is already used");
    }
    declaredTypes.push_back({name, kind, {}});
}

void Parser::addFieldToType(const std::string& typeName, const std::string& fieldName) {
    for (auto& type : declaredTypes) {
        if (type.name == typeName) {
            if (isFieldNameUsed(typeName, fieldName)) {
                throw ParseError("Field name '" + fieldName + "' is already used in type '" + typeName + "'");
            }
            type.fieldNames.push_back(fieldName);
            return;
        }
    }
}

std::shared_ptr<FileNode> Parser::parseFile() {
    auto file = std::make_shared<FileNode>();
    
    while (!isAtEnd()) {
        try {
            auto decl = parseDeclaration();
            if (decl) {
                file->declarations.push_back(decl);
            } else {
                if (isAtEnd()) {
                    break;
                } else {
                    throw ParseError("Expected declaration");
                }
            }
        } catch (const ParseError& error) {
            std::cerr << error.what() << std::endl;
            break;
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
        if (check(TokenType::Punctuation) && peek().value == ".") {
            advance();  // consume '.'
        } else {
            break;
        }
    } while (true);
    
    consume(TokenType::Punctuation, "Expected ';' after namespace declaration");
    return ns;
}

DeclPtr Parser::parseEnum() {
    consume(TokenType::Identifier, "enum", "Expected 'enum'");
    Token name = consume(TokenType::Identifier, "Expected enum name");
    
    auto enumDecl = std::make_shared<EnumDecl>();
    enumDecl->name = name.value;
    
    // 记录枚举类型
    addDeclaredType(name.value, "enum");
    
    consume(TokenType::Punctuation, "{", "Expected '{' after enum name");
    
    while (!check(TokenType::Punctuation, "}")) {
        auto value = parseEnumValue();
        // 检查枚举值名称是否重复
        addFieldToType(name.value, value->name);
        enumDecl->values.push_back(value);
    }
    
    consume(TokenType::Punctuation, "}", "Expected '}' after enum values");
    return enumDecl;
}

std::shared_ptr<EnumValueDecl> Parser::parseEnumValue() {
    auto value = std::make_shared<EnumValueDecl>();
    
    // 解析注解
    value->annotations = parseAnnotations();
    
    // 解析枚举值名称
    Token name = consume(TokenType::Identifier, "Expected enum value name");
    value->name = name.value;
    
    // 检查是否有默认值
    if (check(TokenType::Punctuation, "=")) {
        advance(); // consume '='
        auto literal = parseLiteral();
        auto literalExpr = std::dynamic_pointer_cast<LiteralExpr>(literal);
        if (!literalExpr) {
            throw ParseError("Expected literal value for enum");
        }
        value->value = std::get<int64_t>(literalExpr->value);
    }
    
    // 必须有分号
    consume(TokenType::Punctuation, ";", "Expected ';' after enum value");
    
    return value;
}

DeclPtr Parser::parseStruct() {
    consume(TokenType::Identifier, "struct", "Expected 'struct'");
    Token name = consume(TokenType::Identifier, "Expected struct name");
    
    auto structDecl = std::make_shared<StructDecl>();
    structDecl->name = name.value;
    
    // 记录结构体类型
    addDeclaredType(name.value, "struct");

    // 检查是否有继承
    if (check(TokenType::Punctuation, ":")) {
        advance();  // consume ':'
        
        // 解析父类名称
        Token parentName = consume(TokenType::Identifier, "Expected parent type name");
        
        // 检查父类是否存在
        if (!isDeclaredType(parentName.value, "struct") && !isDeclaredType(parentName.value, "block")) {
            throw ParseError("Parent type '" + parentName.value + "' not found");
        }
        
        // 确定父类类型
        if (isDeclaredType(parentName.value, "struct")) {
            structDecl->parentType = "struct";
        } else {
            structDecl->parentType = "block";
        }
        structDecl->parentName = parentName.value;
    }
    
    consume(TokenType::Punctuation, "{", "Expected '{' after struct name");
    
    while (!check(TokenType::Punctuation, "}")) {
        auto field = parseField();
        // 检查字段名是否重复
        addFieldToType(name.value, field->name);
        structDecl->fields.push_back(field);
        
        consume(TokenType::Punctuation, ";", "Expected ';' after struct field");
    }
    
    consume(TokenType::Punctuation, "}", "Expected '}' after struct fields");
    return structDecl;
}

DeclPtr Parser::parseBlock() {
    consume(TokenType::Identifier, "block", "Expected 'block'");
    Token name = consume(TokenType::Identifier, "Expected block name");
    
    auto blockDecl = std::make_shared<BlockDecl>();
    blockDecl->name = name.value;
    
    // 记录块类型
    addDeclaredType(name.value, "block");

    // 检查是否有继承
    if (check(TokenType::Punctuation, ":")) {
        advance();  // consume ':'
        
        // 解析父类名称
        Token parentName = consume(TokenType::Identifier, "Expected parent block name");
        
        // 检查父类是否存在
        if (!isDeclaredType(parentName.value, "block")) {
            throw ParseError("Parent block '" + parentName.value + "' not found or not a block");
        }
        
        blockDecl->parentName = parentName.value;
    }
    
    consume(TokenType::Punctuation, "{", "Expected '{' after block name");
    
    while (!check(TokenType::Punctuation, "}")) {
        auto field = parseField();
        // 检查字段名是否重复
        addFieldToType(name.value, field->name);
        blockDecl->fields.push_back(field);
        
        consume(TokenType::Punctuation, ";", "Expected ';' after block field");
    }
    
    consume(TokenType::Punctuation, "}", "Expected '}' after block fields");
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
    
    if (check(TokenType::Punctuation) && peek().value == "=") {
        advance();  // consume '='
        field->defaultValue = parseExpression();
    }
    
    return field;
}

TypePtr Parser::parseType() {
    if (check(TokenType::Identifier)) {
        Token modifier = advance();
        if (modifier.value == "optional" || 
            modifier.value == "map" || 
            modifier.value == "repeated") {
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
        
        // 检查自定义类型是否存在
        if (!isDeclaredType(customType->name, "struct") && 
            !isDeclaredType(customType->name, "block") && 
            !isDeclaredType(customType->name, "enum")) {
            throw ParseError("Type '" + customType->name + "' not found");
        }
        
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
            if (check(TokenType::Punctuation) && peek().value == "]") {
                advance();  // consume ']'
                break;
            } else if (check(TokenType::Punctuation) && peek().value == ",") {
                advance();  // consume ','
            }
        } while (true);
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
        Token v = peek();
        Token value = consume(TokenType::Constant, "Expected annotation value: " + v.value + " of key: " + key.value);
        
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

struct DeclaredType {
    std::string name;
    std::string kind;
    std::vector<std::string> fieldNames;
};

std::vector<DeclaredType> declaredTypes;

}  // namespace mota