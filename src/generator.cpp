#include "generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>

namespace mota {
namespace generator {

Generator::Generator(const std::string& templateDir) : templateDir_(templateDir) {
}

bool Generator::loadConfig(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Cannot open config file: " << configPath << std::endl;
        return false;
    }
    
    // 读取并解析JSON5配置
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        // 移除行注释
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        content += line + "\n";
    }
    
    return parseConfig(content);
}

void Generator::buildTypeContext(const ast::Document& document) {
    // 清除之前的上下文
    typeContext_.clear();
    
    // 遍历文档中的所有声明，记录类型信息
    for (const auto& node : document.declarations) {
        switch (node->nodeType()) {
            case ast::NodeType::StructDecl: {
                auto structNode = static_cast<const ast::Struct*>(node.get());
                typeContext_[structNode->name] = "struct";
                break;
            }
            case ast::NodeType::BlockDecl: {
                auto blockNode = static_cast<const ast::Block*>(node.get());
                typeContext_[blockNode->name] = "block";
                break;
            }
            case ast::NodeType::EnumDecl: {
                auto enumNode = static_cast<const ast::Enum*>(node.get());
                typeContext_[enumNode->name] = "enum";
                break;
            }
            case ast::NodeType::AnnotationDecl: {
                auto annotationNode = static_cast<const ast::AnnotationDecl*>(node.get());
                typeContext_[annotationNode->name] = "annotation";
                break;
            }
            default:
                break;
        }
    }
}

bool Generator::parseConfig(const std::string& content) {
    // 简化的JSON5解析 - 在实际项目中应该使用专门的JSON解析库
    // 这里使用简单的字符串解析来提取配置值
    
    auto extractStringValue = [&](const std::string& key) -> std::string {
        std::string pattern = "\"" + key + "\"";
        size_t keyPos = content.find(pattern);
        if (keyPos == std::string::npos) return "";
        
        size_t colonPos = content.find(":", keyPos);
        if (colonPos == std::string::npos) return "";
        
        size_t quoteStart = content.find("\"", colonPos);
        if (quoteStart == std::string::npos) return "";
        
        size_t quoteEnd = content.find("\"", quoteStart + 1);
        if (quoteEnd == std::string::npos) return "";
        
        return content.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
    };
    
    auto extractBoolValue = [&](const std::string& key) -> bool {
        std::string pattern = "\"" + key + "\"";
        size_t keyPos = content.find(pattern);
        if (keyPos == std::string::npos) return false;
        
        size_t colonPos = content.find(":", keyPos);
        if (colonPos == std::string::npos) return false;
        
        size_t valueStart = content.find_first_not_of(" \t\n", colonPos + 1);
        if (valueStart == std::string::npos) return false;
        
        return content.substr(valueStart, 4) == "true";
    };
    
    auto extractObjectValues = [&](const std::string& objectKey) -> std::unordered_map<std::string, std::string> {
        std::unordered_map<std::string, std::string> result;
        std::string pattern = "\"" + objectKey + "\"";
        size_t objectStart = content.find(pattern);
        if (objectStart == std::string::npos) return result;
        
        size_t braceStart = content.find("{", objectStart);
        if (braceStart == std::string::npos) return result;
        
        size_t braceEnd = content.find("}", braceStart);
        if (braceEnd == std::string::npos) return result;
        
        std::string objectContent = content.substr(braceStart + 1, braceEnd - braceStart - 1);
        
        // 解析对象中的键值对
        size_t pos = 0;
        while (pos < objectContent.length()) {
            size_t keyStart = objectContent.find("\"", pos);
            if (keyStart == std::string::npos) break;
            
            size_t keyEnd = objectContent.find("\"", keyStart + 1);
            if (keyEnd == std::string::npos) break;
            
            std::string key = objectContent.substr(keyStart + 1, keyEnd - keyStart - 1);
            
            size_t colonPos = objectContent.find(":", keyEnd);
            if (colonPos == std::string::npos) break;
            
            size_t valueStart = objectContent.find("\"", colonPos);
            if (valueStart == std::string::npos) break;
            
            size_t valueEnd = objectContent.find("\"", valueStart + 1);
            if (valueEnd == std::string::npos) break;
            
            std::string value = objectContent.substr(valueStart + 1, valueEnd - valueStart - 1);
            result[key] = value;
            
            pos = valueEnd + 1;
        }
        
        return result;
    };
    
    // 解析基本配置
    config_.version = extractStringValue("version");
    config_.encoding = extractStringValue("encoding");
    
    // 解析模板映射
    config_.templates = extractObjectValues("templates");
    
    // 解析类型映射
    config_.typeMapping = extractObjectValues("type_mapping");
    
    // 解析访问器格式
    config_.accessorFormat.getterPrefix = extractStringValue("getter_prefix");
    config_.accessorFormat.setterPrefix = extractStringValue("setter_prefix");
    config_.accessorFormat.pascalCase = extractBoolValue("pascal_case");
    
    // 解析标识符格式
    config_.identifierFormat.style = extractStringValue("style");
    config_.identifierFormat.prefix = extractObjectValues("prefix");
    config_.identifierFormat.suffix = extractObjectValues("suffix");
    
    // 解析文件路径配置
    config_.filePath.path = extractStringValue("path");
    config_.filePath.type = extractStringValue("type");
    
    // 解析字段类型模板映射
    config_.fieldTypeTemplates = extractObjectValues("field_type_templates");
    
    // 解析模板变量定义
    config_.templateVariables = extractObjectValues("template_variables");
    
    // 解析类型接口映射
    config_.typeInterfaceMapping = extractObjectValues("type_interface_mapping");
    
    return true;
}

