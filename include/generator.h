#pragma once
#include "ast.h"
#include <string>
#include <vector>
#include <map>

namespace mota {
struct GeneratedFile {
    std::string filename;
    std::string content;
};
class CppGenerator {
public:
    CppGenerator(const std::shared_ptr<FileNode>& ast);
    
    // 生成所有文件
    std::vector<GeneratedFile> generate();

private:
    std::shared_ptr<FileNode> ast;
    std::string currentNamespace;
    
    // 生成头文件和源文件
    GeneratedFile generateHeader();
    GeneratedFile generateSource();
    
    // 类型声明生成
    std::string generateEnumDecl(const std::shared_ptr<EnumDecl>& enumDecl);
    std::string generateBlockDecl(const std::shared_ptr<BlockDecl>& blockDecl);
    std::string generateStructDecl(const std::shared_ptr<StructDecl>& structDecl);
    std::string generateFieldDecl(const std::shared_ptr<FieldDecl>& field);
    
    // 实现生成
    std::string generateEnumImpl(const std::shared_ptr<EnumDecl>& enumDecl);
    std::string generateBlockImpl(const std::shared_ptr<BlockDecl>& blockDecl);
    std::string generateStructImpl(const std::shared_ptr<StructDecl>& structDecl);
    std::string generateFieldImpl(const std::shared_ptr<FieldDecl>& field, const std::string& prefix);
    
    // 序列化相关
    std::string generateToCborImpl(const std::vector<std::shared_ptr<FieldDecl>>& fields, 
                                 const std::string& parentType = "");
    std::string generateFromCborImpl(const std::vector<std::shared_ptr<FieldDecl>>& fields,
                                   const std::string& parentType = "");
    
    // 类型转换
    std::string getCppType(const TypePtr& type);
    std::string getQtType(const TypePtr& type);
    std::string getDefaultValue(const TypePtr& type, const ExprPtr& defaultExpr);
    std::string getSerializeExpr(const std::string& fieldName, const TypePtr& type);
    std::string getDeserializeExpr(const std::string& fieldName, const TypePtr& type);
    
    // 注解处理
    std::string getStorageConfig(const std::vector<Annotation>& annotations);
    std::string getFilePath(const std::vector<Annotation>& annotations);
    std::string getFileFormat(const std::string& filePath, const std::string& formatAttr = "");
};

}
