#include "../include/parser.h"
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <filesystem>
#include <fstream>

namespace mota {

Parser::Parser(const std::vector<Token>& tokens, std::shared_ptr<Config> config)
    : tokens(tokens)
    , current(0)
    , config(config ? config : std::make_shared<Config>()) 
{}

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

bool Parser::match(TokenType type, const std::string &value) {
    if (check(type, value)) {
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
    std::string fullName = resolveTypeName(name);
    return config->isTypeRegistered(fullName) && 
           config->getTypeKind(fullName) == kind;
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
    consume(TokenType::Identifier, "include", "Expected 'include' keyword");
    
    Token pathToken = consume(TokenType::Constant, "Expected file path string");
    consume(TokenType::Punctuation, ";", "Expected ';' after include statement");
    
    std::string includePath = pathToken.value.substr(1, pathToken.value.length() - 2);
    std::string resolvedPath = resolveIncludePath(includePath);
    
    auto includeDecl = std::make_shared<IncludeDecl>();
    includeDecl->path = includePath;
    
    // 解析被包含的文件
    auto includedFile = parseIncludedFile(resolvedPath);
    if (includedFile) {
        // 将被包含文件中的类型添加到类型表中，保持原始命名空间
        for (const auto& decl : includedFile->declarations) {
            if (auto enumDecl = std::dynamic_pointer_cast<EnumDecl>(decl)) {
                config->registerType(enumDecl->name, "enum", resolvedPath);
            } else if (auto structDecl = std::dynamic_pointer_cast<StructDecl>(decl)) {
                config->registerType(structDecl->name, "struct", resolvedPath);
            } else if (auto blockDecl = std::dynamic_pointer_cast<BlockDecl>(decl)) {
                config->registerType(blockDecl->name, "block", resolvedPath);
            }
        }
    }
    
    return includeDecl;
}

DeclPtr Parser::parseNamespace() {
    consume(TokenType::Identifier, "namespace", "Expected 'namespace' keyword");
    
    auto nsDecl = std::make_shared<NamespaceDecl>();
    
    // 解析命名空间路径
    Token name = consume(TokenType::Identifier, "Expected namespace name");
    nsDecl->path.push_back(name.value);
    pushNamespace(name.value);
    
    while (match(TokenType::Punctuation, ".")) {
        name = consume(TokenType::Identifier, "Expected namespace name");
        nsDecl->path.push_back(name.value);
        pushNamespace(name.value);
    }
    
    consume(TokenType::Punctuation, ";", "Expected ';' after namespace declaration");
    
    return nsDecl;
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
    consume(TokenType::Identifier, "block", "Expected 'block' keyword");
    Token name = consume(TokenType::Identifier, "Expected block name");
    
    auto blockDecl = std::make_shared<BlockDecl>();
    blockDecl->name = name.value;
    
    addDeclaredType(name.value, "block");

    // 解析继承
    if (match(TokenType::Punctuation, ":")) {
        std::string parentName;
        Token part = consume(TokenType::Identifier, "Expected parent type name");
        parentName = part.value;
        
        while (match(TokenType::Punctuation, ".")) {
            part = consume(TokenType::Identifier, "Expected parent type name");
            parentName += "." + part.value;
        }
        
        blockDecl->parentName = resolveTypeName(parentName);
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
    // 检查是否是修饰符
    if (check(TokenType::Identifier)) {
        Token token = peek();
        if (token.value == "optional" || token.value == "repeated" || token.value == "map") {
            advance(); // consume modifier
            
            auto modifiedType = std::make_shared<ModifiedTypeNode>();
            
            // 设置修饰符类型
            if (token.value == "optional") {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Optional;
            } else if (token.value == "repeated") {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Repeated;
            } else {
                modifiedType->modifier = ModifiedTypeNode::Modifier::Map;
            }
            
            // 解析基础类型
            modifiedType->baseType = parseType();
            if (!modifiedType->baseType) {
                throw ParseError("Expected type after " + token.value);
            }
            
            return modifiedType;
        }
    }
    
    // 尝试解析基本类型
    if (auto basicType = parseBasicType()) {
        return basicType;
    }
    
    // 如果不是基本类型，那就是自定义类型
    if (check(TokenType::Identifier)) {
        Token typeToken = advance();
        std::string typeName = typeToken.value;
        
        std::vector<std::string> namespaces;
        while (match(TokenType::Punctuation, ".")) {
            Token nsToken = consume(TokenType::Identifier, "Expected namespace or type name");
            namespaces.push_back(typeName);
            typeName = nsToken.value;
        }
        
        auto customType = std::make_shared<CustomTypeNode>();
        customType->name = typeName;
        customType->namespaces = namespaces;
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

void Parser::pushNamespace(const std::string& ns) {
    currentNamespace.push_back(ns);
}

void Parser::popNamespace() {
    if (!currentNamespace.empty()) {
        currentNamespace.pop_back();
    }
}

std::string Parser::resolveTypeName(const std::string& name) {
    // 如果名称已经包含命名空间，直接返回
    if (name.find('.') != std::string::npos) {
        return name;
    }
    
    // 在当前命名空间中查找
    std::string currentNs = getCurrentNamespace();
    std::string fullName = currentNs + name;
    
    if (config->isTypeRegistered(fullName)) {
        return fullName;
    }
    
    // 在全局命名空间中查找
    if (config->isTypeRegistered(name)) {
        return name;
    }
    
    return name;
}

TypePtr Parser::parseBasicType() {
    Token token = peek();
    auto basicType = std::make_shared<BasicTypeNode>();
    
    if (token.type != TokenType::Identifier) {
        throw ParseError("Expected type name");
    }

    advance(); // consume the type token
    
    // 映射基本类型名称到枚举值
    static const std::unordered_map<std::string, BasicType> typeMap = {
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
    
    auto it = typeMap.find(token.value);
    if (it == typeMap.end()) {
        // 如果不是基本类型，回退token并返回nullptr
        current--;
        return nullptr;
    }
    
    basicType->type = it->second;
    return basicType;
}

std::string Parser::resolveIncludePath(const std::string& includePath) {
    std::filesystem::path includeFsPath(includePath);
    
    // 如果是绝对路径，直接返回
    if (includeFsPath.is_absolute()) {
        return includeFsPath.make_preferred().string();
    }
    
    // 从当前文件所在目录开始查找
    if (!currentFile.empty()) {
        std::filesystem::path currentFsPath(currentFile);
        auto tryPath = currentFsPath.parent_path() / includeFsPath;
        if (std::filesystem::exists(tryPath)) {
            return tryPath.make_preferred().string();
        }
    }
    
    // 在搜索路径中查找
    for (const auto& searchPath : config->getSearchPaths()) {
        std::filesystem::path searchFsPath(searchPath);
        auto tryPath = searchFsPath / includeFsPath;
        if (std::filesystem::exists(tryPath)) {
            return tryPath.make_preferred().string();
        }
    }
    
    throw ParseError("Cannot find included file: " + includePath);
}

std::shared_ptr<FileNode> Parser::parseIncludedFile(const std::string& filepath) {
    auto state = config->getFileState(filepath);
    
    if (state == Config::FileState::Parsing) {
        throw ParseError("Circular include detected: " + filepath);
    }
    
    if (state == Config::FileState::Parsed) {
        return nullptr;
    }
    
    config->setFileState(filepath, Config::FileState::Parsing);
    
    std::string content = readFile(filepath);
    Lexer lexer(content);
    auto tokens = lexer.tokenize();
    
    auto subParser = std::make_shared<Parser>(tokens, config);  // 共享同一个 Config
    subParser->currentFile = filepath;
    subParser->parentParser = shared_from_this();
    
    auto fileNode = subParser->parseFile();
    
    config->setFileState(filepath, Config::FileState::Parsed);
    
    return fileNode;
}

std::string Parser::getCurrentNamespace() {
    std::string ns;
    for (const auto& part : currentNamespace) {
        ns += part + ".";
    }
    return ns;
}

// 实现文件读取函数
std::string readFile(const std::string& filepath) {
    std::filesystem::path fsPath(filepath);
    std::ifstream file(fsPath.make_preferred());
    if (!file.is_open()) {
        throw Parser::ParseError("Cannot open file: " + fsPath.make_preferred().string());
    }
    return std::string(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

}  // namespace mota