std::string Generator::loadTemplate(const std::string& templateName) {
    auto it = templateCache_.find(templateName);
    if (it != templateCache_.end()) {
        return it->second;
    }
    
    std::string templatePath = templateDir_ + "/" + templateName;
    std::ifstream file(templatePath);
    if (!file.is_open()) {
        std::cerr << "Cannot open template file: " << templatePath << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    templateCache_[templateName] = content;
    return content;
}

std::string Generator::renderTemplate(const std::string& templateContent, const TemplateVars& vars) {
    std::string result = templateContent;
    
    // 处理条件语句
    result = processConditionals(result, vars);
    
    // 处理模板函数（如 | map_type, | pascal_case 等）
    result = processTemplateFunctions(result, vars);
    
    // 替换变量
    for (const auto& pair : vars) {
        std::string placeholder = "{{" + pair.first + "}}";
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), pair.second);
            pos += pair.second.length();
        }
    }
    
    return result;
}

std::string Generator::processConditionals(const std::string& content, const TemplateVars& vars) {
    std::string result = content;
    
    // 手动查找和处理条件块
    size_t pos = 0;
    while (pos < result.length()) {
        // 查找条件开始标签 {{#CONDITION}}
        size_t startPos = result.find("{{#", pos);
        if (startPos == std::string::npos) break;
        
        size_t conditionStart = startPos + 3;
        size_t conditionEnd = result.find("}}", conditionStart);
        if (conditionEnd == std::string::npos) break;
        
        std::string conditionName = result.substr(conditionStart, conditionEnd - conditionStart);
        
        // 查找对应的结束标签 {{/CONDITION}}
        std::string endTag = "{{/" + conditionName + "}}";
        size_t endPos = result.find(endTag, conditionEnd);
        if (endPos == std::string::npos) {
            pos = conditionEnd + 2;
            continue;
        }
        
        // 提取条件内容
        size_t contentStart = conditionEnd + 2;
        std::string conditionalContent = result.substr(contentStart, endPos - contentStart);
        
        // 检查条件是否满足
        auto it = vars.find(conditionName);
        bool condition = (it != vars.end() && !it->second.empty() && it->second != "false");
        
        std::string replacement = condition ? conditionalContent : "";
        
        // 替换整个条件块
        size_t blockEnd = endPos + endTag.length();
        result.replace(startPos, blockEnd - startPos, replacement);
        
        // 更新位置
        pos = startPos + replacement.length();
    }
    
    return result;
}

std::string Generator::processTemplateFunctions(const std::string& content, const TemplateVars& vars) {
    std::string result = content;
    
    // 查找形如 {{VARIABLE | function}} 的模式
    size_t pos = 0;
    while (pos < result.length()) {
        size_t startPos = result.find("{{", pos);
        if (startPos == std::string::npos) break;
        
        size_t endPos = result.find("}}", startPos);
        if (endPos == std::string::npos) break;
        
        std::string expression = result.substr(startPos + 2, endPos - startPos - 2);
        
        // 检查是否包含管道符
        size_t pipePos = expression.find(" | ");
        if (pipePos != std::string::npos) {
            std::string varName = expression.substr(0, pipePos);
            std::string functionName = expression.substr(pipePos + 3);
            
            // 移除空格
            varName.erase(std::remove_if(varName.begin(), varName.end(), ::isspace), varName.end());
            functionName.erase(std::remove_if(functionName.begin(), functionName.end(), ::isspace), functionName.end());
            
            // 获取变量值
            auto varIt = vars.find(varName);
            if (varIt != vars.end()) {
                std::string value = varIt->second;
                std::string processedValue = applyTemplateFunction(value, functionName);
                
                // 替换整个表达式
                std::string fullPlaceholder = "{{" + expression + "}}";
                result.replace(startPos, fullPlaceholder.length(), processedValue);
                pos = startPos + processedValue.length();
                continue;
            }
        }
        
        pos = endPos + 2;
    }
    
    return result;
}

