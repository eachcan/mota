#include "generator.h"
#include <sstream>
#include <filesystem>
#include <memory>
#include <variant>

namespace mota {

CppGenerator::CppGenerator(const std::shared_ptr<FileNode>& ast) : ast(ast) {}

std::vector<GeneratedFile> CppGenerator::generate() {
    std::vector<GeneratedFile> files;
    files.push_back(generateHeader());
    files.push_back(generateSource());
    return files;
}

GeneratedFile CppGenerator::generateHeader() {
    std::stringstream ss;
    
    // 添加头文件保护和包含
    ss << "#pragma once\n"
       << "#include \"base_model.h\"\n"
       << "#include <optional>\n"
       << "#include <vector>\n"
       << "#include <map>\n\n";
    
    // 生成命名空间开始
    if (!currentNamespace.empty()) {
        ss << "namespace " << currentNamespace << " {\n\n";
    }
    
    // 生成所有声明
    for (const auto& decl : ast->declarations) {
        if (auto enumDecl = std::dynamic_pointer_cast<EnumDecl>(decl)) {
            ss << generateEnumDecl(enumDecl);
        } else if (auto blockDecl = std::dynamic_pointer_cast<BlockDecl>(decl)) {
            ss << generateBlockDecl(blockDecl);
        } else if (auto structDecl = std::dynamic_pointer_cast<StructDecl>(decl)) {
            ss << generateStructDecl(structDecl);
        }
    }
    
    // 生成命名空间结束
    if (!currentNamespace.empty()) {
        ss << "} // namespace " << currentNamespace << "\n";
    }
    
    std::filesystem::path headerPath("generated/models.h");
    return {headerPath.make_preferred().string(), ss.str()};
}

GeneratedFile CppGenerator::generateSource() {
    std::stringstream ss;
    
    // 添加必要的包含
    ss << "#include \"models.h\"\n"
       << "#include <QCborMap>\n"
       << "#include <QCborArray>\n\n";
    
    // 生成命名空间开始
    if (!currentNamespace.empty()) {
        ss << "namespace " << currentNamespace << " {\n\n";
    }
    
    // 生成所有实现
    for (const auto& decl : ast->declarations) {
        if (auto enumDecl = std::dynamic_pointer_cast<EnumDecl>(decl)) {
            ss << generateEnumImpl(enumDecl);
        } else if (auto blockDecl = std::dynamic_pointer_cast<BlockDecl>(decl)) {
            ss << generateBlockImpl(blockDecl);
        } else if (auto structDecl = std::dynamic_pointer_cast<StructDecl>(decl)) {
            ss << generateStructImpl(structDecl);
        }
    }
    
    // 生成命名空间结束
    if (!currentNamespace.empty()) {
        ss << "} // namespace " << currentNamespace << "\n";
    }
    
    std::filesystem::path sourcePath("generated/models.cpp");
    return {sourcePath.make_preferred().string(), ss.str()};
}

std::string CppGenerator::generateEnumDecl(const std::shared_ptr<EnumDecl>& enumDecl) {
    std::stringstream ss;
    
    // 生成注释
    if (!enumDecl->comment.empty()) {
        ss << "// " << enumDecl->comment << "\n";
    }
    
    ss << "enum class " << enumDecl->name << " {\n";
    
    // 生成枚举值
    for (const auto& value : enumDecl->values) {
        if (!value->comment.empty()) {
            ss << "    // " << value->comment << "\n";
        }
        ss << "    " << value->name << " = " << value->value << ",\n";
    }
    
    ss << "};\n\n";
    return ss.str();
}

std::string CppGenerator::generateBlockDecl(const std::shared_ptr<BlockDecl>& blockDecl) {
    std::stringstream ss;
    
    // 生成注释
    if (!blockDecl->comment.empty()) {
        ss << "// " << blockDecl->comment << "\n";
    }
    
    ss << "class " << blockDecl->name << " : public ";
    if (blockDecl->hasParent()) {
        ss << blockDecl->parentName;
    } else {
        ss << "mota::BaseBlock";
    }
    ss << " {\n";
    ss << "public:\n";
    
    // 生成字段
    for (const auto& field : blockDecl->fields) {
        ss << "    " << generateFieldDecl(field) << "\n";
    }
    
    // 生成序列化方法
    ss << "\n    QCborValue toCbor() const override;\n";
    ss << "    void fromCbor(const QCborValue& cbor) override;\n";
    
    ss << "};\n\n";
    return ss.str();
}

std::string CppGenerator::generateFieldDecl(const std::shared_ptr<FieldDecl>& field) {
    std::stringstream ss;
    
    // 生成注释
    if (!field->comment.empty()) {
        ss << "// " << field->comment << "\n    ";
    }
    
    // 生成字段类型和名称
    ss << getCppType(field->type) << " " << field->name;
    
    // 生成默认值
    if (field->defaultValue) {
        ss << " = " << getDefaultValue(field->type, field->defaultValue);
    }
    
    ss << ";";
    return ss.str();
}

std::string CppGenerator::generateToCborImpl(
    const std::vector<std::shared_ptr<FieldDecl>>& fields,
    const std::string& parentType) 
{
    std::stringstream ss;
    ss << "QCborMap map;\n";
    
    // 如果有父类，先调用父类的序列化
    if (!parentType.empty()) {
        ss << "    auto parentMap = " << parentType << "::toCbor().toMap();\n";
        ss << "    for (auto it = parentMap.begin(); it != parentMap.end(); ++it) {\n";
        ss << "        map.insert(it.key(), it.value());\n";
        ss << "    }\n\n";
    }
    
    // 序列化每个字段
    for (const auto& field : fields) {
        ss << "    " << getSerializeExpr(field->name, field->type) << "\n";
    }
    
    ss << "    return map;";
    return ss.str();
}

std::string CppGenerator::getFilePath(const std::vector<Annotation>& annotations) {
    for (const auto& annotation : annotations) {
        auto it = annotation.attributes.find("file");
        if (it != annotation.attributes.end()) {
            std::filesystem::path filePath(it->second);
            return filePath.make_preferred().string();
        }
    }
    return "";
}

std::string CppGenerator::generateStructDecl(const std::shared_ptr<StructDecl>& structDecl) {
    std::stringstream ss;
    
    if (!structDecl->comment.empty()) {
        ss << "// " << structDecl->comment << "\n";
    }
    
    ss << "class " << structDecl->name << " : public mota::BaseModel {\n"
       << "public:\n";
    
    // 生成字段
    for (const auto& field : structDecl->fields) {
        ss << "    " << generateFieldDecl(field) << "\n";
    }
    
    // 生成序列化方法
    ss << "\n    QCborValue toCbor() const override;\n"
       << "    void fromCbor(const QCborValue& cbor) override;\n";
    
    ss << "};\n\n";
    return ss.str();
}

std::string CppGenerator::generateStructImpl(const std::shared_ptr<StructDecl>& structDecl) {
    std::stringstream ss;
    
    // 生成toCbor实现
    ss << "QCborValue " << structDecl->name << "::toCbor() const {\n"
       << "    " << generateToCborImpl(structDecl->fields) << "\n"
       << "}\n\n";
    
    // 生成fromCbor实现
    ss << "void " << structDecl->name << "::fromCbor(const QCborValue& cbor) {\n"
       << "    " << generateFromCborImpl(structDecl->fields) << "\n"
       << "}\n\n";
    
    return ss.str();
}

std::string CppGenerator::getQtType(const TypePtr& type) {
    if (auto basicType = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        switch (basicType->type) {
            case BasicType::Int8: return "qint8";
            case BasicType::Int16: return "qint16";
            case BasicType::Int32: return "qint32";
            case BasicType::Int64: return "qint64";
            case BasicType::Float32: return "float";
            case BasicType::Double64: return "double";
            case BasicType::String: return "QString";
            case BasicType::Bool: return "bool";
            case BasicType::Bytes: return "QByteArray";
        }
    }
    return "QCborValue";
}

std::string CppGenerator::getSerializeExpr(const std::string& fieldName, const TypePtr& type) {
    std::stringstream ss;
    ss << "map.insert(\"" << fieldName << "\", ";
    
    if (auto modifiedType = std::dynamic_pointer_cast<ModifiedTypeNode>(type)) {
        if (modifiedType->modifier == ModifiedTypeNode::Modifier::Optional) {
            ss << fieldName << ".has_value() ? QCborValue(" << fieldName << ".value()) : QCborValue()";
        } else if (modifiedType->modifier == ModifiedTypeNode::Modifier::Repeated) {
            ss << "QCborArray::fromVariantList(" << fieldName << ")";
        }
    } else {
        ss << "QCborValue(" << fieldName << ")";
    }
    
    ss << ");";
    return ss.str();
}

std::string CppGenerator::getDeserializeExpr(const std::string& fieldName, const TypePtr& type) {
    std::stringstream ss;
    ss << "if (auto it = map.find(\"" << fieldName << "\"); it != map.end()) {\n";
    
    if (auto modifiedType = std::dynamic_pointer_cast<ModifiedTypeNode>(type)) {
        if (modifiedType->modifier == ModifiedTypeNode::Modifier::Optional) {
            ss << "        " << fieldName << " = it.value().to" << getQtType(modifiedType->baseType) << "();\n";
        } else if (modifiedType->modifier == ModifiedTypeNode::Modifier::Repeated) {
            ss << "        " << fieldName << " = it.value().toArray().toVariantList();\n";
        }
    } else {
        ss << "        " << fieldName << " = it.value().to" << getQtType(type) << "();\n";
    }
    
    ss << "    }";
    return ss.str();
}

std::string CppGenerator::generateEnumImpl(const std::shared_ptr<EnumDecl>& enumDecl) {
    std::stringstream ss;
    
    // 生成枚举转字符串函数
    ss << "QString toString(" << enumDecl->name << " value) {\n"
       << "    switch (value) {\n";
    
    for (const auto& value : enumDecl->values) {
        ss << "        case " << enumDecl->name << "::" << value->name 
           << ": return \"" << value->name << "\";\n";
    }
    
    ss << "        default: return QString();\n"
       << "    }\n"
       << "}\n\n";
    
    // 生成字符串转枚举函数
    ss << enumDecl->name << " fromString(const QString& str) {\n";
    for (const auto& value : enumDecl->values) {
        ss << "    if (str == \"" << value->name << "\") return " 
           << enumDecl->name << "::" << value->name << ";\n";
    }
    ss << "    return " << enumDecl->name << "::" << enumDecl->values.front()->name << ";\n"
       << "}\n\n";
    
    return ss.str();
}

std::string CppGenerator::generateBlockImpl(const std::shared_ptr<BlockDecl>& blockDecl) {
    std::stringstream ss;
    
    // 生成toCbor实现
    ss << "QCborValue " << blockDecl->name << "::toCbor() const {\n"
       << "    " << generateToCborImpl(blockDecl->fields, blockDecl->hasParent() ? blockDecl->parentName : "") << "\n"
       << "}\n\n";
    
    // 生成fromCbor实现
    ss << "void " << blockDecl->name << "::fromCbor(const QCborValue& cbor) {\n"
       << "    auto map = cbor.toMap();\n"
       << "    " << generateFromCborImpl(blockDecl->fields, blockDecl->hasParent() ? blockDecl->parentName : "") << "\n"
       << "}\n\n";
    
    return ss.str();
}

std::string CppGenerator::generateFromCborImpl(
    const std::vector<std::shared_ptr<FieldDecl>>& fields,
    const std::string& parentType)
{
    std::stringstream ss;
    
    // 如果有父类，先调用父类的反序列化
    if (!parentType.empty()) {
        ss << parentType << "::fromCbor(cbor);\n\n";
    }
    
    // 反序列化每个字段
    for (const auto& field : fields) {
        ss << "    " << getDeserializeExpr(field->name, field->type) << "\n";
    }
    
    return ss.str();
}

std::string CppGenerator::getCppType(const TypePtr& type) {
    if (auto basicType = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
        switch (basicType->type) {
            case BasicType::Int8: return "int8_t";
            case BasicType::Int16: return "int16_t";
            case BasicType::Int32: return "int32_t";
            case BasicType::Int64: return "int64_t";
            case BasicType::Float32: return "float";
            case BasicType::Double64: return "double";
            case BasicType::String: return "QString";
            case BasicType::Bool: return "bool";
            case BasicType::Bytes: return "QByteArray";
        }
    } else if (auto modifiedType = std::dynamic_pointer_cast<ModifiedTypeNode>(type)) {
        std::string baseType = getCppType(modifiedType->baseType);
        switch (modifiedType->modifier) {
            case ModifiedTypeNode::Modifier::Optional:
                return "std::optional<" + baseType + ">";
            case ModifiedTypeNode::Modifier::Repeated:
                return "QVector<" + baseType + ">";
            case ModifiedTypeNode::Modifier::Map:
                return "QMap<QString, " + baseType + ">";
        }
    } else if (auto customType = std::dynamic_pointer_cast<CustomTypeNode>(type)) {
        std::string fullName;
        for (const auto& ns : customType->namespaces) {
            fullName += ns + "::";
        }
        return fullName + customType->name;
    }
    
    return "void";
}

std::string CppGenerator::getDefaultValue(const TypePtr& type, const ExprPtr& defaultExpr) {
    if (auto literalExpr = std::dynamic_pointer_cast<LiteralExpr>(defaultExpr)) {
        if (auto basicType = std::dynamic_pointer_cast<BasicTypeNode>(type)) {
            switch (basicType->type) {
                case BasicType::String:
                    return "\"" + std::get<std::string>(literalExpr->value) + "\"";
                case BasicType::Bool:
                    return std::get<std::string>(literalExpr->value) == "true" ? "true" : "false";
                default:
                    return std::get<std::string>(literalExpr->value);
            }
        }
    } else if (auto arrayExpr = std::dynamic_pointer_cast<ArrayExpr>(defaultExpr)) {
        std::stringstream ss;
        ss << "{";
        for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << getDefaultValue(type, arrayExpr->elements[i]);
        }
        ss << "}";
        return ss.str();
    }
    
