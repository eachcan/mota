#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

namespace mota {

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    
    // 解析整个文件
    std::shared_ptr<FileNode> parseFile();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;  // 当前token位置

    // 工具方法
    Token peek() const;  // 查看当前token
    Token advance();     // 移动到下一个token
    bool match(TokenType type);  // 匹配并消费token
    bool check(TokenType type) const;  // 只检查不消费
    Token consume(TokenType type, const std::string& message);  // 消费并检查
    bool isAtEnd() const;  // 是否到达结尾
    
    // 解析声明
    DeclPtr parseDeclaration();
    DeclPtr parseInclude();
    DeclPtr parseNamespace();
    DeclPtr parseEnum();
    DeclPtr parseStruct();
    DeclPtr parseBlock();

    // 解析字段
    std::shared_ptr<FieldDecl> parseField();
    
    // 解析枚举值
    std::shared_ptr<EnumValueDecl> parseEnumValue();
    
    // 解析类型
    TypePtr parseType();
    TypePtr parseBasicType();
    TypePtr parseModifiedType();
    
    // 解析表达式
    ExprPtr parseExpression();
    ExprPtr parseLiteral();
    ExprPtr parseIdentifier();
    ExprPtr parseArray();
    
    // 解析注解
    std::vector<Annotation> parseAnnotations();
    Annotation parseAnnotation();
    
    // 解析注释
    std::string parseComment();

    // 错误处理
    void synchronize();  // 错误恢复
    
    class ParseError : public std::runtime_error {
    public:
        ParseError(const std::string& message) : std::runtime_error(message) {}
    };
};

}  // namespace mota

#endif // PARSER_H