std::string Generator::applyTemplateFunction(const std::string& value, const std::string& function) {
    if (function == "pascal_case") {
        return toPascalCase(value);
    } else if (function == "camel_case") {
        return toCamelCase(value);
    } else if (function == "map_type") {
        return mapTypeFromConfig(value);
    } else if (function == "field_template") {
        return getFieldTemplate(value);
    } else if (function == "type_suffix") {
        return getTypeSuffix(value);
    } else if (function == "interface_name") {
        return getInterfaceName(value);
    }
    
    return value; // 如果函数不存在，返回原值
}

std::string Generator::mapTypeFromConfig(const std::string& motaType) {
    // 处理repeated类型
    if (motaType.substr(0, 9) == "repeated ") {
        std::string elementType = motaType.substr(9);
        std::string mappedElementType = mapTypeFromConfig(elementType); // 递归调用
        return "QVector<" + mappedElementType + ">";
    }
    
    // 检查内置类型映射
    auto it = config_.typeMapping.find(motaType);
    if (it != config_.typeMapping.end()) {
        return it->second;
    }
    
    // 检查是否是已定义的自定义类型
    auto typeIt = typeContext_.find(motaType);
    if (typeIt != typeContext_.end()) {
        return formatTypeNameFromConfig(motaType, typeIt->second);
    }
    
    // 默认作为自定义类型处理
    return formatTypeNameFromConfig(motaType, "block");
}

std::string Generator::formatTypeNameFromConfig(const std::string& name, const std::string& type) {
    // 从配置的模板变量中获取格式化规则
    auto classNameTemplateIt = config_.templateVariables.find("CLASS_NAME");
    if (classNameTemplateIt != config_.templateVariables.end()) {
        TemplateVars vars;
        vars["TYPE_NAME"] = name;
        vars["TYPE_SUFFIX"] = getTypeSuffix(type);
        vars["TYPE"] = type;
        
        return renderTemplate(classNameTemplateIt->second, vars);
    }
    
    // 回退到原来的逻辑
    return formatTypeName(name, type);
}

std::string Generator::getTypeSuffix(const std::string& type) {
    auto suffixIt = config_.identifierFormat.suffix.find(type);
    if (suffixIt != config_.identifierFormat.suffix.end()) {
        return suffixIt->second;
    }
    return "";
}

std::string Generator::getInterfaceName(const std::string& type) {
    auto interfaceIt = config_.typeInterfaceMapping.find(type);
    if (interfaceIt != config_.typeInterfaceMapping.end()) {
        return interfaceIt->second;
    }
    return "IBlock"; // 默认接口
}

std::string Generator::getFieldTemplate(const std::string& motaType) {
    // 处理repeated类型
    if (motaType.substr(0, 9) == "repeated ") {
        std::string elementType = motaType.substr(9);
        
        // 检查元素类型是否为基本类型
        auto basicTypeIt = config_.typeMapping.find(elementType);
        if (basicTypeIt != config_.typeMapping.end()) {
            return "BASIC_ARRAY"; // 基本类型数组
        }
        
        // 自定义类型数组
        return "ARRAY";
    }
    
    // 检查内置类型
    auto templateIt = config_.fieldTypeTemplates.find(motaType);
    if (templateIt != config_.fieldTypeTemplates.end()) {
        return templateIt->second;
    }
    
    // 检查是否是已定义的自定义类型
    auto typeIt = typeContext_.find(motaType);
    if (typeIt != typeContext_.end()) {
        return "COMPLEX";
    }
    
    return "COMPLEX"; // 默认为复合类型
}

