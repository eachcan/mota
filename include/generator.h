#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include "ast.h"
#include "config.h"
#include "template_engine.h"
#include "file_processor.h"

namespace mota {
namespace processor {
    struct DeclarationInfo;
    using DeclarationRegistry = std::map<std::string, DeclarationInfo>;
}

namespace generator {

// 继承模板引擎的变量类型定义
using TemplateVars = template_engine::TemplateVars;

// 生成器配置（旧版兼容性）
struct GeneratorConfig {
    std::string version = "2.0";
    std::string encoding = "UTF-8";
    std::unordered_map<std::string, std::string> templates;
    std::vector<std::string> miscs;
    std::unordered_map<std::string, std::string> typeMapping;
    std::string filePath;
    std::string includeDirective;
    
    // 从新配置转换
    static GeneratorConfig fromTemplateConfig(const config::TemplateConfig& templateConfig);
};

// 代码生成器
class Generator {
public:
    Generator();
    ~Generator() = default;
    
    // 初始化生成器
    bool initialize(const std::string& templateDir, const std::string& configPath = "");
    
    // 生成代码
    std::string generateCode(const std::shared_ptr<ast::Document>& document, const std::string& templateName, bool verbose = false);
    
    // 获取配置
    const config::TemplateConfig& getConfig() const { return templateConfig_; }
    
    // 获取模板引擎
    template_engine::TemplateEngine& getTemplateEngine() { return *templateEngine_; }
    
    // 设置声明注册表
    void setDeclarationRegistry(const processor::DeclarationRegistry& registry);
    
    // 设置当前命名空间
    void setCurrentNamespace(const std::string& currentNamespace);
    
    // 类型映射方法（模板引擎需要访问）
    std::string mapType(const std::string& motaType);
    bool isBuiltinType(const std::string& type);
    bool isEnumType(const std::string& type);

private:
    // Type信息结构体
    struct TypeInfo {
        std::string name;                           // 简单名
        std::string namespace_name;                 // using_namespace
        std::string full_name;                      // using_namespace_prefix + name
        std::string class_name;                     // prefix + name + suffix
        std::string namespace_class_prefix;         // using_namespace_prefix.replace(".", separator.code)
        std::string full_class_name;                // namespace_class_prefix + class_name
        std::string relative_name;                  // relative_namespace_prefix + name
        std::string relative_class_name;            // relative_namespace_class_prefix + class_name
    };
    
    // 统一的type信息计算函数
    TypeInfo calculateTypeInfo(const std::string& originalName, const std::string& prefix, const std::string& suffix);
    
    // 构建模板变量
    TemplateVars buildTemplateVars(const std::shared_ptr<ast::Document>& document);
    
    // 数据构建方法（纯数据，无渲染逻辑）
    nlohmann::json buildNamespaceData(const std::shared_ptr<ast::Document>& document);
    nlohmann::json buildIncludesData(const std::shared_ptr<ast::Document>& document);
    nlohmann::json buildDeclarationsData(const std::shared_ptr<ast::Document>& document);
    nlohmann::json buildDeclarationData(const std::shared_ptr<ast::Node>& declaration);
    nlohmann::json buildAnnotationData(const std::shared_ptr<ast::Annotation>& annotation);
    nlohmann::json buildFieldData(const std::shared_ptr<ast::Field>& field);
    nlohmann::json buildEnumValueData(const std::shared_ptr<ast::EnumValue>& enumValue);
    nlohmann::json buildExprData(const std::shared_ptr<ast::Expr>& expr);
    nlohmann::json buildAnnotationValueData(const ast::Annotation* annotation);
    nlohmann::json buildTypedExprData(const std::shared_ptr<ast::Expr>& expr, const std::shared_ptr<ast::Type>& expectedType);
    nlohmann::json buildTypeData(const std::shared_ptr<ast::Type>& type);
    
    // 构建声明注册表数据（用于模板变量）
    nlohmann::json buildDeclarationRegistryData();
    
    // 命名空间转换方法
    std::string convertNamespaceToCode(const std::string& namespaceStr);
    
    // relative字段计算方法
    std::string calculateRelativeName(const std::string& fullName, const std::string& currentNamespace);
    std::string calculateRelativeClassName(const std::string& fullClassName, const std::string& namespaceClassPrefix);
    
    // 类型相关方法
    bool isRepeatedType(const ast::Type& type);
    bool isOptionalType(const ast::Type& type);
    bool isMapType(const ast::Type& type);
    
    // 格式化方法
    std::string toPascalCase(const std::string& str);
    std::string toCamelCase(const std::string& str);
    std::string escapeString(const std::string& str);
    
    // Namespace处理
    std::string extractNamespace(const std::shared_ptr<ast::Document>& document);
    std::string formatNamespacePath(const std::string& namespaceStr);
    
    // 时间相关
    std::string getCurrentTime();
    
private:
    config::TemplateConfig templateConfig_;
    std::shared_ptr<template_engine::TemplateEngine> templateEngine_;
    bool initialized_ = false;
    std::string templateDir_;
    
    // 声明注册表和当前命名空间
    processor::DeclarationRegistry declarationRegistryStorage_;
    processor::DeclarationRegistry* declarationRegistry_ = nullptr;
    std::string currentNamespace_;
};

} // namespace generator
} // namespace mota 