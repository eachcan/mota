#include "generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <algorithm>

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
    
    std::cout << "Generator: Building template variables..." << std::endl;
    
    // 构建模板变量
    TemplateVars vars;
    try {
        vars = buildTemplateVars(document);
        std::cout << "Generator: Template variables built successfully" << std::endl;
        
        // 打印待渲染的 JSON (pretty print)
        std::cout << "\n=== Template Variables JSON (Pretty Print) ===" << std::endl;
        for (auto it = vars.begin(); it != vars.end(); ++it) {
            std::cout << "\"" << it.key() << "\": " << it.value().dump(2) << std::endl;
        }
        std::cout << "=== End Template Variables JSON ===" << std::endl << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Generator: Exception in buildTemplateVars: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Generator: Unknown exception in buildTemplateVars" << std::endl;
        return "";
    }
    
    std::cout << "Generator: Rendering template '" << templateName << "'..." << std::endl;
    
    // 使用模板引擎渲染
    try {
        std::string result = templateEngine_->renderTemplate(templateName, vars);
        std::cout << "Generator: Template rendered successfully" << std::endl;
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Generator: Exception in renderTemplate: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Generator: Unknown exception in renderTemplate" << std::endl;
        return "";
    }
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
    vars["CURRENT_TIME"] = getCurrentTime();
    vars["SOURCE_FILE"] = document->location.filename;
    
    // 构建命名空间信息
    vars["NAMESPACE"] = buildNamespaceData(document);
    
    // 构建包含文件信息
    vars["INCLUDES"] = buildIncludesData(document);
    
    // 构建声明信息
    vars["DECLARATIONS"] = buildDeclarationsData(document);
    
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

// 数据构建方法实现
nlohmann::json Generator::buildNamespaceData(const std::unique_ptr<ast::Document>& document) {
    nlohmann::json namespaceData;
    
    if (document->hasNamespace()) {
        const auto& namespaceNode = document->m_namespace;
        
        // 构建命名空间各部分
        nlohmann::json partsArray = nlohmann::json::array();
        for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
            nlohmann::json partObj = {
                {"name", namespaceNode->name[i]},
                {"index", i},
                {"is_first", i == 0},
                {"is_last", i == namespaceNode->name.size() - 1}
            };
            partsArray.push_back(partObj);
        }
        
        // 生成完整限定名
        std::string qualifiedName;
        for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
            if (i > 0) qualifiedName += ".";
            qualifiedName += namespaceNode->name[i];
        }
        
        // 生成路径
        std::string path = qualifiedName;
        std::replace(path.begin(), path.end(), '.', '/');
        
        namespaceData = {
            {"exists", true},
            {"parts", partsArray},
            {"path", path},
            {"parts_count", namespaceNode->name.size()},
            {"qualified_name", qualifiedName}
        };
    } else {
        namespaceData = {
            {"exists", false},
            {"parts", nlohmann::json::array()},
            {"path", ""},
            {"parts_count", 0},
            {"qualified_name", ""}
        };
    }
    
    return namespaceData;
}

nlohmann::json Generator::buildIncludesData(const std::unique_ptr<ast::Document>& document) {
    nlohmann::json includesData;
    nlohmann::json filesArray = nlohmann::json::array();
    
    for (const auto& include : document->includes) {
        std::string sourcePath = include->path;
        std::string translatedPath = sourcePath;
        
        // 根据配置转换文件扩展名
        if (!templateConfig_.include_directive.source_extension.empty() && 
            !templateConfig_.include_directive.target_extension.empty()) {
            std::string sourceExt = templateConfig_.include_directive.source_extension;
            std::string targetExt = templateConfig_.include_directive.target_extension;
            if (sourcePath.size() >= sourceExt.size() && 
                sourcePath.substr(sourcePath.size() - sourceExt.size()) == sourceExt) {
                translatedPath = sourcePath.substr(0, sourcePath.size() - sourceExt.size()) + targetExt;
            }
        }
        
        nlohmann::json fileObj = {
            {"source", sourcePath},
            {"translated", translatedPath}
        };
        filesArray.push_back(fileObj);
    }
    
    includesData = {
        {"files", filesArray},
        {"count", filesArray.size()}
    };
    
    return includesData;
}

nlohmann::json Generator::buildDeclarationsData(const std::unique_ptr<ast::Document>& document) {
    nlohmann::json declarationsArray = nlohmann::json::array();
    
    for (const auto& declaration : document->declarations) {
        nlohmann::json declData = buildDeclarationData(declaration);
        if (!declData.is_null()) {
            declarationsArray.push_back(declData);
        }
    }
    
    return declarationsArray;
}