TemplateVars Generator::buildTemplateVars(const std::string& typeName, const std::string& typeKind, const std::vector<std::unique_ptr<ast::Field>>& fields) {
    TemplateVars vars;
    
    // 基础类型信息
    vars["TYPE_NAME"] = typeName;
    vars["TYPE_KIND"] = typeKind;
    vars["TYPE_SUFFIX"] = getTypeSuffix(typeKind);
    vars["INTERFACE_NAME"] = getInterfaceName(typeKind);
    vars["CLASS_NAME"] = formatTypeNameFromConfig(typeName, typeKind);
    
    // 根据类型设置特定的名称变量
    if (typeKind == "struct") {
        vars["STRUCT_NAME"] = typeName;
    } else if (typeKind == "block") {
        vars["BLOCK_NAME"] = typeName;
    } else if (typeKind == "annotation") {
        vars["ANNOTATION_NAME"] = typeName;
    } else if (typeKind == "enum") {
        vars["ENUM_NAME"] = typeName;
    }
    
    // 生成字段相关的代码，完全基于模板
    vars["PRIVATE_FIELDS"] = generateFromTemplate("PRIVATE_FIELDS", fields);
    vars["ACCESSORS"] = generateFromTemplate("ACCESSORS", fields);
    vars["CONSTRUCTOR"] = generateFromTemplate("CONSTRUCTOR", fields);
    vars["SERIALIZE_FIELDS"] = generateFromTemplate("SERIALIZE_FIELDS", fields);
    vars["DESERIALIZE_FIELDS"] = generateFromTemplate("DESERIALIZE_FIELDS", fields);
    vars["FIELD_NAMES"] = generateFromTemplate("FIELD_NAMES", fields);
    vars["FIELD_TYPE_LOGIC"] = generateFromTemplate("FIELD_TYPE_LOGIC", fields);
    vars["VALUE_GETTER_LOGIC"] = generateFromTemplate("VALUE_GETTER_LOGIC", fields);
    vars["VALUE_SETTER_LOGIC"] = generateFromTemplate("VALUE_SETTER_LOGIC", fields);
    vars["FIELD_ANNOTATION_LOGIC"] = generateFromTemplate("FIELD_ANNOTATION_LOGIC", fields);
    vars["FIELD_DESCRIPTION_LOGIC"] = generateFromTemplate("FIELD_DESCRIPTION_LOGIC", fields);
    vars["ARGUMENT_GETTER_LOGIC"] = generateFromTemplate("ARGUMENT_GETTER_LOGIC", fields);
    vars["ARGUMENT_NAMES"] = generateFromTemplate("ARGUMENT_NAMES", fields);
    
    // 描述信息
    vars["DESCRIPTION"] = "Generated from " + typeKind + " " + typeName;
    
    // 注解信息（可以根据需要扩展）
    vars["STRUCT_ANNOTATIONS"] = "";
    vars["BLOCK_ANNOTATIONS"] = "";
    vars["ANNOTATION_ANNOTATIONS"] = "";
    
    return vars;
}

std::string Generator::generateFromTemplate(const std::string& templateType, const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 根据模板类型生成不同的代码
    if (templateType == "PRIVATE_FIELDS") {
        return generatePrivateFieldsFromTemplate(fields);
    } else if (templateType == "ACCESSORS") {
        return generateAccessorsFromTemplate(fields);
    } else if (templateType == "SERIALIZE_FIELDS") {
        return generateSerializeFieldsFromTemplate(fields);
    } else if (templateType == "DESERIALIZE_FIELDS") {
        return generateDeserializeFieldsFromTemplate(fields);
    } else if (templateType == "FIELD_NAMES") {
        return generateFieldNamesFromTemplate(fields);
    } else if (templateType == "FIELD_TYPE_LOGIC") {
        return generateFieldTypeLogicFromTemplate(fields);
    } else if (templateType == "VALUE_GETTER_LOGIC") {
        return generateValueGetterLogicFromTemplate(fields);
    } else if (templateType == "VALUE_SETTER_LOGIC") {
        return generateValueSetterLogicFromTemplate(fields);
    } else if (templateType == "ARGUMENT_GETTER_LOGIC") {
        return generateArgumentGetterLogicFromTemplate(fields);
    } else if (templateType == "ARGUMENT_NAMES") {
        return generateArgumentNamesFromTemplate(fields);
    }
    
    // 对于其他类型，回退到原来的实现
    return "";
}

std::string Generator::generatePrivateFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        TemplateVars fieldVars = buildFieldTemplateVars(*field);
        
        // 生成私有字段声明
        if (!result.empty()) result += "\n    ";
        result += fieldVars["FIELD_TYPE_MAPPED"] + " " + fieldVars["PRIVATE_FIELD_NAME"] + ";";
    }
    return result;
}

std::string Generator::generateAccessorsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    auto accessorTemplate = loadTemplate(config_.templates["accessor"]);
    if (accessorTemplate.empty()) {
        return generateAccessors(fields); // 回退到原实现
    }
    
    std::string result;
    for (const auto& field : fields) {
        TemplateVars fieldVars = buildFieldTemplateVars(*field);
        
        if (!result.empty()) result += "\n\n    ";
        result += renderTemplate(accessorTemplate, fieldVars);
    }
    return result;
}

std::string Generator::generateSerializeFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        TemplateVars fieldVars = buildFieldTemplateVars(*field);
        
        // 根据字段类型获取序列化模板
        std::string templateName = fieldVars["SERIALIZE_TEMPLATE"];
        std::string serializeCode = getFieldTypeSerializeCode(templateName, fieldVars);
        
        if (!result.empty()) result += "\n        ";
        result += serializeCode;
    }
    return result;
}

std::string Generator::generateDeserializeFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        TemplateVars fieldVars = buildFieldTemplateVars(*field);
        
        // 根据字段类型获取反序列化模板
        std::string templateName = fieldVars["DESERIALIZE_TEMPLATE"];
        std::string deserializeCode = getFieldTypeDeserializeCode(templateName, fieldVars);
        
        if (!result.empty()) result += "\n        ";
        result += deserializeCode;
    }
    return result;
}

