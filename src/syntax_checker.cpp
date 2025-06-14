﻿#include "syntax_checker.h"
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <iostream>
#include <algorithm>

namespace mota {
namespace checker {



namespace {
// 内置基础类型
const std::set<std::string> kBuiltinTypes = {
    "int8", "int16", "int32", "int64",
    "uint8", "uint16", "uint32", "uint64",
    "float32", "float64", "string", "bool", "bytes"
};

// 检测循环继承
bool hasCircularInheritance(const std::string& type, 
                           const std::unordered_map<std::string, std::string>& inheritanceMap,
                           std::set<std::string>& visited) {
    if (visited.count(type)) {
        return true;  // 发现循环
    }
    visited.insert(type);
    
    auto it = inheritanceMap.find(type);
    if (it != inheritanceMap.end() && !it->second.empty()) {
        return hasCircularInheritance(it->second, inheritanceMap, visited);
    }
    return false;
}

// 检测循环include
bool hasCircularInclude(const std::string& file, 
                       const std::unordered_map<std::string, std::set<std::string>>& includeMap,
                       std::set<std::string>& visited) {
    if (visited.count(file)) {
        return true;  // 发现循环
    }
    visited.insert(file);
    
    auto it = includeMap.find(file);
    if (it != includeMap.end()) {
        for (const auto& included : it->second) {
            if (hasCircularInclude(included, includeMap, visited)) {
                return true;
            }
        }
    }
    visited.erase(file);  // 回溯
    return false;
}

// 获取类型的实际类型（内置、struct、block、enum、annotation）
enum class TypeCategory {
    Builtin,
    Struct,
    Block,
    Enum,
    Annotation,
    Unknown
};

TypeCategory getTypeCategory(const std::string& typeName, 
                           const std::unordered_map<std::string, const ast::Node*>& typeTable) {
    if (kBuiltinTypes.count(typeName)) {
        return TypeCategory::Builtin;
    }
    
    auto it = typeTable.find(typeName);
    if (it == typeTable.end()) {
        return TypeCategory::Unknown;
    }
    
    switch (it->second->nodeType()) {
        case ast::NodeType::StructDecl:
            return TypeCategory::Struct;
        case ast::NodeType::BlockDecl:
            return TypeCategory::Block;
        case ast::NodeType::EnumDecl:
            return TypeCategory::Enum;
        case ast::NodeType::AnnotationDecl:
            return TypeCategory::Annotation;
        default:
            return TypeCategory::Unknown;
    }
}

// 检查注解字段类型是否合法（只允许内置类型）
bool isValidAnnotationFieldType(const std::string& typeName,
                               const std::unordered_map<std::string, const ast::Node*>& typeTable) {
    TypeCategory cat = getTypeCategory(typeName, typeTable);
    // 注解字段可以使用内置类型和其他注解类型
    return cat == TypeCategory::Builtin || cat == TypeCategory::Annotation;
}

// 检查struct/block字段类型是否合法（不允许annotation、struct）
bool isValidStructBlockFieldType(const std::string& typeName,
                                const std::unordered_map<std::string, const ast::Node*>& typeTable) {
    TypeCategory cat = getTypeCategory(typeName, typeTable);
    return cat == TypeCategory::Builtin || cat == TypeCategory::Block || cat == TypeCategory::Enum;
}

// 提取类型名称（递归处理容器类型）
std::string extractTypeName(const ast::Type* type) {
    if (auto* named = dynamic_cast<const ast::NamedType*>(type)) {
        return named->name;
    } else if (auto* container = dynamic_cast<const ast::ContainerType*>(type)) {
        return extractTypeName(container->elementType.get());
    }
    return "";
}
}

std::vector<SyntaxDiagnostic> SyntaxChecker::check(const ast::Document& doc, const std::string& entryFile) {
    std::vector<SyntaxDiagnostic> diagnostics;
    std::unordered_map<std::string, const ast::Node*> typeTable; // 名称->声明
    std::unordered_set<std::string> annotationSet;
    std::unordered_map<std::string, ast::NodeType> nameTypeMap; // 名称->类型
    std::unordered_map<std::string, std::string> inheritanceMap; // 子->父
    std::unordered_map<std::string, std::set<std::string>> includeMap; // 文件->包含的文件列表
    
    // 当前命名空间
    std::string currentNamespace = "";
    
    // 1. 收集所有类型、注解定义，检测重复定义/命名冲突
    for (const auto& decl : doc.declarations) {
        std::string name;
        ast::NodeType type = decl->nodeType();
        
        // 处理命名空间声明
        if (type == ast::NodeType::NamespaceDecl) {
            auto namespaceDecl = static_cast<const ast::Namespace*>(decl.get());
            currentNamespace = "";
            for (size_t i = 0; i < namespaceDecl->name.size(); ++i) {
                if (i > 0) currentNamespace += ".";
                currentNamespace += namespaceDecl->name[i];
            }
            continue;
        }
        
        switch (type) {
        case ast::NodeType::StructDecl:
            name = static_cast<const ast::Struct*>(decl.get())->name;
            break;
        case ast::NodeType::BlockDecl:
            name = static_cast<const ast::Block*>(decl.get())->name;
            break;
        case ast::NodeType::EnumDecl:
            name = static_cast<const ast::Enum*>(decl.get())->name;
            break;
        case ast::NodeType::AnnotationDecl:
            name = static_cast<const ast::AnnotationDecl*>(decl.get())->name;
            // 对于注解，需要添加完全限定名到集合中
            if (!currentNamespace.empty()) {
                annotationSet.insert(currentNamespace + "." + name);
            }
            annotationSet.insert(name); // 也添加简单名称以支持同命名空间内的引用
            break;
        default:
            break;
        }
        if (!name.empty()) {
            // 构建完全限定名
            std::string fullName = name;
            if (!currentNamespace.empty()) {
                fullName = currentNamespace + "." + name;
            }
            
            auto it = nameTypeMap.find(fullName);
            if (it != nameTypeMap.end()) {
                if (it->second == type) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "重复定义类型或注解: " + fullName, entryFile, 0, 0});
                } else {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "命名冲突: " + fullName, entryFile, 0, 0});
                }
            } else {
                nameTypeMap[fullName] = type;
                typeTable[fullName] = decl.get();
                // 也添加简单名称的映射
                if (!currentNamespace.empty()) {
                    nameTypeMap[name] = type;
                    typeTable[name] = decl.get();
                }
            }
        }
    }

    // 2. 检查各种类型的字段和继承关系
    for (const auto& decl : doc.declarations) {
        if (decl->nodeType() == ast::NodeType::StructDecl) {
            const auto* s = static_cast<const ast::Struct*>(decl.get());
            
            // 检查字段名重复
            std::set<std::string> fieldNames;
            for (const auto& field : s->fields) {
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段名重复: " + field->name, entryFile, field->location.line, field->location.column});
                }
                
                // 检查字段类型
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty()) {
                    if (!isValidStructBlockFieldType(typeName, typeTable)) {
                        TypeCategory cat = getTypeCategory(typeName, typeTable);
                        if (cat == TypeCategory::Unknown) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段类型未定义: " + typeName, entryFile, field->location.line, field->location.column});
                        } else if (cat == TypeCategory::Annotation) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "不能将注解用作字段类型: " + typeName, entryFile, field->location.line, field->location.column});
                        } else if (cat == TypeCategory::Struct) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "不能将struct用作字段类型: " + typeName, entryFile, field->location.line, field->location.column});
                        }
                    }
                }
                
                // 检查字段注解存在性
                for (const auto& ann : field->annotations) {
                    if (!annotationSet.count(ann->name)) {
                        diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                    }
                }
            }
            
            // 检查结构体注解存在性
            for (const auto& ann : s->annotations) {
                if (!annotationSet.count(ann->name)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "结构体注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                }
            }
            
            // 检查结构体继承合法性
            if (!s->baseName.empty()) {
                inheritanceMap[s->name] = s->baseName;
                auto it = typeTable.find(s->baseName);
                if (it == typeTable.end()) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "继承的父类型未定义: " + s->baseName, entryFile, s->location.line, s->location.column});
                } else if (it->second->nodeType() != ast::NodeType::BlockDecl) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "struct 只能继承 block 类型: " + s->baseName, entryFile, s->location.line, s->location.column});
                }
            }
            
        } else if (decl->nodeType() == ast::NodeType::BlockDecl) {
            const auto* b = static_cast<const ast::Block*>(decl.get());
            
            // 检查字段名重复和类型
            std::set<std::string> fieldNames;
            for (const auto& field : b->fields) {
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段名重复: " + field->name, entryFile, field->location.line, field->location.column});
                }
                
                // 检查字段类型
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty()) {
                    if (!isValidStructBlockFieldType(typeName, typeTable)) {
                        TypeCategory cat = getTypeCategory(typeName, typeTable);
                        if (cat == TypeCategory::Unknown) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段类型未定义: " + typeName, entryFile, field->location.line, field->location.column});
                        } else if (cat == TypeCategory::Annotation) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "不能将注解用作字段类型: " + typeName, entryFile, field->location.line, field->location.column});
                        } else if (cat == TypeCategory::Struct) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "不能将struct用作字段类型: " + typeName, entryFile, field->location.line, field->location.column});
                        }
                    }
                }
                
                // 检查字段注解存在性
                for (const auto& ann : field->annotations) {
                    if (!annotationSet.count(ann->name)) {
                        diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                    }
                }
            }
            
            // 检查块注解存在性
            for (const auto& ann : b->annotations) {
                if (!annotationSet.count(ann->name)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "块注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                }
            }
            
            // 检查继承合法性
            if (!b->baseName.empty()) {
                inheritanceMap[b->name] = b->baseName;
                auto it = typeTable.find(b->baseName);
                if (it == typeTable.end()) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "继承的父类型未定义: " + b->baseName, entryFile, b->location.line, b->location.column});
                } else if (it->second->nodeType() != ast::NodeType::BlockDecl) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "block 只能继承 block 类型: " + b->baseName, entryFile, b->location.line, b->location.column});
                }
            }
            
        } else if (decl->nodeType() == ast::NodeType::EnumDecl) {
            const auto* e = static_cast<const ast::Enum*>(decl.get());
            
            // 检查枚举值名称重复
            std::set<std::string> enumValueNames;
            for (const auto& value : e->values) {
                if (!enumValueNames.insert(value->name).second) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "枚举值名称重复: " + value->name, entryFile, value->location.line, value->location.column});
                }
            }
            
        } else if (decl->nodeType() == ast::NodeType::AnnotationDecl) {
            const auto* a = static_cast<const ast::AnnotationDecl*>(decl.get());
            
            // 检查注解字段名重复和类型
            std::set<std::string> fieldNames;
            for (const auto& field : a->fields) {
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "注解字段名重复: " + field->name, entryFile, field->location.line, field->location.column});
                }
                
                // 检查注解字段类型（允许内置类型和其他注解类型）
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty()) {
                    if (!isValidAnnotationFieldType(typeName, typeTable)) {
                        TypeCategory cat = getTypeCategory(typeName, typeTable);
                        if (cat == TypeCategory::Unknown) {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "注解字段类型未定义: " + typeName, entryFile, field->location.line, field->location.column});
                        } else {
                            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "注解字段只能使用内置类型或其他注解类型: " + typeName, entryFile, field->location.line, field->location.column});
                        }
                    }
                }
            }
        }
    }
    
    // 3. 检查循环继承
    for (const auto& [child, parent] : inheritanceMap) {
        std::set<std::string> visited;
        if (hasCircularInheritance(child, inheritanceMap, visited)) {
            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "发现循环继承: " + child, entryFile, 0, 0});
        }
    }
    
    // 4. 检查循环include（这里简化处理，实际应该从parser获取include信息）
    for (const auto& [file, includes] : includeMap) {
        std::set<std::string> visited;
        if (hasCircularInclude(file, includeMap, visited)) {
            diagnostics.push_back({SyntaxDiagnostic::Level::Error, "发现循环include: " + file, entryFile, 0, 0});
        }
    }
    
    return diagnostics;
}




