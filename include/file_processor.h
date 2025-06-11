#pragma once

#include "ast.h"
#include "syntax_checker.h"
#include "template_engine.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

namespace mota {
namespace processor {

// 声明注册表结构，包含完整的类型信息
struct DeclarationInfo {
    std::string name;                     // 原始名称
    std::string qualified_name;           // 完全限定名
    std::string class_name;               // 生成的类名（带后缀）
    std::string type;                     // 声明类型：struct|block|enum|annotation_decl
    std::string namespace_name;           // 命名空间
    std::string file_path;                // 所在文件路径
    const ast::Node* node;                // AST节点指针
    
    // 获取相对于指定命名空间的类型名称
    std::string getRelativeTypeName(const std::string& currentNamespace) const {
        if (currentNamespace == namespace_name) {
            return class_name; // 同命名空间返回简单类名
        }
        return class_name; // 返回完整类名（已包含前后缀）
    }
};

using DeclarationRegistry = std::map<std::string, DeclarationInfo>;

// 文件处理器类
class FileProcessor {
public:
    // 主要的处理方法
    bool processMotaFile(
        const std::string& inputFile,
        const std::string& outputDir,
        const std::string& templateDir,
        const std::vector<std::string>& includePaths,
        bool verbose = false
    );

private:
    // 构建包含注册表 - 收集所有包含文件及其声明
    void buildIncludeRegistry(
        const ast::Document& root,
        const std::string& rootFile,
        std::set<std::string>& includedFiles,
        const std::vector<std::string>& includePaths,
        std::map<std::string, checker::KnownDecl>& includedDeclarations,
        bool verbose
    );
    
    // 构建声明注册表
    void buildDeclarationRegistry(
        const std::map<std::string, checker::KnownDecl>& includedDeclarations,
        const std::map<std::string, checker::KnownDecl>& currentDeclarations,
        DeclarationRegistry& registry,
        const config::TemplateConfig& config
    );
    
    // 读取文件内容
    std::string readFile(const std::string& filePath) const;
    
    // 解析文件
    std::unique_ptr<ast::Document> parseFile(const std::string& filePath) const;
    
    // 获取文档直接包含的文件路径
    std::vector<std::string> getDirectIncludes(const ast::Document& doc) const;
    
    // 解析绝对路径
    std::string getAbsolutePath(const std::string& includePath, 
                               const std::vector<std::string>& includePaths,
                               const std::string& currentFileDir) const;
    
    // 合并声明映射
    void mergeDeclarations(
        std::map<std::string, checker::KnownDecl>& target,
        const std::map<std::string, checker::KnownDecl>& source
    ) const;
};

} // namespace processor
} // namespace mota 