TemplateVars Generator::buildFieldTemplateVars(const ast::Field& field) {
    TemplateVars vars;
    
    vars["FIELD_NAME"] = field.name;
    vars["FIELD_TYPE"] = field.type->toString();
    vars["FIELD_TYPE_MAPPED"] = mapTypeFromConfig(field.type->toString());
    vars["PRIVATE_FIELD_NAME"] = field.name + "_";
    vars["FIELD_NAME_PASCAL"] = toPascalCase(field.name);
    vars["FIELD_NAME_CAMEL"] = toCamelCase(field.name);
    vars["GETTER_NAME"] = config_.accessorFormat.getterPrefix + toPascalCase(field.name);
    vars["SETTER_NAME"] = config_.accessorFormat.setterPrefix + toPascalCase(field.name);
    vars["SERIALIZE_TEMPLATE"] = getFieldTemplate(field.type->toString()) + "_SERIALIZE";
    vars["DESERIALIZE_TEMPLATE"] = getFieldTemplate(field.type->toString()) + "_DESERIALIZE";
    
    // 处理数组类型的元素类型
    if (field.type->toString().substr(0, 9) == "repeated ") {
        std::string elementType = field.type->toString().substr(9);
        vars["ITEM_TYPE"] = mapTypeFromConfig(elementType);
        vars["ELEMENT_TYPE"] = elementType;
        
        // 为基本类型数组生成转换方法
        if (elementType == "int8" || elementType == "int16" || elementType == "int32" || 
            elementType == "int64" || elementType == "uint8" || elementType == "uint16" || 
            elementType == "uint32" || elementType == "uint64") {
            vars["CONVERT_METHOD"] = "Integer";
        } else if (elementType == "float32" || elementType == "float64") {
            vars["CONVERT_METHOD"] = "Double";
        } else if (elementType == "string") {
            vars["CONVERT_METHOD"] = "String";
        } else if (elementType == "bool") {
            vars["CONVERT_METHOD"] = "Bool";
        } else if (elementType == "bytes") {
            vars["CONVERT_METHOD"] = "ByteArray";
        }
    }
    
    return vars;
}

std::string Generator::getFieldTypeSerializeCode(const std::string& templateName, const TemplateVars& fieldVars) {
    // 从field_types.template文件中查找对应的序列化代码
    auto fieldTypesTemplate = loadTemplate(config_.templates["field_types"]);
    return extractTemplateSection(fieldTypesTemplate, templateName, fieldVars);
}

std::string Generator::getFieldTypeDeserializeCode(const std::string& templateName, const TemplateVars& fieldVars) {
    // 从field_types.template文件中查找对应的反序列化代码
    auto fieldTypesTemplate = loadTemplate(config_.templates["field_types"]);
    return extractTemplateSection(fieldTypesTemplate, templateName, fieldVars);
}

std::string Generator::extractTemplateSection(const std::string& templateContent, const std::string& sectionName, const TemplateVars& vars) {
    // 查找 [SECTION_NAME] 标记
    std::string startMarker = "[" + sectionName + "]";
    size_t startPos = templateContent.find(startMarker);
    if (startPos == std::string::npos) {
        return ""; // 未找到对应的模板段
    }
    
    // 跳过标记行
    startPos = templateContent.find('\n', startPos);
    if (startPos == std::string::npos) return "";
    startPos++; // 跳过换行符
    
    // 查找下一个段的开始或文件结束
    size_t endPos = templateContent.find("\n[", startPos);
    if (endPos == std::string::npos) {
        // 如果没有找到下一个段，查找是否有注释行
        size_t commentPos = templateContent.find("\n#", startPos);
        if (commentPos != std::string::npos && (endPos == std::string::npos || commentPos < endPos)) {
            endPos = commentPos;
        } else {
            endPos = templateContent.length();
        }
    }
    
    // 提取模板段内容
    std::string sectionContent = templateContent.substr(startPos, endPos - startPos);
    
    // 移除开头和末尾的空行以及注释
    std::stringstream ss(sectionContent);
    std::string line;
    std::string cleanContent;
    
    while (std::getline(ss, line)) {
        // 跳过注释行和空行
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        if (!cleanContent.empty()) {
            cleanContent += "\n";
        }
        cleanContent += line;
    }
    
    return renderTemplate(cleanContent, vars);
}

std::string Generator::generateFieldNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) result += ", ";
        result += "QLatin1String(\"" + fields[i]->name + "\")";
    }
    return result;
}

std::string Generator::generateFieldTypeLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) return QLatin1String(\"" + field->type->toString() + "\");";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QLatin1String(\"\");";
    return result;
}

std::string Generator::generateValueGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) return QVariant::fromValue(" + field->name + "_);";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QVariant();";
    return result;
}

