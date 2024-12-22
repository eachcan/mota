#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <variant>

namespace mota {

// 前向声明
class Node;
class Expression;
class Type;
class Statement;
class Declaration;

using NodePtr = std::shared_ptr<Node>;
using ExprPtr = std::shared_ptr<Expression>;
using TypePtr = std::shared_ptr<Type>;
using StmtPtr = std::shared_ptr<Statement>;
using DeclPtr = std::shared_ptr<Declaration>;

// 基础节点类型
class Node {
public:
    virtual ~Node() = default;
    int line = 0;
    int column = 0;
};

// 注解属性
struct Annotation {
    std::map<std::string, std::string> attributes;
};

// 基本类型
enum class BasicType {
    Int8,
    Int16,
    Int32,
    Int64,
    Float32,
    Double64,
    String,
    Bool,
    Bytes
};

// 类型定义
class Type : public Node {
public:
    virtual ~Type() = default;
};

// 基本类型节点
class BasicTypeNode : public Type {
public:
    BasicType type;
};

// 自定义类型节点
class CustomTypeNode : public Type {
public:
    std::string name;
};

// 修饰类型节点
class ModifiedTypeNode : public Type {
public:
    enum class Modifier {
        Optional,
        Map,
        Repeated
    };
    Modifier modifier;
    TypePtr baseType;
};

// 表达式基类
class Expression : public Node {
public:
    virtual ~Expression() = default;
};

// 字面量表达式
class LiteralExpr : public Expression {
public:
    std::variant<int64_t, double, bool, std::string> value;
};

// 标识符表达式
class IdentifierExpr : public Expression {
public:
    std::string name;
};

// 数组表达式
class ArrayExpr : public Expression {
public:
    std::vector<ExprPtr> elements;
};

// 声明基类
class Declaration : public Node {
public:
    virtual ~Declaration() = default;
    std::string name;
    std::vector<Annotation> annotations;
    std::string comment;
};

// 字段声明
class FieldDecl : public Declaration {
public:
    TypePtr type;
    std::string name;
    ExprPtr defaultValue;
    std::vector<Annotation> annotations;
    std::string comment;  // 块注释
};

// 枚举项声明
class EnumValueDecl : public Declaration {
public:
    std::string name;
    int64_t value = 0;  // 默认值为0
    std::vector<Annotation> annotations;
    std::string comment;
};

// 枚举声明
class EnumDecl : public Declaration {
public:
    std::vector<std::shared_ptr<EnumValueDecl>> values;
};

// 结构体声明
class StructDecl : public Declaration {
public:
    std::vector<std::shared_ptr<FieldDecl>> fields;
    std::string parentType;  // "struct" 或 "block"
    std::string parentName;  // 父类名称
    bool hasParent() const { return !parentName.empty(); }
};

// Block声明
class BlockDecl : public Declaration {
public:
    std::vector<std::shared_ptr<FieldDecl>> fields;
    std::string parentName;  // 父类名称（只能是 block）
    bool hasParent() const { return !parentName.empty(); }
};

// 命名空间声明
class NamespaceDecl : public Declaration {
public:
    std::vector<std::string> path;  // 命名空间路径，如 a.b.c
};

// Include声明
class IncludeDecl : public Declaration {
public:
    std::string path;  // 包含文件的路径
};

// 文件的根节点
class FileNode : public Node {
public:
    std::vector<DeclPtr> declarations;
};

}  // namespace mota

#endif // AST_H