    return "";
}

std::string CppGenerator::getStorageConfig(const std::vector<Annotation>& annotations) {
    for (const auto& annotation : annotations) {
        if (annotation.attributes.find("file") != annotation.attributes.end()) {
            std::stringstream ss;
            ss << "StorageConfig{";
            
            std::string filePath;
            std::string formatAttr;
            
            // 首先收集所有属性
            for (const auto& [key, value] : annotation.attributes) {
                if (key == "file") {
                    filePath = value;
                    ss << ".filePath = \"" << value << "\", ";
                } else if (key == "format") {
                    formatAttr = value;
                } else if (key == "level") {
                    ss << ".level = \"" << value << "\", ";
                }
            }
            
            // 确定并添加文件格式
            std::string format = getFileFormat(filePath, formatAttr);
            ss << ".format = \"" << format << "\", ";
            
            ss << "}";
            return ss.str();
        }
    }
    return "StorageConfig{}";
}

std::string CppGenerator::getFileFormat(const std::string& filePath, const std::string& formatAttr) {
    if (!formatAttr.empty()) {
        return formatAttr;
    }
    
    // 从文件扩展名判断格式
    size_t dotPos = filePath.find_last_of('.');
    if (dotPos != std::string::npos) {
        std::string ext = filePath.substr(dotPos + 1);
        if (ext == "json") return "json";
        if (ext == "cbor") return "cbor";
        if (ext == "yaml" || ext == "yml") return "yaml";
    }
    return "unknown";
}

// TODO: 实现其他方法

}
