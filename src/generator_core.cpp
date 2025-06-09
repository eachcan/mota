#include "generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <filesystem>

namespace mota {
namespace generator {

GeneratorConfig GeneratorConfig::fromTemplateConfig(const config::TemplateConfig& templateConfig) {
    GeneratorConfig config;
    config.version = templateConfig.version;
    config.encoding = templateConfig.encoding;
    config.templates = templateConfig.templates;
    config.miscs = templateConfig.miscs;
    config.typeMapping = templateConfig.type_mapping;
    
    // 简化文件路径和包含指令
    if (!templateConfig.file_path.empty()) {
        config.filePath = templateConfig.file_path[0].path;
    }
    config.includeDirective = templateConfig.include_directive.pattern;
    
    return config;
}

Generator::Generator() = default;

bool Generator::initialize(const std::string& templateDir, const std::string& configPath) {
    templateDir_ = templateDir;
    
    // 加载模板配置
    std::string actualConfigPath = configPath;
    if (actualConfigPath.empty()) {
        actualConfigPath = templateDir + "/config.json5";
        // 如果json5不存在，尝试json
        if (!std::filesystem::exists(actualConfigPath)) {
            actualConfigPath = templateDir + "/config.json";
        }
    }
    
    if (!templateConfig_.loadFromFile(actualConfigPath)) {
        std::cerr << "Failed to load template config from: " << actualConfigPath << std::endl;
        return false;
    }
    
    // 创建模板引擎
    templateEngine_ = std::make_unique<template_engine::TemplateEngine>(templateConfig_, templateDir_);
    
    initialized_ = true;
    return true;
}

bool Generator::initializeWithConfig(const config::TemplateConfig& templateConfig, const std::string& templateDir) {
    templateConfig_ = templateConfig;
    templateDir_ = templateDir;
    
    // 创建模板引擎
    templateEngine_ = std::make_unique<template_engine::TemplateEngine>(templateConfig_, templateDir_);
    
    initialized_ = true;
    return true;
}

std::string Generator::generateCode(const std::unique_ptr<ast::Document>& document, const std::string& templateName) {
    if (!initialized_) {
        std::cerr << "Generator not initialized" << std::endl;
        return "";
    }
    
    // 构建模板变量
    TemplateVars vars = buildTemplateVars(document);
    
    // 使用模板引擎渲染
    return templateEngine_->renderTemplate(templateName, vars);
}

bool Generator::generateToFile(const std::unique_ptr<ast::Document>& document, 
                              const std::string& templateName, 
                              const std::string& outputPath) {
    std::string code = generateCode(document, templateName);
    if (code.empty()) {
        return false;
    }
    
    // 确保输出目录存在
    std::filesystem::path outputPathObj(outputPath);
    std::filesystem::create_directories(outputPathObj.parent_path());
    
    // 写入文件
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        std::cerr << "Cannot create output file: " << outputPath << std::endl;
        return false;
    }
    
    outFile << code;
    outFile.close();
    
