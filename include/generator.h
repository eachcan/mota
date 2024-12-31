#pragma once
#include "ast.h"
#include <string>
#include <vector>
#include <map>

namespace mota {

class CppGenerator {
public:
    struct GeneratedFile {
        std::string filename;
        std::string content;
    };

    CppGenerator(const std::shared_ptr<FileNode>& ast);
    
    // 生成所有文件
    std::vector<GeneratedFile> generate();

private:
    std::shared_ptr<FileNode> ast;
    std::string currentNamespace;
    
    // 生成头文件
    GeneratedFile generateHeader();
    // 生成源文件
    GeneratedFile generateSource();
    
    // 辅助方法
    std::string generateEnumDecl(const std::shared_ptr<EnumDecl>& enumDecl);
    std::string generateBlockDecl(const std::shared_ptr<BlockDecl>& blockDecl);
    std::string generateStructDecl(const std::shared_ptr<StructDecl>& structDecl);
    
    std::string generateEnumImpl(const std::shared_ptr<EnumDecl>& enumDecl);
    std::string generateBlockImpl(const std::shared_ptr<BlockDecl>& blockDecl);
    std::string generateStructImpl(const std::shared_ptr<StructDecl>& structDecl);
    
    // 类型转换
    std::string getCppType(const TypePtr& type);
    std::string getDefaultValue(const TypePtr& type, const ExprPtr& defaultExpr);
    
    // 注解处理
    std::string getStorageConfig(const std::vector<Annotation>& annotations);
};

}
