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