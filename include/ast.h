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
class AnnotationDecl;
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
    ArrayLiteral,
    BinaryOp,
    UnaryOp,
    MemberAccess,
    
    // 类型
    NamedType,
    ContainerType,
    
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
    Document,
    
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
    // 纯虚函数，强制子类实现
    NodeType nodeType() const override = 0;
};

// 标识符
class Identifier : public Expr {
public:
    explicit Identifier(std::string name) : name(std::move(name)) {}
    
    NodeType nodeType() const override { return NodeType::Identifier; }
    
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
    
    NodeType nodeType() const override { return NodeType::Literal; }
    
    ValueType value;
};

// 数组字面量
class ArrayLiteral : public Expr {
public:
    explicit ArrayLiteral(std::vector<std::unique_ptr<Expr>> elements = {})
        : elements(std::move(elements)) {}
    
    NodeType nodeType() const override { return NodeType::ArrayLiteral; }
    
    std::vector<std::unique_ptr<Expr>> elements;
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
    
    NodeType nodeType() const override { return NodeType::BinaryOp; }
    
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
    
    NodeType nodeType() const override { return NodeType::UnaryOp; }
    
    Op op;
    std::unique_ptr<Expr> operand;
};

// 成员访问
class MemberAccess : public Expr {
public:
    MemberAccess(std::unique_ptr<Expr> object, std::string member)
        : object(std::move(object)), member(std::move(member)) {}
    
    NodeType nodeType() const override { return NodeType::MemberAccess; }
    
    std::unique_ptr<Expr> object;
    std::string member;
};

// 类型基类
class Type : public Node {
public:
    virtual ~Type() = default;
    virtual std::string toString() const = 0;
};

// 命名类型
class NamedType : public Type {
public:
    explicit NamedType(std::string name) : name(std::move(name)) {}
    
    std::string name;
    
    std::string toString() const override { return name; }
    NodeType nodeType() const override { return NodeType::NamedType; }
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
    
    std::string toString() const override {
        switch(kind) {
            case Kind::Array: return "repeated " + elementType->toString();
            case Kind::Optional: return "optional " + elementType->toString();
            case Kind::Map: 
                if (keyType) {
                    return "map<" + keyType->toString() + ", " + elementType->toString() + ">";
                } else {
                    return "map " + elementType->toString();
                }
            default: return "unknown";
        }
    }
    
    NodeType nodeType() const override { return NodeType::ContainerType; }
};

// 注解参数 - 现在继承自Node
class AnnotationArgument : public Node {
public:
    AnnotationArgument(std::string name, std::unique_ptr<Expr> value)
        : name(std::move(name)), value(std::move(value)) {}
    
    std::string name;
    std::unique_ptr<Expr> value;
    
    NodeType nodeType() const override { return NodeType::AnnotationArgument; }
};

// 注解
class Annotation : public Expr {
public:
    Annotation(std::string name, std::vector<std::unique_ptr<AnnotationArgument>> args = {})
        : name(std::move(name)), arguments(std::move(args)) {}
    
    std::string name;
    std::vector<std::unique_ptr<AnnotationArgument>> arguments;
    
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
    explicit Block(std::string name, std::string baseName = "") : name(std::move(name)), baseName(std::move(baseName)) {}
    
    std::string name;
    std::string baseName; // 继承的父 block 名称
    std::vector<std::unique_ptr<Field>> fields;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::BlockDecl; }
};

// 结构体定义
class Struct : public Node {
public:
    explicit Struct(std::string name, std::string baseName = "") : name(std::move(name)), baseName(std::move(baseName)) {}
    
    std::string name;
    std::string baseName; // 继承的父 block 名称（仅 struct 支持继承 block）
    std::vector<std::unique_ptr<Field>> fields;
    std::vector<std::unique_ptr<Annotation>> annotations;
    
    NodeType nodeType() const override { return NodeType::StructDecl; }
};

// 注解声明 - 添加baseName支持继承
class AnnotationDecl : public Node {
public:
    explicit AnnotationDecl(std::string name, std::string baseName = "") 
        : name(std::move(name)), baseName(std::move(baseName)) {}
    
    std::string name;
    std::string baseName;  // 继承的父注解名称
    std::vector<std::unique_ptr<Field>> fields;  // 注解字段
    
    NodeType nodeType() const override { return NodeType::AnnotationDecl; }
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
    
    NodeType nodeType() const override { return NodeType::NamespaceDecl; }
};

// 包含声明
class Include : public Node {
public:
    explicit Include(std::string path) : path(std::move(path)) {}
    
    std::string path;
    
    NodeType nodeType() const override { return NodeType::IncludeDecl; }
};

// 文档根节点 - 重新设计结构
class Document : public Node {
public:
    Document() = default;
    
    // 顶层声明（struct、block、enum、annotation）
    std::vector<std::unique_ptr<Node>> declarations;
    
    // 命名空间（一个文件只能有0个或1个）
    std::unique_ptr<Namespace> m_namespace;
    
    // 包含声明（可以有多个）
    std::vector<std::unique_ptr<Include>> includes;
    
    NodeType nodeType() const override { return NodeType::Document; } // 使用现有的枚举值
    
    // 检查是否已经开始解析声明
    bool hasDeclarations() const { return !declarations.empty(); }
    
    // 检查是否已经设置了命名空间
    bool hasNamespace() const { return m_namespace != nullptr; }
};

} // namespace ast
} // namespace mota