nlohmann::json Generator::buildDeclarationData(const std::unique_ptr<ast::Node>& declaration) {
    switch (declaration->nodeType()) {
        case ast::NodeType::AnnotationDecl: {
            auto annotationDecl = static_cast<const ast::AnnotationDecl*>(declaration.get());
            nlohmann::json data = {
                {"type", "annotation_decl"},
                {"name", annotationDecl->name},
                {"class_name", annotationDecl->name + "Annotation"},  // 可以通过配置自定义
                {"parent", annotationDecl->baseName},
                {"parent_class_name", annotationDecl->baseName.empty() ? "" : annotationDecl->baseName + "Annotation"},
                {"annotations", nlohmann::json::array()},  // 注解声明本身不能有注解
                {"fields", nlohmann::json::array()}
            };
            
            // 构建字段数据
            for (const auto& field : annotationDecl->fields) {
                data["fields"].push_back(buildFieldData(field));
            }
            
            return data;
        }
        
        case ast::NodeType::StructDecl: {
            auto structDecl = static_cast<const ast::Struct*>(declaration.get());
            nlohmann::json data = {
                {"type", "struct"},
                {"name", structDecl->name},
                {"class_name", structDecl->name + "Model"},  // 可以通过配置自定义
                {"parent", structDecl->baseName},
                {"parent_class_name", structDecl->baseName.empty() ? "" : structDecl->baseName + "Block"},
                {"annotations", nlohmann::json::array()},
                {"fields", nlohmann::json::array()}
            };
            
            // 构建注解数据
            for (const auto& annotation : structDecl->annotations) {
                data["annotations"].push_back(buildAnnotationData(annotation));
            }
            
            // 构建字段数据
            for (const auto& field : structDecl->fields) {
                data["fields"].push_back(buildFieldData(field));
            }
            
            return data;
        }
        
        case ast::NodeType::BlockDecl: {
            auto blockDecl = static_cast<const ast::Block*>(declaration.get());
            nlohmann::json data = {
                {"type", "block"},
                {"name", blockDecl->name},
                {"class_name", blockDecl->name + "Block"},  // 可以通过配置自定义
                {"parent", blockDecl->baseName},
                {"parent_class_name", blockDecl->baseName.empty() ? "" : blockDecl->baseName + "Block"},
                {"annotations", nlohmann::json::array()},
                {"fields", nlohmann::json::array()}
            };
            
            // 构建注解数据
            for (const auto& annotation : blockDecl->annotations) {
                data["annotations"].push_back(buildAnnotationData(annotation));
            }
            
            // 构建字段数据
            for (const auto& field : blockDecl->fields) {
                data["fields"].push_back(buildFieldData(field));
            }
            
            return data;
        }
        
        case ast::NodeType::EnumDecl: {
            auto enumDecl = static_cast<const ast::Enum*>(declaration.get());
            nlohmann::json data = {
                {"type", "enum"},
                {"name", enumDecl->name},
                {"class_name", enumDecl->name},  // 枚举不需要后缀
                {"parent", ""},  // 枚举不支持继承
                {"parent_class_name", ""},
                {"annotations", nlohmann::json::array()},
                {"values", nlohmann::json::array()}
            };
            
            // 构建注解数据
            for (const auto& annotation : enumDecl->annotations) {
                data["annotations"].push_back(buildAnnotationData(annotation));
            }
            
            // 构建枚举值数据
            for (const auto& enumValue : enumDecl->values) {
                data["values"].push_back(buildEnumValueData(enumValue));
            }
            
            return data;
        }
        
        default:
            return nlohmann::json();  // 返回 null
    }
}

nlohmann::json Generator::buildAnnotationData(const std::unique_ptr<ast::Annotation>& annotation) {
    nlohmann::json data = {
        {"name", annotation->name},
        {"class_name", annotation->name + "Annotation"},  // 可以通过配置自定义
        {"arguments", nlohmann::json::array()}
    };
    
    // 构建参数数据
    for (const auto& argument : annotation->arguments) {
        nlohmann::json typeData = buildExprData(argument->value);
        
        nlohmann::json argData = {
            {"name", argument->name},
            {"field_name", argument->name},  // 可以通过配置转换
            {"container_type", "none"},  // 注解参数通常不是容器类型
            {"type_name", "string"},  // 需要根据实际表达式类型推断
            {"type_namespaces", nlohmann::json::array()},
            {"qualified_type_name", "string"},
            {"value", typeData}
        };
        
        data["arguments"].push_back(argData);
    }
    
    return data;
}

nlohmann::json Generator::buildFieldData(const std::unique_ptr<ast::Field>& field) {
    nlohmann::json typeInfo = buildTypeData(field->type);
    
    nlohmann::json data = {
        {"name", field->name},
        {"field_name", field->name},  // 可以通过配置转换
        {"container_type", typeInfo["container_type"]},
        {"type_name", typeInfo["type_name"]},
        {"type_namespaces", typeInfo["type_namespaces"]},
        {"qualified_type_name", typeInfo["qualified_type_name"]},
        {"annotations", nlohmann::json::array()}
    };
    
    // 添加默认值
    if (field->defaultValue) {
        data["default_value"] = buildExprData(field->defaultValue);
    }
    
    // 构建注解数据
    for (const auto& annotation : field->annotations) {
        data["annotations"].push_back(buildAnnotationData(annotation));
    }
    
    return data;
}