// 新的方法实现，支持外部声明注册表
std::vector<SyntaxDiagnostic> SyntaxChecker::check(
    const ast::Document& doc,
    const std::string& entryFile,
    const std::map<std::string, KnownDecl>& includedDeclarations,
    std::map<std::string, KnownDecl>& currentDeclarations) {
    
    std::vector<SyntaxDiagnostic> diagnostics;
    
    // 获取当前文档的命名空间
    std::string currentNamespace = "";
    if (doc.hasNamespace()) {
        for (size_t i = 0; i < doc.m_namespace->name.size(); ++i) {
            if (i > 0) currentNamespace += ".";
            currentNamespace += doc.m_namespace->name[i];
        }
    }
    
    // 合并所有可用的声明（包含的声明 + 当前声明）
    auto getAllDeclarations = [&]() -> std::map<std::string, KnownDecl> {
        std::map<std::string, KnownDecl> allDecls = includedDeclarations;
        for (const auto& [name, decl] : currentDeclarations) {
            allDecls[name] = decl;
        }
        return allDecls;
    };
    
    // 第一遍：收集当前文档的所有声明
    for (const auto& decl : doc.declarations) {
        std::string declName;
        ast::NodeType declType = decl->nodeType();
        
        // 获取声明名称
        switch (declType) {
            case ast::NodeType::StructDecl: {
                auto structDecl = static_cast<const ast::Struct*>(decl.get());
                declName = structDecl->name;
                break;
            }
            case ast::NodeType::BlockDecl: {
                auto blockDecl = static_cast<const ast::Block*>(decl.get());
                declName = blockDecl->name;
                break;
            }
            case ast::NodeType::EnumDecl: {
                auto enumDecl = static_cast<const ast::Enum*>(decl.get());
                declName = enumDecl->name;
                break;
            }
            case ast::NodeType::AnnotationDecl: {
                auto annotationDecl = static_cast<const ast::AnnotationDecl*>(decl.get());
                declName = annotationDecl->name;
                break;
            }
            default:
                continue; // 跳过其他类型
        }
        
        std::string qualifiedName = getFullName(declName, currentNamespace);
        
        // 检查名称冲突
        if (checkNameExists(declName, currentNamespace, includedDeclarations) ||
            currentDeclarations.find(qualifiedName) != currentDeclarations.end()) {
            diagnostics.push_back({
                SyntaxDiagnostic::Level::Error,
                "名称冲突: " + qualifiedName,
                entryFile,
                decl->location.line,
                decl->location.column
            });
            continue;
        }
        
        // 添加到当前声明中  
        currentDeclarations[qualifiedName] = {
            currentNamespace,
            declType,
            declName,
            entryFile,
            decl
        };
        
        // 同时添加简单名称映射（用于同命名空间内的引用）
        if (!currentNamespace.empty()) {
            currentDeclarations[declName] = {
                currentNamespace,
                declType,
                declName,
                entryFile,
                decl
            };
        }
    }
    
    // 第二遍：验证继承关系和字段类型
    auto allDeclarations = getAllDeclarations();
    
    for (const auto& decl : doc.declarations) {
        ast::NodeType declType = decl->nodeType();
        
        if (declType == ast::NodeType::StructDecl) {
            const auto* structDecl = static_cast<const ast::Struct*>(decl.get());
            
            // 检查继承关系
            if (!structDecl->baseName.empty()) {
                // 查找父类型
                auto parentDecl = findDeclaration(structDecl->baseName, currentNamespace, allDeclarations);
                if (!parentDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "继承的父类型未定义: " + structDecl->baseName,
                        entryFile,
                        structDecl->location.line,
                        structDecl->location.column
                    });
                } else if (parentDecl->type != ast::NodeType::BlockDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "struct 只能继承 block 类型: " + structDecl->baseName,
                        entryFile,
                        structDecl->location.line,
                        structDecl->location.column
                    });
                }
            }
            
            // 检查字段类型
            std::set<std::string> fieldNames;
            for (const auto& field : structDecl->fields) {
                // 检查字段名重复
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "字段名重复: " + field->name,
                        entryFile,
                        field->location.line,
                        field->location.column
                    });
                }
                
                // 检查字段类型
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty() && !isBuiltinType(typeName)) {
                    auto typeDecl = findDeclaration(typeName, currentNamespace, allDeclarations);
                    if (!typeDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "字段类型未定义: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    } else if (typeDecl->type == ast::NodeType::AnnotationDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "不能将注解用作字段类型: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    } else if (typeDecl->type == ast::NodeType::StructDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "不能将struct用作字段类型: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    }
                }
                
                // 检查字段注解
                for (const auto& ann : field->annotations) {
                    auto annDecl = findDeclaration(ann->name, currentNamespace, allDeclarations);
                    if (!annDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "字段注解未定义: " + ann->name,
                            entryFile,
                            ann->location.line,
                            ann->location.column
                        });
                    } else if (annDecl->type != ast::NodeType::AnnotationDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "只能使用注解类型作为注解: " + ann->name,
                            entryFile,
                            ann->location.line,
                            ann->location.column
                        });
                    }
                }
            }
            
            // 检查结构体注解
            for (const auto& ann : structDecl->annotations) {
                auto annDecl = findDeclaration(ann->name, currentNamespace, allDeclarations);
                if (!annDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "结构体注解未定义: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                } else if (annDecl->type != ast::NodeType::AnnotationDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "只能使用注解类型作为注解: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                }
            }
            
        } else if (declType == ast::NodeType::BlockDecl) {
            const auto* blockDecl = static_cast<const ast::Block*>(decl.get());
            
            // 检查继承关系
            if (!blockDecl->baseName.empty()) {
                auto parentDecl = findDeclaration(blockDecl->baseName, currentNamespace, allDeclarations);
                if (!parentDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "继承的父类型未定义: " + blockDecl->baseName,
                        entryFile,
                        blockDecl->location.line,
                        blockDecl->location.column
                    });
                } else if (parentDecl->type != ast::NodeType::BlockDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "block 只能继承 block 类型: " + blockDecl->baseName,
                        entryFile,
                        blockDecl->location.line,
                        blockDecl->location.column
                    });
                }
            }
            
            // 检查字段类型（与struct相同的逻辑）
            std::set<std::string> fieldNames;
            for (const auto& field : blockDecl->fields) {
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "字段名重复: " + field->name,
                        entryFile,
                        field->location.line,
                        field->location.column
                    });
                }
                
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty() && !isBuiltinType(typeName)) {
                    auto typeDecl = findDeclaration(typeName, currentNamespace, allDeclarations);
                    if (!typeDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "字段类型未定义: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    } else if (typeDecl->type == ast::NodeType::AnnotationDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "不能将注解用作字段类型: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    } else if (typeDecl->type == ast::NodeType::StructDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "不能将struct用作字段类型: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    }
                }
                
                for (const auto& ann : field->annotations) {
                    auto annDecl = findDeclaration(ann->name, currentNamespace, allDeclarations);
                    if (!annDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "字段注解未定义: " + ann->name,
                            entryFile,
                            ann->location.line,
                            ann->location.column
                        });
                    } else if (annDecl->type != ast::NodeType::AnnotationDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "只能使用注解类型作为注解: " + ann->name,
                            entryFile,
                            ann->location.line,
                            ann->location.column
                        });
                    }
                }
            }
            
            for (const auto& ann : blockDecl->annotations) {
                auto annDecl = findDeclaration(ann->name, currentNamespace, allDeclarations);
                if (!annDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "块注解未定义: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                } else if (annDecl->type != ast::NodeType::AnnotationDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "只能使用注解类型作为注解: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                }
            }
            
        } else if (declType == ast::NodeType::EnumDecl) {
            const auto* enumDecl = static_cast<const ast::Enum*>(decl.get());
            
            // 检查枚举值名称重复
            std::set<std::string> enumValueNames;
            for (const auto& value : enumDecl->values) {
                if (!enumValueNames.insert(value->name).second) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "枚举值名称重复: " + value->name,
                        entryFile,
                        value->location.line,
                        value->location.column
                    });
                }
            }
            
            // 检查枚举注解
            for (const auto& ann : enumDecl->annotations) {
                auto annDecl = findDeclaration(ann->name, currentNamespace, allDeclarations);
                if (!annDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "枚举注解未定义: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                } else if (annDecl->type != ast::NodeType::AnnotationDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "只能使用注解类型作为注解: " + ann->name,
                        entryFile,
                        ann->location.line,
                        ann->location.column
                    });
                }
            }
            
        } else if (declType == ast::NodeType::AnnotationDecl) {
            const auto* annotationDecl = static_cast<const ast::AnnotationDecl*>(decl.get());
            
            // 检查注解继承关系
            if (!annotationDecl->baseName.empty()) {
                auto parentDecl = findDeclaration(annotationDecl->baseName, currentNamespace, allDeclarations);
                if (!parentDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "继承的父注解未定义: " + annotationDecl->baseName,
                        entryFile,
                        annotationDecl->location.line,
                        annotationDecl->location.column
                    });
                } else if (parentDecl->type != ast::NodeType::AnnotationDecl) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "注解只能继承注解类型: " + annotationDecl->baseName,
                        entryFile,
                        annotationDecl->location.line,
                        annotationDecl->location.column
                    });
                }
            }
            
            // 检查注解字段类型
            std::set<std::string> fieldNames;
            for (const auto& field : annotationDecl->fields) {
                if (!fieldNames.insert(field->name).second) {
                    diagnostics.push_back({
                        SyntaxDiagnostic::Level::Error,
                        "注解字段名重复: " + field->name,
                        entryFile,
                        field->location.line,
                        field->location.column
                    });
                }
                
                std::string typeName = extractTypeName(field->type.get());
                if (!typeName.empty() && !isBuiltinType(typeName)) {
                    auto typeDecl = findDeclaration(typeName, currentNamespace, allDeclarations);
                    if (!typeDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "注解字段类型未定义: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    } else if (typeDecl->type != ast::NodeType::AnnotationDecl) {
                        diagnostics.push_back({
                            SyntaxDiagnostic::Level::Error,
                            "注解字段只能使用内置类型或其他注解类型: " + typeName,
                            entryFile,
                            field->location.line,
                            field->location.column
                        });
                    }
                }
            }
        }
    }
    
    return diagnostics;
}

