#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <optional>

namespace mota {
namespace ast {

// 前向声明
class Node;
class Expr;
class Type;
class Annotation;
class AnnotationArgument;
class Statement;
class Field;
class EnumValue;
class Block;
class Struct;
class Enum;
class Namespace;
class Include;

// 节点类型
enum class NodeType {
    // 表达式
    Identifier, 
    Literal,
    BinaryOp,
    UnaryOp,
    MemberAccess,
    
    // 类型
    NamedType,
    ContainerType,
    OptionalType,
    
    // 语句
    FieldDecl,
    EnumValueDecl,
    
    // 顶层声明
    AnnotationDecl,
    BlockDecl,
    StructDecl,
    EnumDecl,
    NamespaceDecl,
    IncludeDecl,
    
    // 其他
    Annotation,
    AnnotationArgument,
};

// 基础节点类
class Node {
public:
    virtual ~Node() = default;
    virtual NodeType nodeType() const = 0;
    
    // 源代码位置信息
    struct SourceLocation {
        std::string filename;
        uint32_t line = 0;
        uint32_t column = 0;
    };
    
    SourceLocation location;
};

// 表达式基类
class Expr : public Node {
public:
    NodeType nodeType() const override { return NodeType::Identifier; }
};

// 标识符
class Identifier : public Expr {
public:
    explicit Identifier(std::string name) : name(std::move(name)) {}
    
    std::string name;
};

// 字面量
class Literal : public Expr {
public:
    using ValueType = std::variant<
        std::monostate,  // 无值
        bool,            // 布尔值
        int64_t,         // 整型
        double,          // 浮点型
        std::string      // 字符串
    >;
    
    explicit Literal(ValueType value) : value(std::move(value)) {}
    
    ValueType value;
};

// 二元操作符
class BinaryOp : public Expr {
public:
    enum class Op {
        Add, Sub, Mul, Div, Mod,
        Eq, Ne, Lt, Le, Gt, Ge,
        And, Or, Xor, Shl, Shr
    };
    
    BinaryOp(Op op, std::unique_ptr<Expr> lhs, std::unique_ptr<Expr> rhs)
        : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    
    Op op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

// 一元操作符
class UnaryOp : public Expr {
public:
    enum class Op {
        Plus, Minus, Not, BitNot
    };
    
    UnaryOp(Op op, std::unique_ptr<Expr> operand)
        : op(op), operand(std::move(operand)) {}
    
    Op op;
    std::unique_ptr<Expr> operand;
};

// 成员访问
class MemberAccess : public Expr {
public:
    MemberAccess(std::unique_ptr<Expr> object, std::string member)
        : object(std::move(object)), member(std::move(member)) {}
    
    std::unique_ptr<Expr> object;
    std::string member;
};

// 类型基类
class Type : public Node {
public:
    virtual ~Type() = default;
    NodeType nodeType() const override { return NodeType::NamedType; }
};

// 命名类型
class NamedType : public Type {
public:
    explicit NamedType(std::string name) : name(std::move(name)) {}
    
    std::string name;
};

// 容器类型
class ContainerType : public Type {
public:
    enum class Kind {
        Array,      // repeated
        Map,        // map
        Optional    // optional
    };
    
    ContainerType(Kind kind, std::unique_ptr<Type> elementType)
        : kind(kind), elementType(std::move(elementType)) {}
    
    Kind kind;
    std::unique_ptr<Type> elementType;
    std::unique_ptr<Type> keyType;  // 仅用于Map
};

// 注解参数
class AnnotationArgument {
public:
    std::string name;
    std::unique_ptr<Expr> value;
};

// 注解
class Annotation : public Node {
public:
    Annotation(std::string name, std::vector<AnnotationArgument> args = {})
        : name(std::move(name)), arguments(std::move(args)) {}
    
    std::string name;
    std::vector<AnnotationArgument> arguments;
    
    NodeType nodeType() const override { return NodeType::Annotation; }
};

// 字段声明
class Field : public Node {
public:
    Field(std::string name, std::unique_ptr<Type> type, std::unique_ptr<Expr> defaultValue = nullptr)
        : name(std::move(name)), type(std::move(type)), defaultValue(std::move(defaultValue)) {}
    
    std::string name;
    std::unique_ptr<Type> type;
    std::unique_ptr<Expr> defaultValue;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::FieldDecl; }
};

// 枚举值
class EnumValue : public Node {
public:
    EnumValue(std::string name, std::unique_ptr<Expr> value = nullptr)
        : name(std::move(name)), value(std::move(value)) {}
    
    std::string name;
    std::unique_ptr<Expr> value;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::EnumValueDecl; }
};

// 块定义
class Block : public Node {
public:
    explicit Block(std::string name) : name(std::move(name)) {}
    
    std::string name;
    std::vector<std::unique_ptr<Field>> fields;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::BlockDecl; }
};

// 结构体定义
class Struct : public Node {
public:
    explicit Struct(std::string name) : name(std::move(name)) {}
    
    std::string name;
    std::vector<std::unique_ptr<Field>> fields;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::StructDecl; }
};

// 枚举定义
class Enum : public Node {
public:
    explicit Enum(std::string name) : name(std::move(name)) {}
    
    std::string name;
    std::vector<std::unique_ptr<EnumValue>> values;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::EnumDecl; }
};

// 命名空间
class Namespace : public Node {
public:
    explicit Namespace(std::vector<std::string> name) : name(std::move(name)) {}
    
    std::vector<std::string> name;  // 完全限定名
    std::vector<std::unique_ptr<Node>> declarations;
    
    NodeType nodeType() const override { return NodeType::NamespaceDecl; }
};

// 包含声明
class Include : public Node {
public:
    explicit Include(std::string path) : path(std::move(path)) {}
    
    std::string path;
    
    NodeType nodeType() const override { return NodeType::IncludeDecl; }
};

// 文档根节点
class Document {
public:
    std::vector<std::unique_ptr<Node>> declarations;
    std::map<std::string, std::string> includes;  // 已包含的文件路径
};

} // namespace ast
} // namespace mota