nlohmann::json Generator::buildEnumValueData(const std::unique_ptr<ast::EnumValue>& enumValue) {
    nlohmann::json data = {
        {"name", enumValue->name},
        {"field_name", enumValue->name},  // 可以通过配置转换
        {"annotations", nlohmann::json::array()}
    };
    
    // 添加值
    if (enumValue->value) {
        data["value"] = buildExprData(enumValue->value);
    }
    
    // 构建注解数据
    for (const auto& annotation : enumValue->annotations) {
        data["annotations"].push_back(buildAnnotationData(annotation));
    }
    
    return data;
}

nlohmann::json Generator::buildExprData(const std::unique_ptr<ast::Expr>& expr) {
    if (!expr) {
        return nlohmann::json();
    }
    
    switch (expr->nodeType()) {
        case ast::NodeType::Literal: {
            auto literal = static_cast<const ast::Literal*>(expr.get());
            
            if (std::holds_alternative<std::string>(literal->value)) {
                std::string str = std::get<std::string>(literal->value);
                return "\"" + escapeString(str) + "\"";
            } else if (std::holds_alternative<int64_t>(literal->value)) {
                return std::to_string(std::get<int64_t>(literal->value));
            } else if (std::holds_alternative<double>(literal->value)) {
                return std::to_string(std::get<double>(literal->value));
            } else if (std::holds_alternative<bool>(literal->value)) {
                return std::get<bool>(literal->value) ? "true" : "false";
            }
            break;
        }
        
        case ast::NodeType::ArrayLiteral: {
            auto arrayLiteral = static_cast<const ast::ArrayLiteral*>(expr.get());
            nlohmann::json arrayData = nlohmann::json::array();
            for (const auto& element : arrayLiteral->elements) {
                arrayData.push_back(buildExprData(element));
            }
            return arrayData;
        }
        
        case ast::NodeType::Annotation: {
            auto annotation = static_cast<const ast::Annotation*>(expr.get());
            // 直接构建注解数据，不使用 unique_ptr
            nlohmann::json data = {
                {"name", annotation->name},
                {"class_name", annotation->name + "Annotation"},
                {"arguments", nlohmann::json::array()}
            };
            
            // 构建参数数据
            for (const auto& argument : annotation->arguments) {
                nlohmann::json typeData = buildExprData(argument->value);
                
                nlohmann::json argData = {
                    {"name", argument->name},
                    {"field_name", argument->name},
                    {"container_type", "none"},
                    {"type_name", "string"},
                    {"type_namespaces", nlohmann::json::array()},
                    {"qualified_type_name", "string"},
                    {"value", typeData}
                };
                
                data["arguments"].push_back(argData);
            }
            
            return data;
        }
        
        default:
            // 对于其他类型的表达式，返回字符串表示
            return "/* complex expression */";
    }
    
    return nlohmann::json();
}

nlohmann::json Generator::buildTypeData(const std::unique_ptr<ast::Type>& type) {
    nlohmann::json data;
    
    switch (type->nodeType()) {
        case ast::NodeType::NamedType: {
            auto namedType = static_cast<const ast::NamedType*>(type.get());
            std::string typeName = namedType->name;
            
            // 解析类型命名空间
            std::vector<std::string> namespaces;
            size_t lastDot = typeName.find_last_of('.');
            if (lastDot != std::string::npos) {
                std::string namespacePart = typeName.substr(0, lastDot);
                typeName = typeName.substr(lastDot + 1);
                
                std::stringstream ss(namespacePart);
                std::string part;
                while (std::getline(ss, part, '.')) {
                    namespaces.push_back(part);
                }
            }
            
            data = {
                {"container_type", "none"},
                {"type_name", typeName},
                {"type_namespaces", namespaces},
                {"qualified_type_name", namedType->name}
            };
            break;
        }
        
        case ast::NodeType::ContainerType: {
            auto containerType = static_cast<const ast::ContainerType*>(type.get());
            nlohmann::json elementTypeData = buildTypeData(containerType->elementType);
            
            std::string containerTypeStr;
            switch (containerType->kind) {
                case ast::ContainerType::Kind::Array:
                    containerTypeStr = "array";
                    break;
                case ast::ContainerType::Kind::Map:
                    containerTypeStr = "map";
                    break;
                case ast::ContainerType::Kind::Optional:
                    containerTypeStr = "optional";
                    break;
            }
            
            data = {
                {"container_type", containerTypeStr},
                {"type_name", elementTypeData["type_name"]},
                {"type_namespaces", elementTypeData["type_namespaces"]},
                {"qualified_type_name", elementTypeData["qualified_type_name"]}
            };
            break;
        }
        
        default:
            data = {
                {"container_type", "none"},
                {"type_name", "unknown"},
                {"type_namespaces", nlohmann::json::array()},
                {"qualified_type_name", "unknown"}
            };
            break;
    }
    
    return data;
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