std::string Generator::generateValueSetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) {\n";
        result += "            " + field->name + "_ = value.value<" + mapTypeFromConfig(field->type->toString()) + ">();\n";
        result += "            return true;\n";
        result += "        }";
    }
    if (!result.empty()) result += "\n        ";
    result += "return false;";
    return result;
}

std::string Generator::generateArgumentGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (argumentName == QLatin1String(\"" + field->name + "\")) return QVariant::fromValue(" + field->name + "_);";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QVariant();";
    return result;
}

std::string Generator::generateArgumentNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) result += ", ";
        result += "QLatin1String(\"" + fields[i]->name + "\")";
    }
    return result;
}

std::string Generator::generate(const ast::Document& document, const std::string& outputPath) {
    return generateFile(document);
}

std::string Generator::generateFile(const ast::Document& document) {
    auto headerIt = config_.templates.find("header");
    if (headerIt == config_.templates.end()) {
        std::cerr << "Header template not found in config" << std::endl;
        return "";
    }
    
    std::string headerTemplate = loadTemplate(headerIt->second);
    if (headerTemplate.empty()) {
        return "";
    }
    
    // 首先建立类型上下文
    buildTypeContext(document);
    
    // 收集所有生成的内容
    std::vector<std::string> contents;
    
    // 遍历文档中的所有声明
    for (const auto& node : document.declarations) {
        switch (node->nodeType()) {
            case ast::NodeType::StructDecl: {
                auto structNode = static_cast<const ast::Struct*>(node.get());
                contents.push_back(generateStruct(*structNode));
                break;
            }
            case ast::NodeType::BlockDecl: {
                auto blockNode = static_cast<const ast::Block*>(node.get());
                contents.push_back(generateBlock(*blockNode));
                break;
            }
            case ast::NodeType::EnumDecl: {
                auto enumNode = static_cast<const ast::Enum*>(node.get());
                contents.push_back(generateEnum(*enumNode));
                break;
            }
            case ast::NodeType::AnnotationDecl: {
                auto annotationNode = static_cast<const ast::AnnotationDecl*>(node.get());
                contents.push_back(generateAnnotation(*annotationNode));
                break;
            }
            default:
                break;
        }
    }
    
    // 准备模板变量
    TemplateVars vars;
    vars["GENERATION_TIME"] = getCurrentTimestamp();
    vars["SOURCE_FILE"] = "unknown.mota";
    
    std::string namespaceStr = extractNamespace(document);
    if (!namespaceStr.empty()) {
        vars["HAS_NAMESPACE"] = "true";
        vars["NAMESPACE"] = namespaceStr;
    } else {
        vars["HAS_NAMESPACE"] = "";
        vars["NAMESPACE"] = "";
    }
    
    // 合并所有内容
    std::string allContent;
    for (const auto& content : contents) {
        if (!allContent.empty()) {
            allContent += "\n\n";
        }
        allContent += content;
    }
    vars["CONTENT"] = allContent;
    
    return renderTemplate(headerTemplate, vars);
}

std::string Generator::generateStruct(const ast::Struct& structNode) {
    auto templateIt = config_.templates.find("struct");
    if (templateIt == config_.templates.end()) {
        std::cerr << "Struct template not found in config" << std::endl;
        return "";
    }
    
    std::string structTemplate = loadTemplate(templateIt->second);
    if (structTemplate.empty()) {
        return "";
    }
    
    TemplateVars vars = buildTemplateVars(structNode.name, "struct", structNode.fields);
    
    return renderTemplate(structTemplate, vars);
}

std::string Generator::generateBlock(const ast::Block& blockNode) {
    auto templateIt = config_.templates.find("block");
    if (templateIt == config_.templates.end()) {
        std::cerr << "Block template not found in config" << std::endl;
        return "";
    }
    
    std::string blockTemplate = loadTemplate(templateIt->second);
    if (blockTemplate.empty()) {
        return "";
    }
    
    TemplateVars vars = buildTemplateVars(blockNode.name, "block", blockNode.fields);
    
    return renderTemplate(blockTemplate, vars);
}

