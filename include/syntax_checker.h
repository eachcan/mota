#pragma once

#include "ast.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

namespace mota {
namespace checker {

// 已知声明结构
struct KnownDecl {
    std::string namespaceName;  // 命名空间
    ast::NodeType type;         // 声明类型（直接使用AST的NodeType）
    std::string name;           // 声明名称
    std::string file;           // 所在文件
    std::shared_ptr<const ast::Node> node;      // AST节点指针
    
    // 获取完全限定名
    std::string getFullName() const {
        if (namespaceName.empty()) {
            return name;
        }
        return namespaceName + "." + name;
    }
};

// 单条语法诊断信息
struct SyntaxDiagnostic {
    enum class Level {
        Error,
        Warning,
        Info
    };
    Level level;
    std::string message;
    std::string file;
    uint32_t line = 0;
    uint32_t column = 0;
};

// 语法检查器
class SyntaxChecker {
public:
    // 主要的检查方法 - 检查文档并收集当前文档的声明
    std::vector<SyntaxDiagnostic> check(
        const ast::Document& doc, 
        const std::string& entryFile,
        const std::map<std::string, KnownDecl>& includedDeclarations,
        std::map<std::string, KnownDecl>& currentDeclarations
    );
    
    // 检查名称是否存在
    bool checkNameExists(const std::string& name, const std::string& ns, 
                        const std::map<std::string, KnownDecl>& declarations) const;
    
    // 检查类型匹配
    bool isTypeMatch(const ast::NodeType& expectedType, const std::string& typeName,
                    const std::string& ns, const std::map<std::string, KnownDecl>& declarations) const;
    
    // 检查是否是基础类型
    bool isBuiltinType(const std::string& typeName) const;
    
    // 获取完全限定名
    std::string getFullName(const std::string& name, const std::string& ns) const;
    
    // 查找声明（支持命名空间解析）
    const KnownDecl* findDeclaration(const std::string& name, const std::string& currentNamespace,
                                    const std::map<std::string, KnownDecl>& declarations) const;
    
    // 为了兼容旧代码，保留原有方法
    std::vector<SyntaxDiagnostic> check(const ast::Document& doc, const std::string& entryFile = "");
};

} // namespace checker
} // namespace mota 