// 辅助方法实现
bool SyntaxChecker::checkNameExists(const std::string& name, const std::string& ns,
                                   const std::map<std::string, KnownDecl>& declarations) const {
    std::string fullName = getFullName(name, ns);
    
    // 首先检查完全限定名
    if (declarations.find(fullName) != declarations.end()) {
        return true;
    }
    
    // 如果有命名空间，也检查简单名称（同命名空间内）
    if (!ns.empty() && declarations.find(name) != declarations.end()) {
        return true;
    }
    
    return false;
}

bool SyntaxChecker::isTypeMatch(const ast::NodeType& expectedType, const std::string& typeName,
                               const std::string& ns, const std::map<std::string, KnownDecl>& declarations) const {
    std::string fullName = getFullName(typeName, ns);
    
    auto it = declarations.find(fullName);
    if (it == declarations.end()) {
        // 也尝试简单名称
        it = declarations.find(typeName);
        if (it == declarations.end()) {
            return false;
        }
    }
    
    return it->second.type == expectedType;
}

bool SyntaxChecker::isBuiltinType(const std::string& typeName) const {
    return kBuiltinTypes.find(typeName) != kBuiltinTypes.end();
}



std::string SyntaxChecker::getFullName(const std::string& name, const std::string& ns) const {
    if (ns.empty()) {
        return name;
    }
    return ns + "." + name;
}