std::string Generator::generateEnum(const ast::Enum& enumNode) {
    auto templateIt = config_.templates.find("enum");
    if (templateIt == config_.templates.end()) {
        std::cerr << "Enum template not found in config" << std::endl;
        return "";
    }
    
    std::string enumTemplate = loadTemplate(templateIt->second);
    if (enumTemplate.empty()) {
        return "";
    }
    
    TemplateVars vars;
    std::string className = formatTypeName(enumNode.name, "enum");
    vars["CLASS_NAME"] = className;
    vars["ENUM_NAME"] = enumNode.name;
    
    // 生成枚举值列表
    std::string enumValues;
    std::string toStringCases;
    std::string fromStringLogic;
    std::string stringValues;
    std::string displayNames;
    
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        const auto& enumValue = enumNode.values[i];
        
        // 枚举值定义
        if (i > 0) {
            enumValues += ",\n    ";
            stringValues += " ";
            displayNames += " ";
        }
        enumValues += enumValue->name + " = " + std::to_string(i);
        
        // toString cases
        if (i > 0) toStringCases += "\n            ";
        toStringCases += "case " + className + "::" + enumValue->name + ":\n";
        toStringCases += "                return \"" + enumValue->name + "\";";
        
        // fromString logic
        if (i > 0) fromStringLogic += " else ";
        fromStringLogic += "if (str == \"" + enumValue->name + "\") {\n";
        fromStringLogic += "            return " + className + "::" + enumValue->name + ";\n";
        fromStringLogic += "        }";
        
        // string values and display names
        stringValues += "<< \"" + enumValue->name + "\"";
        displayNames += "<< \"" + enumValue->name + "\"";
    }
    
    vars["ENUM_VALUES"] = enumValues;
    vars["ENUM_TO_STRING_CASES"] = toStringCases;
    vars["STRING_TO_ENUM_LOGIC"] = fromStringLogic;
    vars["DEFAULT_ENUM_VALUE"] = enumNode.values.empty() ? "" : enumNode.values[0]->name;
    vars["ENUM_STRING_VALUES"] = stringValues;
    vars["ENUM_DISPLAY_NAMES"] = displayNames;
    
    return renderTemplate(enumTemplate, vars);
}

std::string Generator::generateAnnotation(const ast::AnnotationDecl& annotationNode) {
    auto templateIt = config_.templates.find("annotation");
    if (templateIt == config_.templates.end()) {
        std::cerr << "Annotation template not found in config" << std::endl;
        return "";
    }
    
    std::string annotationTemplate = loadTemplate(templateIt->second);
    if (annotationTemplate.empty()) {
        return "";
    }
    
    TemplateVars vars = buildTemplateVars(annotationNode.name, "annotation", annotationNode.fields);
    
    return renderTemplate(annotationTemplate, vars);
}

std::string Generator::generateAccessors(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    auto templateIt = config_.templates.find("accessor");
    if (templateIt == config_.templates.end()) {
        return ""; // 没有模板就不生成
    }
    
    std::string accessorTemplate = loadTemplate(templateIt->second);
    if (accessorTemplate.empty()) {
        return "";
    }
    
    std::string result;
    for (const auto& field : fields) {
        TemplateVars vars = buildFieldTemplateVars(*field);
        
        if (!result.empty()) result += "\n\n    ";
        result += renderTemplate(accessorTemplate, vars);
    }
    
    return result;
}

std::string Generator::generatePrivateFields(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n    ";
        result += mapTypeFromConfig(field->type->toString()) + " " + field->name + "_;";
    }
    return result;
}

std::string Generator::generateConstructor(const std::vector<std::unique_ptr<ast::Field>>& fields, const std::string& className) {
    if (fields.empty()) {
        return ""; // 空构造函数通过默认实现
    }
    
    std::string result = className + "() {\n";
    
    for (const auto& field : fields) {
        result += "        " + field->name + "_ = " + mapTypeFromConfig(field->type->toString()) + "();\n";
    }
    
    result += "    }";
    return result;
}

std::string Generator::generateSerializeFields(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    auto templateIt = config_.templates.find("serialize");
    if (templateIt == config_.templates.end()) {
        // 降级到默认行为
        std::string result;
        for (const auto& field : fields) {
            if (!result.empty()) result += "\n        ";
            result += "map[QLatin1String(\"" + field->name + "\")] = QCborValue::fromVariant(QVariant::fromValue(" + field->name + "_));";
        }
        return result;
    }
    
    std::string serializeTemplate = loadTemplate(templateIt->second);
    if (serializeTemplate.empty()) {
        return "";
    }
    
    std::string result;
    for (const auto& field : fields) {
        TemplateVars vars;
        vars["FIELD_NAME"] = field->name;
        vars["FIELD_TYPE"] = mapType(field->type->toString());
        vars["PRIVATE_FIELD_NAME"] = field->name + "_";
        
        if (!result.empty()) result += "\n";
        result += renderTemplate(serializeTemplate, vars);
    }
    
    return result;
}

std::string Generator::generateDeserializeFields(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    auto templateIt = config_.templates.find("deserialize");
    if (templateIt == config_.templates.end()) {
        // 降级到默认行为
        std::string result;
        for (const auto& field : fields) {
            if (!result.empty()) result += "\n        ";
            result += "if (map.contains(QLatin1String(\"" + field->name + "\"))) {\n";
            result += "            " + field->name + "_ = map[QLatin1String(\"" + field->name + "\")].toVariant().value<" + mapType(field->type->toString()) + ">();\n";
            result += "        }";
        }
        return result;
    }
    
    std::string deserializeTemplate = loadTemplate(templateIt->second);
    if (deserializeTemplate.empty()) {
        return "";
    }
    
    std::string result;
    for (const auto& field : fields) {
        TemplateVars vars;
        vars["FIELD_NAME"] = field->name;
        vars["FIELD_TYPE"] = mapType(field->type->toString());
        vars["PRIVATE_FIELD_NAME"] = field->name + "_";
        
        if (!result.empty()) result += "\n";
        result += renderTemplate(deserializeTemplate, vars);
    }
    
    return result;
}

