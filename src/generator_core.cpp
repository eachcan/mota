#include "generator.h"
#include "file_processor.h"
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
    if (initialized_) {
        return true;
    }
    
    templateDir_ = templateDir;
    
    // 加载配置
    std::string configFile = configPath.empty() ? templateDir + "/config.json5" : configPath;
    if (!templateConfig_.loadFromFile(configFile)) {
        std::cerr << "Failed to load template config from: " << configFile << std::endl;
        return false;
    }
    
    // 创建模板引擎
    templateEngine_ = std::make_shared<template_engine::TemplateEngine>(templateConfig_, templateDir);
    
    // 设置模板引擎的Generator引用
    templateEngine_->setGenerator(this);
    
    initialized_ = true;
    return true;
}

std::string Generator::generateCode(const std::shared_ptr<ast::Document>& document, const std::string& templateName) {
    if (!initialized_) {
        std::cerr << "Generator not initialized" << std::endl;
        return "";
    }
    
    std::cout << "[DEBUG] 开始构建模板变量..." << std::endl;
        
    // 构建模板变量
    TemplateVars vars;
    try {
        vars = buildTemplateVars(document);
        std::cout << "[DEBUG] 模板变量构建完成" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Generator: Exception in buildTemplateVars: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Generator: Unknown exception in buildTemplateVars" << std::endl;
        return "";
    }
    
    std::cout << "[DEBUG] 开始渲染模板: " << templateName << std::endl;
    
    // 使用模板引擎渲染
    try {
        std::string result = templateEngine_->renderTemplate(templateName, vars);
        std::cout << "[DEBUG] 模板渲染完成，结果长度: " << result.length() << std::endl;
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Generator: Exception in renderTemplate: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Generator: Unknown exception in renderTemplate" << std::endl;
        return "";
    }
}



TemplateVars Generator::buildTemplateVars(const std::shared_ptr<ast::Document>& document) {
    TemplateVars vars;
    
    // 设置当前命名空间
    currentNamespace_ = extractNamespace(document);
    
    // 基本信息
    vars["CURRENT_TIME"] = getCurrentTime();
    vars["SOURCE_FILE"] = document->location.filename;
    
    // 构建命名空间信息
    vars["NAMESPACE"] = buildNamespaceData(document);
    
    // 构建包含文件信息
    vars["INCLUDES"] = buildIncludesData(document);
    
    // 构建声明信息
    vars["DECLARATIONS"] = buildDeclarationsData(document);
    
    // 构建声明注册表信息
    vars["DECLARATIONS_REGISTRY"] = buildDeclarationRegistryData();
    
    return vars;
}

std::string Generator::extractNamespace(const std::shared_ptr<ast::Document>& document) {
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
nlohmann::json Generator::buildNamespaceData(const std::shared_ptr<ast::Document>& document) {
    nlohmann::json namespaceData;
    
    if (document->hasNamespace()) {
        const auto& namespaceNode = document->m_namespace;
        
        // 构建命名空间各部分
        std::string classPrefix;
        nlohmann::json partsArray = nlohmann::json::array();
        for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
            nlohmann::json partObj = {
                {"name", namespaceNode->name[i]},
                {"index", i},
                {"is_first", i == 0},
                {"is_last", i == namespaceNode->name.size() - 1}
            };
            partsArray.push_back(partObj);
            classPrefix += namespaceNode->name[i] + templateConfig_.namespace_config.separator.code;
        }
        
        // 生成完整限定名
        std::string qualifiedName;
        for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
            if (i > 0) qualifiedName += ".";
            qualifiedName += namespaceNode->name[i];
        }
        
        // 生成路径，使用配置中的目录分隔符
        std::string dirPath = qualifiedName;
        if (!templateConfig_.namespace_config.separator.dir.empty()) {
            std::string from = ".";
            std::string to = templateConfig_.namespace_config.separator.dir;
            size_t pos = 0;
            while ((pos = dirPath.find(from, pos)) != std::string::npos) {
                dirPath.replace(pos, from.length(), to);
                pos += to.length();
            }
        }
        
        namespaceData = {
            {"exists", true},
            {"parts", partsArray},
            {"path", dirPath},
            {"parts_count", namespaceNode->name.size()},
            {"qualified_name", qualifiedName},
            {"as_class_prefix", classPrefix}
        };
    } else {
        namespaceData = {
            {"exists", false},
            {"parts", nlohmann::json::array()},
            {"path", ""},
            {"parts_count", 0},
            {"qualified_name", ""},
            {"as_class_prefix", ""}
        };
    }
    
    return namespaceData;
}

