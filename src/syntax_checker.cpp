#include "syntax_checker.h"
#include <unordered_set>
#include <unordered_map>
#include <set>

namespace mota {
namespace checker {

namespace {
// 内置基础类型
const std::set<std::string> kBuiltinTypes = {
    "int8", "int16", "int32", "int64",
    "uint8", "uint16", "uint32", "uint64",
    "float32", "float64", "string", "bool", "bytes"
};
}

std::vector<SyntaxDiagnostic> SyntaxChecker::check(const ast::Document& doc, const std::string& entryFile) {
    std::vector<SyntaxDiagnostic> diagnostics;
    std::unordered_map<std::string, const ast::Node*> typeTable; // 名称->声明
    std::unordered_set<std::string> annotationSet;
    std::unordered_map<std::string, std::string> inheritanceMap; // 子->父

    // 1. 收集所有类型、注解定义
    for (const auto& decl : doc.declarations) {
        switch (decl->nodeType()) {
        case ast::NodeType::StructDecl:
        case ast::NodeType::BlockDecl:
        case ast::NodeType::EnumDecl:
            typeTable[static_cast<const ast::Struct*>(decl.get())->name] = decl.get();
            break;
        case ast::NodeType::AnnotationDecl:
            annotationSet.insert(static_cast<const ast::Annotation*>(decl.get())->name);
            break;
        default:
            break;
        }
    }

    // 2. 检查类型引用、继承、注解存在性
    for (const auto& decl : doc.declarations) {
        if (decl->nodeType() == ast::NodeType::StructDecl) {
            const auto* s = static_cast<const ast::Struct*>(decl.get());
            // 字段类型检查
            for (const auto& field : s->fields) {
                std::string typeName;
                if (auto* named = dynamic_cast<ast::NamedType*>(field->type.get())) {
                    typeName = named->name;
                } else if (auto* ct = dynamic_cast<ast::ContainerType*>(field->type.get())) {
                    if (auto* elem = dynamic_cast<ast::NamedType*>(ct->elementType.get()))
                        typeName = elem->name;
                }
                if (!typeName.empty() && !kBuiltinTypes.count(typeName) && !typeTable.count(typeName)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段类型未定义: " + typeName, entryFile, field->location.line, field->location.column});
                }
                // 注解存在性
                for (const auto& ann : field->annotations) {
                    if (!annotationSet.count(ann->name)) {
                        diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                    }
                }
            }
            // 结构体注解存在性
            for (const auto& ann : s->annotations) {
                if (!annotationSet.count(ann->name)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "结构体注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                }
            }
        } else if (decl->nodeType() == ast::NodeType::BlockDecl) {
            const auto* b = static_cast<const ast::Block*>(decl.get());
            // 字段类型检查
            for (const auto& field : b->fields) {
                std::string typeName;
                if (auto* named = dynamic_cast<ast::NamedType*>(field->type.get())) {
                    typeName = named->name;
                } else if (auto* ct = dynamic_cast<ast::ContainerType*>(field->type.get())) {
                    if (auto* elem = dynamic_cast<ast::NamedType*>(ct->elementType.get()))
                        typeName = elem->name;
                }
                if (!typeName.empty() && !kBuiltinTypes.count(typeName) && !typeTable.count(typeName)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段类型未定义: " + typeName, entryFile, field->location.line, field->location.column});
                }
                // 注解存在性
                for (const auto& ann : field->annotations) {
                    if (!annotationSet.count(ann->name)) {
                        diagnostics.push_back({SyntaxDiagnostic::Level::Error, "字段注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                    }
                }
            }
            // 块注解存在性
            for (const auto& ann : b->annotations) {
                if (!annotationSet.count(ann->name)) {
                    diagnostics.push_back({SyntaxDiagnostic::Level::Error, "块注解未定义: " + ann->name, entryFile, ann->location.line, ann->location.column});
                }
            }
            // 继承合法性（只允许继承 block，且父类型存在且无环）
            // TODO: 目前 AST 未体现继承关系，后续补充
        } else if (decl->nodeType() == ast::NodeType::StructDecl) {
            // 结构体继承合法性（只允许继承 block，且父类型存在且无环）
            // TODO: 目前 AST 未体现继承关系，后续补充
        }
        // TODO: 枚举、注解的其他检查
    }
    // TODO: 定义顺序、循环依赖、include 递归等
    return diagnostics;
}

} // namespace checker
} // namespace mota 