std::string Generator::generateFieldNames(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) result += ", ";
        result += "QLatin1String(\"" + fields[i]->name + "\")";
    }
    return result;
}

std::string Generator::generateFieldTypeLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) return QLatin1String(\"" + field->type->toString() + "\");";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QLatin1String(\"\");";
    return result;
}

std::string Generator::generateValueGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) return QVariant::fromValue(" + field->name + "_);";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QVariant();";
    return result;
}

std::string Generator::generateValueSetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (fieldName == QLatin1String(\"" + field->name + "\")) {\n";
        result += "            " + field->name + "_ = value.value<" + mapType(field->type->toString()) + ">();\n";
        result += "            return true;\n";
        result += "        }";
    }
    if (!result.empty()) result += "\n        ";
    result += "return false;";
    return result;
}

std::string Generator::generatePropertyTypeLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    return generateFieldTypeLogic(fields);
}

std::string Generator::generatePropertyGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    return generateValueGetterLogic(fields);
}

std::string Generator::generatePropertySetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    return generateValueSetterLogic(fields);
}

std::string Generator::generateArgumentGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        result += "if (argumentName == QLatin1String(\"" + field->name + "\")) return QVariant::fromValue(" + field->name + "_);";
    }
    if (!result.empty()) result += "\n        ";
    result += "return QVariant();";
    return result;
}

std::string Generator::mapType(const std::string& motaType) {
    // 处理repeated类型
    if (motaType.substr(0, 9) == "repeated ") {
        std::string elementType = motaType.substr(9);
        std::string mappedElementType = mapType(elementType); // 递归调用
        return "QVector<" + mappedElementType + ">";
    }
    
    // 检查内置类型映射
    auto it = config_.typeMapping.find(motaType);
    if (it != config_.typeMapping.end()) {
        return it->second;
    }
    
    // 检查是否是已定义的自定义类型
    auto typeIt = typeContext_.find(motaType);
    if (typeIt != typeContext_.end()) {
        return formatTypeName(motaType, typeIt->second);
    }
    
    // 如果找不到，假设是block类型（保持向后兼容）
    return formatTypeName(motaType, "block");
}

std::string Generator::formatTypeName(const std::string& name, const std::string& type) {
    std::string result = name;
    
    // 应用前缀
    auto prefixIt = config_.identifierFormat.prefix.find(type);
    if (prefixIt != config_.identifierFormat.prefix.end()) {
        result = prefixIt->second + result;
    }
    
    // 应用后缀
    auto suffixIt = config_.identifierFormat.suffix.find(type);
    if (suffixIt != config_.identifierFormat.suffix.end()) {
        result = result + suffixIt->second;
    }
    
    // 应用命名风格
    if (config_.identifierFormat.style == "pascal_case") {
        result = toPascalCase(result);
    }
    
    return result;
}

std::string Generator::toPascalCase(const std::string& str) {
    if (str.empty()) return str;
    
    std::string result;
    bool capitalizeNext = true;
    
    for (char c : str) {
        if (c == '_' || c == '-') {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            result += std::toupper(c);
            capitalizeNext = false;
        } else {
            result += c; // 保持原始大小写，不强制转换为小写
        }
    }
    
    return result;
}

std::string Generator::toCamelCase(const std::string& str) {
    std::string pascalCase = toPascalCase(str);
    if (!pascalCase.empty()) {
        pascalCase[0] = std::tolower(pascalCase[0]);
    }
    return pascalCase;
}

std::string Generator::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Generator::extractNamespace(const ast::Document& document) {
    // 查找文档中的命名空间声明
    for (const auto& node : document.declarations) {
        if (node->nodeType() == ast::NodeType::NamespaceDecl) {
            auto namespaceNode = static_cast<const ast::Namespace*>(node.get());
            // 将命名空间的向量名称转换为点分隔的字符串
            std::string result;
            for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
                if (i > 0) result += ".";
                result += namespaceNode->name[i];
            }
            return result;
        }
    }
    return "";
}

std::string Generator::extractFileName(const std::string& filePath) {
    size_t lastSlash = filePath.find_last_of("/\\");
    size_t lastDot = filePath.find_last_of(".");
    
    if (lastSlash == std::string::npos) lastSlash = 0;
    else lastSlash++;
    
    if (lastDot == std::string::npos || lastDot < lastSlash) {
        return filePath.substr(lastSlash);
    }
    
    return filePath.substr(lastSlash, lastDot - lastSlash);
}

} // namespace generator
} // namespace mota 