const checker::KnownDecl* SyntaxChecker::findDeclaration(const std::string& name, const std::string& currentNamespace,
                                                        const std::map<std::string, KnownDecl>& declarations) const {
    // 1. 首先尝试完全限定名查找
    auto it = declarations.find(name);
    if (it != declarations.end()) {
        return &it->second;
    }
    
    // 2. 如果有当前命名空间，尝试在当前命名空间中查找
    if (!currentNamespace.empty()) {
        std::string qualifiedName = getFullName(name, currentNamespace);
        it = declarations.find(qualifiedName);
        if (it != declarations.end()) {
            return &it->second;
        }
    }
    
    // 3. 如果名称包含点号，可能是跨命名空间引用，直接查找
    if (name.find('.') != std::string::npos) {
        it = declarations.find(name);
        if (it != declarations.end()) {
            return &it->second;
        }
    }
    
    // 4. 最后尝试简单名称查找（用于同命名空间内的引用）
    for (const auto& [declName, decl] : declarations) {
        // 提取简单名称进行比较
        size_t lastDot = declName.find_last_of('.');
        std::string simpleName = (lastDot != std::string::npos) ? declName.substr(lastDot + 1) : declName;
        if (simpleName == name) {
            return &decl;
        }
    }
    
    return nullptr;
}





} // namespace checker
} // namespace mota 