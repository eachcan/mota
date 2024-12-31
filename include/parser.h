#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <map>
#include "config.h"
namespace mota {

// 文件读取函数声明
std::string readFile(const std::string& filepath);

class Parser : public std::enable_shared_from_this<Parser> {
public:
    Parser(const std::vector<Token>& tokens, std::shared_ptr<Config> config = nullptr);
    
    // 解析整个文件
    std::shared_ptr<FileNode> parseFile();

private:
    std::vector<Token> tokens;
    int current = 0;  // 当前token位置

    // 记录已声明的类型
    struct DeclaredType {
        std::string name;
        std::string kind;  // "struct", "block", "enum"
        std::vector<std::string> fieldNames;  // 该类型中的字段名
    };
    std::vector<DeclaredType> declaredTypes;

    std::vector<std::string> currentNamespace;  // 当前命名空间栈
    std::map<std::string, std::vector<std::string>> includedTypes;  // 记录include的类型及其命名空间

    // 工具方法
    Token peek() const;  // 查看当前token
    Token previous() const;  // 查看前一个token
    Token advance();     // 移动到下一个token
    bool match(TokenType type);  // 匹配并消费token
    bool match(TokenType type, const std::string& value);  // 匹配并消费token
    bool check(TokenType type) const;  // 只检查不消费
    bool check(TokenType type, const std::string& value) const;  // 只检查不消费
    Token consume(TokenType type, const std::string& message);  // 消费并检查
    Token consume(TokenType type, const std::string& value, const std::string& message);  // 消费并检查
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
    
    // 类型检查辅助函数
    bool isDeclaredType(const std::string& name, const std::string& kind);
    bool isTypeNameUsed(const std::string& name);
    bool isFieldNameUsed(const std::string& typeName, const std::string& fieldName);
    void addDeclaredType(const std::string& name, const std::string& kind);
    void addFieldToType(const std::string& typeName, const std::string& fieldName);

    // 辅助方法
    void pushNamespace(const std::string& ns);
    void popNamespace();
    std::string resolveTypeName(const std::string& name);  // 解析类型的完整名称

    // 添加新的成员
    std::string currentFile;  // 当前正在解析的文件
    std::shared_ptr<Parser> parentParser;  // 用于追踪包含链

    // 新增方法
    std::string resolveIncludePath(const std::string& includePath);
    std::shared_ptr<FileNode> parseIncludedFile(const std::string& filepath);

    std::string getCurrentNamespace();
    
    std::shared_ptr<Config> config;

public:    
    class ParseError : public std::runtime_error {
    public:
        ParseError(const std::string& message) : std::runtime_error(message) {}
    };

};

}  // namespace mota

#endif // PARSER_H