nlohmann::json Generator::buildIncludesData(const std::shared_ptr<ast::Document>& document) {
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

nlohmann::json Generator::buildDeclarationsData(const std::shared_ptr<ast::Document>& document) {
    nlohmann::json declarationsArray = nlohmann::json::array();
    
    for (const auto& declaration : document->declarations) {
        nlohmann::json declData = buildDeclarationData(declaration);
        if (!declData.is_null()) {
            declarationsArray.push_back(declData);
        }
    }
    
    return declarationsArray;
}

nlohmann::json Generator::buildDeclarationData(const std::shared_ptr<ast::Node>& declaration) {
    switch (declaration->nodeType()) {
        case ast::NodeType::AnnotationDecl: {
            auto annotationDecl = static_cast<const ast::AnnotationDecl*>(declaration.get());
            
            // 获取当前命名空间信息
            std::string currentNamespace = currentNamespace_;
            std::string namespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
            std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
            if (!namespaceClassPrefix.empty() && namespaceClassPrefix.back() != ':') {
                namespaceClassPrefix += "::";
            }
            
            // 获取类名后缀配置
            std::string classPrefix = templateConfig_.declaration_types.annotation_decl.prefix;
            std::string classSuffix = templateConfig_.declaration_types.annotation_decl.suffix;
            
            // 解析父类型的完整信息
            std::string parentName = annotationDecl->baseName;
            std::string parentClassName = parentName.empty() ? "" : classPrefix + parentName + classSuffix;
            std::string parentFullName = parentName;
            std::string parentFullClassName = parentClassName;
            
            if (!parentName.empty()) {
                // 如果父类型包含命名空间，直接使用
                if (parentName.find('.') != std::string::npos) {
                    parentFullName = parentName;
                    std::string simpleParentName = parentName.substr(parentName.find_last_of('.') + 1);
                    parentClassName = classPrefix + simpleParentName + classSuffix;
                    parentFullClassName = parentName;
                    std::replace(parentFullClassName.begin(), parentFullClassName.end(), '.', ':');
                    parentFullClassName = classPrefix + parentFullClassName + classSuffix;
                } else {
                    // 如果父类型不包含命名空间，假设在当前命名空间中
                    parentFullName = currentNamespace.empty() ? parentName : currentNamespace + "." + parentName;
                    parentFullClassName = namespaceClassPrefix + parentClassName;
                }
            }
            
            nlohmann::json data = {
                {"type", "annotation_decl"},
                {"name", annotationDecl->name},
                {"class_name", classPrefix + annotationDecl->name + classSuffix},
                {"full_name", currentNamespace.empty() ? annotationDecl->name : currentNamespace + "." + annotationDecl->name},
                {"full_class_name", namespaceClassPrefix + classPrefix + annotationDecl->name + classSuffix},
                {"parent_name", parentName},
                {"parent_class_name", parentClassName},
                {"parent_full_name", parentFullName},
                {"parent_full_class_name", parentFullClassName},
                {"namespace", currentNamespace},
                {"namespace_class_prefix", namespaceClassPrefix},
                {"parent", annotationDecl->baseName},  // 保持向后兼容
                {"annotations", nlohmann::json::array()},
                {"fields", nlohmann::json::array()},
                {"relative_name", (currentNamespace == currentNamespace ? annotationDecl->name : (currentNamespace.empty() ? annotationDecl->name : currentNamespace + "." + annotationDecl->name))},
                {"relative_class_name", (currentNamespace == currentNamespace ? classPrefix + annotationDecl->name + classSuffix : namespaceClassPrefix + classPrefix + annotationDecl->name + classSuffix)},
                {"parent_relative_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentName : parentFullName))},
                {"parent_relative_class_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentClassName : parentFullClassName))}
            };
            
            // 构建字段数据
            for (const auto& field : annotationDecl->fields) {
                data["fields"].push_back(buildFieldData(field));
            }
            
            return data;
        }
        
        case ast::NodeType::StructDecl: {
            auto structDecl = static_cast<const ast::Struct*>(declaration.get());
            
            // 获取当前命名空间信息
            std::string currentNamespace = currentNamespace_;
            std::string namespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
            std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
            if (!namespaceClassPrefix.empty() && namespaceClassPrefix.back() != ':') {
                namespaceClassPrefix += "::";
            }
            
            // 获取类名后缀配置
            std::string classPrefix = templateConfig_.declaration_types.struct_decl.prefix;
            std::string classSuffix = templateConfig_.declaration_types.struct_decl.suffix;
            
            // 解析父类型的完整信息
            std::string parentName = structDecl->baseName;
            std::string parentClassName = parentName.empty() ? "" : classPrefix + parentName + classSuffix;
            std::string parentFullName = parentName;
            std::string parentFullClassName = parentClassName;
            
            if (!parentName.empty()) {
                // 如果父类型包含命名空间，直接使用
                if (parentName.find('.') != std::string::npos) {
                    parentFullName = parentName;
                    std::string simpleParentName = parentName.substr(parentName.find_last_of('.') + 1);
                    parentClassName = classPrefix + simpleParentName + classSuffix;
                    parentFullClassName = parentName;
                    std::replace(parentFullClassName.begin(), parentFullClassName.end(), '.', ':');
                    parentFullClassName = classPrefix + parentFullClassName + classSuffix;
                } else {
                    // 如果父类型不包含命名空间，假设在当前命名空间中
                    parentFullName = currentNamespace.empty() ? parentName : currentNamespace + "." + parentName;
                    parentFullClassName = namespaceClassPrefix + parentClassName;
                }
            }
            
            nlohmann::json data = {
                {"type", "struct"},
                {"name", structDecl->name},
                {"class_name", classPrefix + structDecl->name + classSuffix},
                {"full_name", currentNamespace.empty() ? structDecl->name : currentNamespace + "." + structDecl->name},
                {"full_class_name", namespaceClassPrefix + classPrefix + structDecl->name + classSuffix},
                {"parent_name", parentName},
                {"parent_class_name", parentClassName},
                {"parent_full_name", parentFullName},
                {"parent_full_class_name", parentFullClassName},
                {"namespace", currentNamespace},
                {"namespace_class_prefix", namespaceClassPrefix},
                {"parent", structDecl->baseName},  // 保持向后兼容
                {"annotations", nlohmann::json::array()},
                {"fields", nlohmann::json::array()},
                {"relative_name", (currentNamespace == currentNamespace ? structDecl->name : (currentNamespace.empty() ? structDecl->name : currentNamespace + "." + structDecl->name))},
                {"relative_class_name", (currentNamespace == currentNamespace ? classPrefix + structDecl->name + classSuffix : namespaceClassPrefix + classPrefix + structDecl->name + classSuffix)},
                {"parent_relative_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentName : parentFullName))},
                {"parent_relative_class_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentClassName : parentFullClassName))}
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
            
            // 获取当前命名空间信息
            std::string currentNamespace = currentNamespace_;
            std::string namespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
            std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
            if (!namespaceClassPrefix.empty() && namespaceClassPrefix.back() != ':') {
                namespaceClassPrefix += "::";
            }
            
            // 获取类名后缀配置
            std::string classPrefix = templateConfig_.declaration_types.block_decl.prefix;
            std::string classSuffix = templateConfig_.declaration_types.block_decl.suffix;
            
            // 解析父类型的完整信息
            std::string parentName = blockDecl->baseName;
            std::string parentClassName = parentName.empty() ? "" : classPrefix + parentName + classSuffix;
            std::string parentFullName = parentName;
            std::string parentFullClassName = parentClassName;
            
            if (!parentName.empty()) {
                // 如果父类型包含命名空间，直接使用
                if (parentName.find('.') != std::string::npos) {
                    parentFullName = parentName;
                    std::string simpleParentName = parentName.substr(parentName.find_last_of('.') + 1);
                    parentClassName = classPrefix + simpleParentName + classSuffix;
                    parentFullClassName = parentName;
                    std::replace(parentFullClassName.begin(), parentFullClassName.end(), '.', ':');
                    parentFullClassName = classPrefix + parentFullClassName + classSuffix;
                } else {
                    // 如果父类型不包含命名空间，假设在当前命名空间中
                    parentFullName = currentNamespace.empty() ? parentName : currentNamespace + "." + parentName;
                    parentFullClassName = namespaceClassPrefix + parentClassName;
                }
            }
            
            nlohmann::json data = {
                {"type", "block"},
                {"name", blockDecl->name},
                {"class_name", classPrefix + blockDecl->name + classSuffix},
                {"full_name", currentNamespace.empty() ? blockDecl->name : currentNamespace + "." + blockDecl->name},
                {"full_class_name", namespaceClassPrefix + classPrefix + blockDecl->name + classSuffix},
                {"parent_name", parentName},
                {"parent_class_name", parentClassName},
                {"parent_full_name", parentFullName},
                {"parent_full_class_name", parentFullClassName},
                {"namespace", currentNamespace},
                {"namespace_class_prefix", namespaceClassPrefix},
                {"parent", blockDecl->baseName},  // 保持向后兼容
                {"annotations", nlohmann::json::array()},
                {"fields", nlohmann::json::array()},
                {"relative_name", (currentNamespace == currentNamespace ? blockDecl->name : (currentNamespace.empty() ? blockDecl->name : currentNamespace + "." + blockDecl->name))},
                {"relative_class_name", (currentNamespace == currentNamespace ? classPrefix + blockDecl->name + classSuffix : namespaceClassPrefix + classPrefix + blockDecl->name + classSuffix)},
                {"parent_relative_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentName : parentFullName))},
                {"parent_relative_class_name", (parentName.empty() ? "" : (currentNamespace == currentNamespace ? parentClassName : parentFullClassName))}
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
            
            // 获取当前命名空间信息
            std::string currentNamespace = currentNamespace_;
            std::string namespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
            std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
            if (!namespaceClassPrefix.empty() && namespaceClassPrefix.back() != ':') {
                namespaceClassPrefix += "::";
            }
            
            // 获取类名后缀配置
            std::string classPrefix = templateConfig_.declaration_types.enum_decl.prefix;
            std::string classSuffix = templateConfig_.declaration_types.enum_decl.suffix;
            
            nlohmann::json data = {
                {"type", "enum"},
                {"name", enumDecl->name},
                {"class_name", classPrefix + enumDecl->name + classSuffix},
                {"full_name", currentNamespace.empty() ? enumDecl->name : currentNamespace + "." + enumDecl->name},
                {"full_class_name", namespaceClassPrefix + classPrefix + enumDecl->name + classSuffix},
                {"parent_name", ""},
                {"parent_class_name", ""},
                {"parent_full_name", ""},
                {"parent_full_class_name", ""},
                {"namespace", currentNamespace},
                {"namespace_class_prefix", namespaceClassPrefix},
                {"parent", ""},  // 保持向后兼容
                {"annotations", nlohmann::json::array()},
                {"values", nlohmann::json::array()},
                {"relative_name", (currentNamespace == currentNamespace ? enumDecl->name : (currentNamespace.empty() ? enumDecl->name : currentNamespace + "." + enumDecl->name))},
                {"relative_class_name", (currentNamespace == currentNamespace ? classPrefix + enumDecl->name + classSuffix : namespaceClassPrefix + classPrefix + enumDecl->name + classSuffix)},
                {"parent_relative_name", ""},
                {"parent_relative_class_name", ""}
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

nlohmann::json Generator::buildAnnotationData(const std::shared_ptr<ast::Annotation>& annotation) {
    // 获取当前命名空间信息
    std::string currentNamespace = currentNamespace_;
    std::string namespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
    std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
    if (!namespaceClassPrefix.empty() && namespaceClassPrefix.back() != ':') {
        namespaceClassPrefix += "::";
    }
    
    // 获取类名后缀配置
    std::string classPrefix = templateConfig_.declaration_types.annotation_decl.prefix;
    std::string classSuffix = templateConfig_.declaration_types.annotation_decl.suffix;
    
    // 解析注解类型的完整信息
    std::string annotationName = annotation->name;
    std::string fullName = annotationName;
    std::string fullClassName = classPrefix + annotationName + classSuffix;
    
    std::string annotationNamespaceClassPrefix;
    if (annotationName.find('.') != std::string::npos) {
        std::string ns = annotationName.substr(0, annotationName.find_last_of('.'));
        annotationNamespaceClassPrefix = ns.empty() ? "" : ns + "::";
        std::replace(annotationNamespaceClassPrefix.begin(), annotationNamespaceClassPrefix.end(), '.', ':');
        if (!annotationNamespaceClassPrefix.empty() && annotationNamespaceClassPrefix.back() != ':') {
            annotationNamespaceClassPrefix += "::";
        }
    } else {
        annotationNamespaceClassPrefix = currentNamespace.empty() ? "" : currentNamespace + "::";
        std::replace(annotationNamespaceClassPrefix.begin(), annotationNamespaceClassPrefix.end(), '.', ':');
        if (!annotationNamespaceClassPrefix.empty() && annotationNamespaceClassPrefix.back() != ':') {
            annotationNamespaceClassPrefix += "::";
        }
    }
    
    nlohmann::json data = {
        {"name", annotationName},
        {"class_name", classPrefix + annotationName + classSuffix},
        {"full_name", fullName},
        {"full_class_name", fullClassName},
        {"type", "annotation"},
        {"namespace", currentNamespace},
        {"arguments", nlohmann::json::array()},
        {"relative_name", (currentNamespace == currentNamespace ? annotationName : (currentNamespace.empty() ? annotationName : currentNamespace + "." + annotationName))},
        {"relative_class_name", (currentNamespace == currentNamespace ? classPrefix + annotationName + classSuffix : annotationNamespaceClassPrefix + classPrefix + annotationName + classSuffix)}
    };
    
    // 构建参数数据 - 使用字段信息
    if (declarationRegistry_) {
        auto it = declarationRegistry_->find(fullName);
        if (it != declarationRegistry_->end()) {
            const auto& declInfo = it->second;
            if (declInfo.type == "annotation_decl") {
                // 为每个参数构建类型化的数据
                for (const auto& argument : annotation->arguments) {
                    // 查找对应的字段定义
                    const processor::DeclarationInfo::FieldInfo* fieldDef = nullptr;
                    for (const auto& field : declInfo.fields) {
                        if (field.name == argument->name) {
                            fieldDef = &field;
                            break;
                        }
                    }
                    
                    if (fieldDef) {
                        nlohmann::json valueData = buildExprData(argument->value);
                        std::string argTypeName = fieldDef->type_name;
                        std::string argFullTypeName = argTypeName;
                        if (!isBuiltinType(argTypeName) && argFullTypeName.find('.') == std::string::npos && !currentNamespace_.empty()) {
                            argFullTypeName = currentNamespace_ + "." + argFullTypeName;
                        }
                        std::string argContainerType = fieldDef->container_type;
                        std::string argMappedTypeName = mapType(argTypeName);
                        std::string argFullMappedTypeName = argMappedTypeName;
                        std::string argNamespaceName;
                        if (!isBuiltinType(argTypeName) && declarationRegistry_) {
                            auto typeIt = declarationRegistry_->find(argFullTypeName);
                            if (typeIt != declarationRegistry_->end()) {
                                argMappedTypeName = typeIt->second.class_name;
                                if (!typeIt->second.namespace_name.empty()) {
                                    std::string namespaceClassPrefix = typeIt->second.namespace_name;
                                    std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
                                    namespaceClassPrefix += "::";
                                    argFullMappedTypeName = namespaceClassPrefix + typeIt->second.class_name;
                                } else {
                                    argFullMappedTypeName = typeIt->second.class_name;
                                }
                                argNamespaceName = typeIt->second.namespace_name;
                            }
                        }
                        nlohmann::json argData = {
                            {"name", argument->name},
                            {"field_name", argument->name},
                            {"container_type", argContainerType},
                            {"type_name", argTypeName},
                            {"mapped_type_name", argMappedTypeName},
                            {"full_type_name", argFullTypeName},
                            {"full_mapped_type_name", argFullMappedTypeName},
                            {"value", valueData},
                            {"relative_type_name", (currentNamespace_ == argNamespaceName ? argTypeName : argFullTypeName)},
                            {"relative_mapped_type_name", (currentNamespace_ == argNamespaceName ? argMappedTypeName : argFullMappedTypeName)}
                        };
                        data["arguments"].push_back(argData);
                    }
                }
            }
        }
    }
    
    return data;
}

nlohmann::json Generator::buildFieldData(const std::shared_ptr<ast::Field>& field) {
    nlohmann::json typeInfo = buildTypeData(field->type);
    std::string typeName = typeInfo["type_name"];
    std::string mappedTypeName = mapType(typeName);
    std::string fullTypeName = typeInfo["qualified_type_name"];
    if (!isBuiltinType(typeName) && fullTypeName.find('.') == std::string::npos && !currentNamespace_.empty()) {
        fullTypeName = currentNamespace_ + "." + fullTypeName;
    }
    std::string fullMappedTypeName = mappedTypeName;
    std::string fieldNamespaceName;
    if (!isBuiltinType(typeName) && declarationRegistry_) {
        auto it = declarationRegistry_->find(fullTypeName);
        if (it != declarationRegistry_->end()) {
            mappedTypeName = it->second.class_name;
            if (!it->second.namespace_name.empty()) {
                std::string namespaceClassPrefix = it->second.namespace_name;
                std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
                namespaceClassPrefix += "::";
                fullMappedTypeName = namespaceClassPrefix + it->second.class_name;
            } else {
                fullMappedTypeName = it->second.class_name;
            }
            fieldNamespaceName = it->second.namespace_name;
        }
    }
    nlohmann::json data = {
        {"name", field->name},
        {"field_name", field->name},
        {"container_type", typeInfo["container_type"]},
        {"type_name", typeName},
        {"mapped_type_name", mappedTypeName},
        {"full_type_name", fullTypeName},
        {"full_mapped_type_name", fullMappedTypeName},
        {"annotations", nlohmann::json::array()},
        {"relative_type_name", (currentNamespace_ == fieldNamespaceName ? typeName : fullTypeName)},
        {"relative_mapped_type_name", (currentNamespace_ == fieldNamespaceName ? mappedTypeName : fullMappedTypeName)}
    };
    if (field->defaultValue) {
        data["default_value"] = buildExprData(field->defaultValue);
    }
    for (const auto& annotation : field->annotations) {
        data["annotations"].push_back(buildAnnotationData(annotation));
    }
    return data;
}

nlohmann::json Generator::buildEnumValueData(const std::shared_ptr<ast::EnumValue>& enumValue) {
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

nlohmann::json Generator::buildExprData(const std::shared_ptr<ast::Expr>& expr) {
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
            return buildAnnotationValueData(annotation);
        }
        
        default:
            // 对于其他类型的表达式，返回字符串表示
            return "/* complex expression */";
    }
    
    return nlohmann::json();
}

nlohmann::json Generator::buildAnnotationValueData(const ast::Annotation* annotation) {
    // 获取注解类名后缀配置
    std::string classPrefix = templateConfig_.declaration_types.annotation_decl.prefix;
    std::string classSuffix = templateConfig_.declaration_types.annotation_decl.suffix;
    
    // 获取完整的注解信息
    std::string annotationName = annotation->name;
    std::string fullName = annotationName;
    std::string className = classPrefix + annotationName + classSuffix;
    std::string fullClassName = className;
    
    // 处理命名空间
    std::string annotationNamespaceClassPrefix;
    if (annotationName.find('.') != std::string::npos) {
        fullName = annotationName;
        std::string simpleAnnotationName = annotationName.substr(annotationName.find_last_of('.') + 1);
        className = classPrefix + simpleAnnotationName + classSuffix;
        fullClassName = annotationName;
        std::replace(fullClassName.begin(), fullClassName.end(), '.', ':');
        fullClassName = classPrefix + fullClassName + classSuffix;
        annotationName = simpleAnnotationName;
        std::string ns = annotation->name.substr(0, annotation->name.find_last_of('.'));
        annotationNamespaceClassPrefix = ns.empty() ? "" : ns + "::";
        std::replace(annotationNamespaceClassPrefix.begin(), annotationNamespaceClassPrefix.end(), '.', ':');
        if (!annotationNamespaceClassPrefix.empty() && annotationNamespaceClassPrefix.back() != ':') {
            annotationNamespaceClassPrefix += "::";
        }
    } else {
        // 如果注解名不包含命名空间，假设在当前命名空间中
        fullName = currentNamespace_.empty() ? annotationName : currentNamespace_ + "." + annotationName;
        annotationNamespaceClassPrefix = currentNamespace_.empty() ? "" : currentNamespace_ + "::";
        std::replace(annotationNamespaceClassPrefix.begin(), annotationNamespaceClassPrefix.end(), '.', ':');
        if (!annotationNamespaceClassPrefix.empty() && annotationNamespaceClassPrefix.back() != ':') {
            annotationNamespaceClassPrefix += "::";
        }
        fullClassName = annotationNamespaceClassPrefix + className;
    }
    
    nlohmann::json data = {
        {"name", annotationName},
        {"class_name", className},
        {"full_name", fullName},
        {"full_class_name", fullClassName},
        {"type", "annotation"},
        {"namespace", currentNamespace_},
        {"arguments", nlohmann::json::array()},
        {"relative_name", (currentNamespace_ == currentNamespace_ ? annotationName : (currentNamespace_.empty() ? annotationName : currentNamespace_ + "." + annotationName))},
        {"relative_class_name", (currentNamespace_ == currentNamespace_ ? classPrefix + annotationName + classSuffix : annotationNamespaceClassPrefix + classPrefix + annotationName + classSuffix)}
    };
    
    // 构建参数数据 - 使用字段信息
    if (declarationRegistry_) {
        auto it = declarationRegistry_->find(fullName);
        if (it != declarationRegistry_->end()) {
            const auto& declInfo = it->second;
            if (declInfo.type == "annotation_decl") {
                // 为每个参数构建类型化的数据
                for (const auto& argument : annotation->arguments) {
                    // 查找对应的字段定义
                    const processor::DeclarationInfo::FieldInfo* fieldDef = nullptr;
                    for (const auto& field : declInfo.fields) {
                        if (field.name == argument->name) {
                            fieldDef = &field;
                            break;
                        }
                    }
                    
                    if (fieldDef) {
                        nlohmann::json valueData = buildExprData(argument->value);
                        std::string argTypeName = fieldDef->type_name;
                        std::string argFullTypeName = argTypeName;
                        if (!isBuiltinType(argTypeName) && argFullTypeName.find('.') == std::string::npos && !currentNamespace_.empty()) {
                            argFullTypeName = currentNamespace_ + "." + argFullTypeName;
                        }
                        std::string argContainerType = fieldDef->container_type;
                        std::string argMappedTypeName = mapType(argTypeName);
                        std::string argFullMappedTypeName = argMappedTypeName;
                        std::string argNamespaceName;
                        if (!isBuiltinType(argTypeName) && declarationRegistry_) {
                            auto typeIt = declarationRegistry_->find(argFullTypeName);
                            if (typeIt != declarationRegistry_->end()) {
                                argMappedTypeName = typeIt->second.class_name;
                                if (!typeIt->second.namespace_name.empty()) {
                                    std::string namespaceClassPrefix = typeIt->second.namespace_name;
                                    std::replace(namespaceClassPrefix.begin(), namespaceClassPrefix.end(), '.', ':');
                                    namespaceClassPrefix += "::";
                                    argFullMappedTypeName = namespaceClassPrefix + typeIt->second.class_name;
                                } else {
                                    argFullMappedTypeName = typeIt->second.class_name;
                                }
                                argNamespaceName = typeIt->second.namespace_name;
                            }
                        }
                        nlohmann::json argData = {
                            {"name", argument->name},
                            {"field_name", argument->name},
                            {"container_type", argContainerType},
                            {"type_name", argTypeName},
                            {"mapped_type_name", argMappedTypeName},
                            {"full_type_name", argFullTypeName},
                            {"full_mapped_type_name", argFullMappedTypeName},
                            {"value", valueData},
                            {"relative_type_name", (currentNamespace_ == argNamespaceName ? argTypeName : argFullTypeName)},
                            {"relative_mapped_type_name", (currentNamespace_ == argNamespaceName ? argMappedTypeName : argFullMappedTypeName)}
                        };
                        data["arguments"].push_back(argData);
                    }
                }
            }
        }
    }
    
    return data;
}

nlohmann::json Generator::buildTypedExprData(const std::shared_ptr<ast::Expr>& expr, const std::shared_ptr<ast::Type>& expectedType) {
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
            
            // 如果期望类型是数组，获取元素类型
            std::shared_ptr<ast::Type> elementType = nullptr;
            if (expectedType && expectedType->nodeType() == ast::NodeType::ContainerType) {
                const auto* containerType = static_cast<const ast::ContainerType*>(expectedType.get());
                if (containerType->kind == ast::ContainerType::Kind::Array) {
                    // 这里需要克隆元素类型，但为了简化，我们使用递归调用
                    for (const auto& element : arrayLiteral->elements) {
                        arrayData.push_back(buildTypedExprData(element, containerType->elementType));
                    }
                    return arrayData;
                }
            }
            
            // 默认处理
            for (const auto& element : arrayLiteral->elements) {
                arrayData.push_back(buildExprData(element));
            }
            return arrayData;
        }
        
        case ast::NodeType::Annotation: {
            auto annotation = static_cast<const ast::Annotation*>(expr.get());
            return buildAnnotationValueData(annotation);
        }
        
        default:
            // 对于其他类型的表达式，回退到普通处理
            return buildExprData(expr);
    }
    
    return nlohmann::json();
}

nlohmann::json Generator::buildTypeData(const std::shared_ptr<ast::Type>& type) {
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
    // 1. 首先检查是否为基础类型
    if (isBuiltinType(motaType)) {
        auto it = templateConfig_.type_mapping.find(motaType);
        if (it != templateConfig_.type_mapping.end()) {
            return it->second;
        }
        return motaType; // 如果基础类型没有映射，返回原始类型
    }
    
    // 2. 查询声明注册表
    if (declarationRegistry_) {
        // 首先尝试完全限定名查找
        auto it = declarationRegistry_->find(motaType);
        if (it != declarationRegistry_->end()) {
            return it->second.getRelativeTypeName(currentNamespace_);
        }
        
        // 如果没找到，尝试在当前命名空间中查找简单名称
        std::string qualifiedName = currentNamespace_.empty() ? motaType : currentNamespace_ + "." + motaType;
        it = declarationRegistry_->find(qualifiedName);
        if (it != declarationRegistry_->end()) {
            return it->second.getRelativeTypeName(currentNamespace_);
        }
        
        // 遍历注册表查找匹配的简单名称
        for (const auto& [regQualifiedName, info] : *declarationRegistry_) {
            if (info.name == motaType) {
                return info.getRelativeTypeName(currentNamespace_);
            }
        }
    }
    
    // 3. 如果都没找到，检查传统类型映射
    auto it = templateConfig_.type_mapping.find(motaType);
    if (it != templateConfig_.type_mapping.end()) {
        return it->second;
    }
    
    // 4. 最后返回原始类型
    return motaType;
}

bool Generator::isBuiltinType(const std::string& type) {
    static const std::vector<std::string> builtinTypes = {
        "int8", "int16", "int32", "int64", "uint8", "uint16", "uint32", "uint64", "float32", "float64", "string", "bool", "bytes"
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

void Generator::setDeclarationRegistry(const processor::DeclarationRegistry& registry) {
    // 复制声明注册表以确保数据有效性
    declarationRegistryStorage_ = registry;
    declarationRegistry_ = &declarationRegistryStorage_;
}

void Generator::setCurrentNamespace(const std::string& currentNamespace) {
    currentNamespace_ = currentNamespace;
}

nlohmann::json Generator::buildDeclarationRegistryData() {
    nlohmann::json registryData = nlohmann::json::object();
    
    if (!declarationRegistry_) {
        return registryData;
    }
    
    // 构建按类型分组的注册表
    nlohmann::json allDeclarations = nlohmann::json::array();
    nlohmann::json byType = nlohmann::json::object();
    byType["struct"] = nlohmann::json::array();
    byType["block"] = nlohmann::json::array();
    byType["enum"] = nlohmann::json::array();
    byType["annotation_decl"] = nlohmann::json::array();
    
    for (const auto& [qualifiedName, info] : *declarationRegistry_) {
        nlohmann::json declInfo = {
            {"name", info.name},
            {"qualified_name", info.qualified_name},
            {"class_name", info.class_name},
            {"type", info.type},
            {"namespace_name", info.namespace_name},
            {"file_path", info.file_path},
            {"relative_type_name", info.getRelativeTypeName(currentNamespace_)}
        };
        
        allDeclarations.push_back(declInfo);
        byType[info.type].push_back(declInfo);
    }
    
    registryData["all"] = allDeclarations;
    registryData["by_type"] = byType;
    registryData["count"] = allDeclarations.size();
    
    return registryData;
}

} // namespace generator
} // namespace mota 