    return true;
}

TemplateVars Generator::buildTemplateVars(const std::unique_ptr<ast::Document>& document) {
    TemplateVars vars;
    
    // 基本信息
    vars["GENERATION_TIME"] = getCurrentTime();
    vars["SOURCE_FILE"] = "document.mota"; // 可以从参数传入
    
    // 处理命名空间
    std::string namespaceStr = extractNamespace(document);
    vars["NAMESPACE"] = namespaceStr;
    vars["NAMESPACE_PATH"] = formatNamespacePath(namespaceStr);
    vars["HAS_NAMESPACE"] = namespaceStr.empty() ? "false" : "true";
    
    // 分割namespace为各个部分，用于嵌套声明
    if (!namespaceStr.empty()) {
        std::vector<std::string> namespaceParts;
        std::stringstream ss(namespaceStr);
        std::string part;
        while (std::getline(ss, part, '.')) {
            namespaceParts.push_back(part);
        }
        
        // 构建NAMESPACE_PARTS数据为JSON数组
        nlohmann::json partsArray = nlohmann::json::array();
        for (size_t i = 0; i < namespaceParts.size(); ++i) {
            nlohmann::json partObj = {
                {"name", namespaceParts[i]},
                {"index", i},
                {"is_first", i == 0},
                {"is_last", i == namespaceParts.size() - 1}
            };
            partsArray.push_back(partObj);
        }
        vars["NAMESPACE_PARTS"] = partsArray;
    } else {
        vars["NAMESPACE_PARTS"] = nlohmann::json::array();
    }
    
    // 处理Include声明
    std::vector<std::string> includeContents;
    for (const auto& include : document->includes) {
        // 根据配置转换路径
        std::string includePath = include->path;
        // 如果有源扩展名配置，则替换扩展名
        if (!templateConfig_.include_directive.source_extension.empty() && 
            !templateConfig_.include_directive.target_extension.empty()) {
            std::string sourceExt = templateConfig_.include_directive.source_extension;
            std::string targetExt = templateConfig_.include_directive.target_extension;
            if (includePath.size() >= sourceExt.size() && 
                includePath.substr(includePath.size() - sourceExt.size()) == sourceExt) {
                includePath = includePath.substr(0, includePath.size() - sourceExt.size()) + targetExt;
            }
        }
        
        // 生成include指令
        std::string includeLine = "#include \"" + includePath + "\"";
        includeContents.push_back(includeLine);
    }
    
    std::string includesStr;
    for (size_t i = 0; i < includeContents.size(); ++i) {
        if (i > 0) includesStr += "\n";
        includesStr += includeContents[i];
    }
    vars["INCLUDES"] = includesStr;
    vars["HAS_INCLUDES"] = includeContents.empty() ? "false" : "true";
    
    // 收集各种类型的声明并生成代码
    std::vector<std::string> contents;
    
    for (const auto& decl : document->declarations) {
        switch (decl->nodeType()) {
            case ast::NodeType::AnnotationDecl: {
                auto annotation = static_cast<const ast::AnnotationDecl*>(decl.get());
                std::string annotationCode = generateAnnotationDecl(*annotation);
                if (!annotationCode.empty()) {
                    contents.push_back(annotationCode);
                }
                break;
            }
            case ast::NodeType::StructDecl: {
                auto struct_ = static_cast<const ast::Struct*>(decl.get());
                std::string structCode = generateStructDecl(*struct_);
                if (!structCode.empty()) {
                    contents.push_back(structCode);
                }
                break;
            }
            case ast::NodeType::BlockDecl: {
                auto block = static_cast<const ast::Block*>(decl.get());
                std::string blockCode = generateBlockDecl(*block);
                if (!blockCode.empty()) {
                    contents.push_back(blockCode);
                }
                break;
            }
            case ast::NodeType::EnumDecl: {
                auto enum_ = static_cast<const ast::Enum*>(decl.get());
                std::string enumCode = generateEnumDecl(*enum_);
                if (!enumCode.empty()) {
                    contents.push_back(enumCode);
                }
                break;
            }
            default:
                // 忽略其他类型的声明
                break;
        }
    }
    
    // 合并所有内容
    std::string content;
    for (size_t i = 0; i < contents.size(); ++i) {
        if (i > 0) content += "\n\n";
        content += contents[i];
    }
    vars["CONTENT"] = content;
    
    // 添加描述信息（默认值）
    vars["DESCRIPTION"] = "DESCRIPTION";
    
    return vars;
}

std::string Generator::extractNamespace(const std::unique_ptr<ast::Document>& document) {
    // 从document中提取namespace
    if (document->hasNamespace()) {
        std::string namespaceStr = "";
        for (size_t i = 0; i < document->m_namespace->name.size(); ++i) {
            if (i > 0) namespaceStr += ".";
            namespaceStr += document->m_namespace->name[i];
        }
        return namespaceStr;
    }
    return "";
}

std::string Generator::formatNamespacePath(const std::string& namespaceStr) {
    if (namespaceStr.empty()) return "";
    
    std::string result = namespaceStr;
    std::replace(result.begin(), result.end(), '.', '/');
    return result;
}

std::string Generator::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Generator::mapType(const std::string& motaType) {
    auto it = templateConfig_.type_mapping.find(motaType);
    if (it != templateConfig_.type_mapping.end()) {
        return it->second;
    }
    return motaType;
}

bool Generator::isBuiltinType(const std::string& type) {
    static const std::vector<std::string> builtinTypes = {
        "string", "int32", "int64", "float", "double", "bool", "bytes"
    };
    return std::find(builtinTypes.begin(), builtinTypes.end(), type) != builtinTypes.end();
}

bool Generator::isRepeatedType(const ast::Type& type) {
    // 检查是否为数组类型
    if (type.nodeType() == ast::NodeType::ContainerType) {
        const auto& containerType = static_cast<const ast::ContainerType&>(type);
        return containerType.kind == ast::ContainerType::Kind::Array;
    }
    return false;
}

bool Generator::isOptionalType(const ast::Type& type) {
    // 检查是否为可选类型
    if (type.nodeType() == ast::NodeType::ContainerType) {
        const auto& containerType = static_cast<const ast::ContainerType&>(type);
        return containerType.kind == ast::ContainerType::Kind::Optional;
    }
    return false;
}

bool Generator::isMapType(const ast::Type& type) {
    // 检查是否为映射类型
    if (type.nodeType() == ast::NodeType::ContainerType) {
        const auto& containerType = static_cast<const ast::ContainerType&>(type);
        return containerType.kind == ast::ContainerType::Kind::Map;
    }
    return false;
}

std::string Generator::toPascalCase(const std::string& str) {
    if (str.empty()) return str;
    
    std::string result;
    bool capitalizeNext = true;
    
    for (char c : str) {
        if (c == '_' || c == '-' || c == ' ') {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            result += std::toupper(c);
            capitalizeNext = false;
        } else {
            result += std::tolower(c);
        }
    }
    
    return result;
}

std::string Generator::toCamelCase(const std::string& str) {
    std::string pascal = toPascalCase(str);
    if (!pascal.empty()) {
        pascal[0] = std::tolower(pascal[0]);
    }
    return pascal;
}

std::string Generator::escapeString(const std::string& str) {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += c; break;
        }
    }
    return result;
}

} // namespace generator
} // namespace mota 