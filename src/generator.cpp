#include "generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <regex>

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
        
        // 查找匹配的结束引号，考虑转义字符
        size_t pos = quoteStart + 1;
        while (pos < content.length()) {
            if (content[pos] == '\\') {
                pos += 2; // 跳过转义字符
                continue;
            }
            if (content[pos] == '"') {
                break; // 找到结束引号
            }
            pos++;
        }
        
        if (pos >= content.length()) return "";
        
        std::string result = content.substr(quoteStart + 1, pos - quoteStart - 1);
        
        // 处理转义字符
        std::string unescaped;
        for (size_t i = 0; i < result.length(); ++i) {
            if (result[i] == '\\' && i + 1 < result.length()) {
                char nextChar = result[i + 1];
                if (nextChar == '"') {
                    unescaped += '"';
                } else if (nextChar == '\\') {
                    unescaped += '\\';
                } else if (nextChar == 'n') {
                    unescaped += '\n';
                } else if (nextChar == 't') {
                    unescaped += '\t';
                } else if (nextChar == 'r') {
                    unescaped += '\r';
                } else {
                    unescaped += nextChar;
                }
                i++; // 跳过下一个字符
            } else {
                unescaped += result[i];
            }
        }
        
        return unescaped;
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
            
            // 查找匹配的结束引号，考虑转义字符
            size_t valuePos = valueStart + 1;
            while (valuePos < objectContent.length()) {
                if (objectContent[valuePos] == '\\') {
                    valuePos += 2; // 跳过转义字符
                    continue;
                }
                if (objectContent[valuePos] == '"') {
                    break; // 找到结束引号
                }
                valuePos++;
            }
            
            if (valuePos >= objectContent.length()) break;
            
            std::string rawValue = objectContent.substr(valueStart + 1, valuePos - valueStart - 1);
            
            // 处理转义字符
            std::string value;
            for (size_t i = 0; i < rawValue.length(); ++i) {
                if (rawValue[i] == '\\' && i + 1 < rawValue.length()) {
                    char nextChar = rawValue[i + 1];
                    if (nextChar == '"') {
                        value += '"';
                    } else if (nextChar == '\\') {
                        value += '\\';
                    } else if (nextChar == 'n') {
                        value += '\n';
                    } else if (nextChar == 't') {
                        value += '\t';
                    } else if (nextChar == 'r') {
                        value += '\r';
                    } else {
                        value += nextChar;
                    }
                    i++; // 跳过下一个字符
                } else {
                    value += rawValue[i];
                }
            }
            
            result[key] = value;
            
            pos = valuePos + 1;
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
    
    // 解析命名空间格式
    config_.namespaceFormat.separator = extractStringValue("separator");
    config_.namespaceFormat.style = extractStringValue("style");
    
    // 解析继承格式
    config_.inheritanceFormat.singleInheritance = extractStringValue("single_inheritance");
    config_.inheritanceFormat.multipleInheritance = extractStringValue("multiple_inheritance");
    config_.inheritanceFormat.interfaceInheritance = extractStringValue("interface_inheritance");
    config_.inheritanceFormat.combinedInheritance = extractStringValue("combined_inheritance");
    config_.inheritanceFormat.inheritanceKeyword = extractStringValue("inheritance_keyword");
    
    // 解析文件路径配置
    config_.filePath.path = extractStringValue("path");
    config_.filePath.type = extractStringValue("type");
    
    // 解析字段类型模板映射
    config_.fieldTypeTemplates = extractObjectValues("field_type_templates");
    
    // 解析模板变量定义
    config_.templateVariables = extractObjectValues("template_variables");
    std::cerr << "Loaded " << config_.templateVariables.size() << " template variables" << std::endl;
    for (const auto& pair : config_.templateVariables) {
        std::cerr << "  " << pair.first << " = " << pair.second << std::endl;
    }
    
    // 解析类型接口映射
    config_.typeInterfaceMapping = extractObjectValues("type_interface_mapping");
    
    // 解析循环语法配置
    config_.loopSyntax.startTag = extractStringValue("start_tag");
    config_.loopSyntax.endTag = extractStringValue("end_tag");
    config_.loopSyntax.itemVariable = extractStringValue("item_variable");
    config_.loopSyntax.indexVariable = extractStringValue("index_variable");
    
    // 解析语法元素配置
    config_.syntaxElements = extractObjectValues("syntax_elements");
    
    // 解析Include指令配置
    config_.includeDirective.pattern = extractStringValue("include_pattern");
    config_.includeDirective.sourceExtension = extractStringValue("source_extension");
    config_.includeDirective.targetExtension = extractStringValue("target_extension");
    
    // 解析代码生成配置
    config_.codeGeneration.containerTemplate = extractStringValue("container_template");
    config_.codeGeneration.stringLiteralTemplate = extractStringValue("string_literal_template");
    config_.codeGeneration.variantTemplate = extractStringValue("variant_template");
    config_.codeGeneration.collectionSeparator = extractStringValue("collection_separator");
    
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
    
    // 处理循环语句
    result = processLoops(result, vars);
    
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

std::string Generator::processLoops(const std::string& content, const TemplateVars& vars) {
    std::string result = content;
    
    // 从配置获取循环语法标签，需要转义正则表达式特殊字符
    auto escapeRegex = [](const std::string& str) -> std::string {
        std::string result;
        for (char c : str) {
            if (c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']' || 
                c == '.' || c == '*' || c == '+' || c == '?' || c == '^' || c == '$' || 
                c == '|' || c == '\\') {
                result += '\\';
            }
            result += c;
        }
        return result;
    };
    
    std::string startTag = config_.loopSyntax.startTag.empty() ? "\\{\\{#each" : escapeRegex(config_.loopSyntax.startTag);
    std::string endTag = config_.loopSyntax.endTag.empty() ? "\\{\\{/each\\}\\}" : escapeRegex(config_.loopSyntax.endTag);
    
    // 构建动态正则表达式
    std::string regexPattern = startTag + R"(\s+(\w+)\s+as\s+(\w+)(?:\s+with\s+(\w+))?\}\}(.*?))" + endTag;
    std::regex loopRegex(regexPattern);
    std::smatch match;
    
    while (std::regex_search(result, match, loopRegex)) {
        std::string collectionName = match[1].str();
        std::string itemName = match[2].str();
        std::string indexName = match[3].str();
        std::string loopContent = match[4].str();
        
        // 查找集合数据
        auto collectionIt = vars.find(collectionName);
        if (collectionIt != vars.end()) {
            std::string expandedContent = expandLoop(loopContent, collectionIt->second, itemName, indexName);
            result.replace(match.position(), match.length(), expandedContent);
        } else {
            // 如果找不到集合，移除整个循环块
            result.replace(match.position(), match.length(), "");
        }
    }
    
    return result;
}

std::string Generator::expandLoop(const std::string& loopContent, const std::string& collectionData, 
                                 const std::string& itemName, const std::string& indexName) {
    // 从配置获取集合分隔符
    std::string separator = config_.codeGeneration.collectionSeparator.empty() ? "|" : config_.codeGeneration.collectionSeparator;
    char separatorChar = separator.empty() ? '|' : separator[0];
    
    std::vector<std::string> items;
    std::stringstream ss(collectionData);
    std::string item;
    
    while (std::getline(ss, item, separatorChar)) {
        items.push_back(item);
    }
    
    std::string result;
    for (size_t i = 0; i < items.size(); ++i) {
        std::string iterationContent = loopContent;
        
        // 替换项目变量
        std::string itemPlaceholder = "{{" + itemName + "}}";
        size_t pos = 0;
        while ((pos = iterationContent.find(itemPlaceholder, pos)) != std::string::npos) {
            iterationContent.replace(pos, itemPlaceholder.length(), items[i]);
            pos += items[i].length();
        }
        
        // 替换索引变量（如果提供）
        if (!indexName.empty()) {
            std::string indexPlaceholder = "{{" + indexName + "}}";
            pos = 0;
            while ((pos = iterationContent.find(indexPlaceholder, pos)) != std::string::npos) {
                iterationContent.replace(pos, indexPlaceholder.length(), std::to_string(i));
                pos += std::to_string(i).length();
            }
        }
        
        result += iterationContent;
        if (i < items.size() - 1) {
            result += "\n";
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
    } else if (function == "snake_case") {
        return toSnakeCase(value);
    } else if (function == "map_type") {
        return mapTypeFromConfig(value);
    } else if (function == "field_template") {
        return getFieldTemplate(value);
    } else if (function == "type_suffix") {
        return getTypeSuffix(value);
    } else if (function == "interface_name") {
        return getInterfaceName(value);
    } else if (function == "namespace_path") {
        return formatNamespacePath(value);
    } else if (function.substr(0, 4) == "join") {
        // 处理 join 函数，例如 join(', ')
        size_t parenStart = function.find('(');
        size_t parenEnd = function.find(')', parenStart);
        if (parenStart != std::string::npos && parenEnd != std::string::npos) {
            std::string separator = function.substr(parenStart + 1, parenEnd - parenStart - 1);
            // 移除引号
            if (separator.front() == '\'' || separator.front() == '"') {
                separator = separator.substr(1, separator.length() - 2);
            }
            return joinStrings(value, separator);
        }
    }
    
    return value; // 如果函数不存在，返回原值
}

std::string Generator::toSnakeCase(const std::string& str) {
    if (str.empty()) return str;
    
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (std::isupper(c) && i > 0) {
            result += '_';
        }
        result += std::tolower(c);
    }
    
    return result;
}

std::string Generator::formatNamespacePath(const std::string& namespaceStr) {
    if (namespaceStr.empty()) return "";
    
    std::string result = namespaceStr;
    
    // 从配置获取路径分隔符
    auto pathSeparatorIt = config_.syntaxElements.find("NAMESPACE_PATH_SEPARATOR");
    std::string pathSeparator = (pathSeparatorIt != config_.syntaxElements.end()) ? 
        pathSeparatorIt->second : "/";
    
    // 将非数字、英文、下划线的字符替换为路径分隔符
    for (size_t i = 0; i < result.length(); ++i) {
        char c = result[i];
        if (!std::isalnum(c) && c != '_') {
            result[i] = pathSeparator[0];
        }
    }
    
    return result;
}

std::string Generator::joinStrings(const std::string& value, const std::string& separator) {
    // 使用配置的集合分隔符
    std::string collectionSep = config_.codeGeneration.collectionSeparator.empty() ? "|" : config_.codeGeneration.collectionSeparator;
    char collectionSepChar = collectionSep.empty() ? '|' : collectionSep[0];
    
    std::vector<std::string> parts;
    std::stringstream ss(value);
    std::string part;
    
    while (std::getline(ss, part, collectionSepChar)) {
        parts.push_back(part);
    }
    
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += separator;
        result += parts[i];
    }
    
    return result;
}

std::string Generator::mapTypeFromConfig(const std::string& motaType) {
    // 从配置获取repeated关键字
    auto repeatedKeywordIt = config_.syntaxElements.find("REPEATED_KEYWORD");
    std::string repeatedKeyword = (repeatedKeywordIt != config_.syntaxElements.end()) ? 
        repeatedKeywordIt->second : "repeated";
    
    // 处理repeated类型
    std::string repeatedPrefix = repeatedKeyword + " ";
    if (motaType.substr(0, repeatedPrefix.length()) == repeatedPrefix) {
        std::string elementType = motaType.substr(repeatedPrefix.length());
        std::string mappedElementType = mapTypeFromConfig(elementType); // 递归调用
        
        // 从配置获取容器模板
        std::string containerTemplate = config_.codeGeneration.containerTemplate.empty() ? 
            "QVector<{{ELEMENT_TYPE}}>" : config_.codeGeneration.containerTemplate;
        
        TemplateVars containerVars;
        containerVars["ELEMENT_TYPE"] = mappedElementType;
        return renderTemplate(containerTemplate, containerVars);
    }
    
    // 检查内置类型映射
    auto it = config_.typeMapping.find(motaType);
    if (it != config_.typeMapping.end()) {
        return it->second;
    }
    
    // 检查是否是已定义的自定义类型
    auto typeIt = typeContext_.find(motaType);
    if (typeIt != typeContext_.end()) {
        std::string typeName = formatTypeNameFromConfig(motaType, typeIt->second);
        // 如果是注解类型，需要用智能指针包装
        if (typeIt->second == "annotation") {
            return "QSharedPointer<" + typeName + ">";
        }
        return typeName;
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
        if (typeIt->second == "enum") {
            return "ENUM"; // 枚举类型
        }
        return "COMPLEX"; // 其他复合类型
    }
    
    return "COMPLEX"; // 默认为复合类型
}

TemplateVars Generator::buildTemplateVars(const std::string& typeName, const std::string& typeKind, 
                                         const std::vector<std::unique_ptr<ast::Field>>& fields,
                                         const std::string& baseName) {
    TemplateVars vars;
    
    // 基础类型信息
    vars["TYPE_NAME"] = typeName;
    vars["TYPE_KIND"] = typeKind;
    vars["TYPE_SUFFIX"] = getTypeSuffix(typeKind);
    vars["INTERFACE_NAME"] = getInterfaceName(typeKind);
    vars["CLASS_NAME"] = formatTypeNameFromConfig(typeName, typeKind);
    
    // 继承信息
    if (!baseName.empty()) {
        vars["HAS_BASE_CLASS"] = "true";
        vars["BASE_CLASS"] = formatTypeNameFromConfig(baseName, getTypeKind(baseName));
        vars["BASE_CLASSES"] = vars["BASE_CLASS"]; // 单继承情况
        
        // 构建完整的继承声明
        std::string inheritanceDecl = config_.inheritanceFormat.inheritanceKeyword + " " + vars["BASE_CLASS"];
        
        // 添加接口
        std::string interfaceName = getInterfaceName(typeKind);
        if (!interfaceName.empty()) {
            vars["HAS_INTERFACES"] = "true";
            vars["INTERFACES"] = interfaceName;
            inheritanceDecl += ", " + config_.inheritanceFormat.inheritanceKeyword + " " + interfaceName;
        }
        
        vars["INHERITANCE_DECLARATION"] = inheritanceDecl;
    } else {
        vars["HAS_BASE_CLASS"] = "";
        vars["BASE_CLASS"] = "";
        vars["BASE_CLASSES"] = "";
        
        // 只有接口继承
        std::string interfaceName = getInterfaceName(typeKind);
        if (!interfaceName.empty()) {
            vars["HAS_INTERFACES"] = "true";
            vars["INTERFACES"] = interfaceName;
            vars["INHERITANCE_DECLARATION"] = config_.inheritanceFormat.inheritanceKeyword + " " + interfaceName;
        } else {
            vars["HAS_INTERFACES"] = "";
            vars["INTERFACES"] = "";
            vars["INHERITANCE_DECLARATION"] = "";
        }
    }
    
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
    
    // 添加模型和块注解逻辑 - 从模板变量获取或留空
    auto modelAnnotationIt = config_.templateVariables.find("MODEL_ANNOTATION_LOGIC");
    vars["MODEL_ANNOTATION_LOGIC"] = (modelAnnotationIt != config_.templateVariables.end()) ? 
        renderTemplate(modelAnnotationIt->second, vars) : "";
    
    auto blockAnnotationIt = config_.templateVariables.find("BLOCK_ANNOTATION_LOGIC");
    vars["BLOCK_ANNOTATION_LOGIC"] = (blockAnnotationIt != config_.templateVariables.end()) ? 
        renderTemplate(blockAnnotationIt->second, vars) : "";
    
    // 为循环语法准备字段数据
    std::string fieldsData;
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) fieldsData += "|";
        fieldsData += fields[i]->name;
    }
    vars["FIELDS"] = fieldsData;
    
    // 描述信息
    vars["DESCRIPTION"] = "Generated from " + typeKind + " " + typeName;
    
    // 注解信息（可以根据需要扩展）
    vars["STRUCT_ANNOTATIONS"] = "";
    vars["BLOCK_ANNOTATIONS"] = "";
    vars["ANNOTATION_ANNOTATIONS"] = "";
    
    return vars;
}

std::string Generator::getTypeKind(const std::string& typeName) {
    auto it = typeContext_.find(typeName);
    if (it != typeContext_.end()) {
        return it->second;
    }
    return "block"; // 默认类型
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
    } else if (templateType == "FIELD_ANNOTATION_LOGIC") {
        return generateFieldAnnotationLogicFromTemplate(fields);
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
    auto privateFieldTemplateIt = config_.templateVariables.find("PRIVATE_FIELD_DECLARATION");
    std::string privateFieldTemplate;
    if (privateFieldTemplateIt != config_.templateVariables.end()) {
        privateFieldTemplate = privateFieldTemplateIt->second;
    } else {
        // 硬编码的回退模板，支持默认值
        privateFieldTemplate = "{{FIELD_TYPE_MAPPED}} {{PRIVATE_FIELD_NAME}}{{#HAS_DEFAULT_VALUE}} = {{DEFAULT_VALUE}}{{/HAS_DEFAULT_VALUE}};";
    }
    
    for (const auto& field : fields) {
        TemplateVars fieldVars = buildFieldTemplateVars(*field);
        
        // 生成私有字段声明
        if (!result.empty()) result += "\n    ";
        std::string renderedField = renderTemplate(privateFieldTemplate, fieldVars);
        std::cerr << "Private field template: " << privateFieldTemplate << std::endl;
        std::cerr << "Rendered field: " << renderedField << std::endl;
        result += renderedField;
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
    
    // 基础字段信息
    vars["FIELD_NAME"] = field.name;
    vars["FIELD_TYPE"] = field.type->toString();
    vars["FIELD_TYPE_MAPPED"] = mapTypeFromConfig(field.type->toString());
    
    // 处理默认值
    if (field.defaultValue) {
        vars["HAS_DEFAULT_VALUE"] = "true";
        vars["DEFAULT_VALUE"] = generateDefaultValue(*field.defaultValue, field.type->toString());
        std::cerr << "Field " << field.name << " has default value: " << vars["DEFAULT_VALUE"] << std::endl;
    } else {
        vars["HAS_DEFAULT_VALUE"] = "";
        vars["DEFAULT_VALUE"] = "";
        std::cerr << "Field " << field.name << " has no default value" << std::endl;
    }
    
    // 使用配置的模板变量来生成字段相关的变量
    for (const auto& templateVar : config_.templateVariables) {
        if (templateVar.first.find("FIELD_") == 0 || templateVar.first.find("PRIVATE_") == 0) {
            // 为字段相关的模板变量创建临时变量集合
            TemplateVars tempVars = vars;
            tempVars["FIELD_NAME"] = field.name;
            tempVars["FIELD_TYPE"] = field.type->toString();
            
            // 渲染模板变量
            vars[templateVar.first] = renderTemplate(templateVar.second, tempVars);
        }
    }
    
    // 如果配置中没有定义，则使用默认值
    if (vars.find("PRIVATE_FIELD_NAME") == vars.end()) {
        auto privateFieldSuffixIt = config_.syntaxElements.find("PRIVATE_FIELD_SUFFIX");
        std::string privateFieldSuffix = (privateFieldSuffixIt != config_.syntaxElements.end()) ? 
            privateFieldSuffixIt->second : "_";
        vars["PRIVATE_FIELD_NAME"] = field.name + privateFieldSuffix;
    }
    if (vars.find("FIELD_NAME_PASCAL") == vars.end()) {
        vars["FIELD_NAME_PASCAL"] = toPascalCase(field.name);
    }
    if (vars.find("FIELD_NAME_CAMEL") == vars.end()) {
        vars["FIELD_NAME_CAMEL"] = toCamelCase(field.name);
    }
    
    // 生成访问器名称
    std::string getterName = config_.accessorFormat.getterPrefix;
    std::string setterName = config_.accessorFormat.setterPrefix;
    if (config_.accessorFormat.pascalCase) {
        getterName += toPascalCase(field.name);
        setterName += toPascalCase(field.name);
    } else {
        getterName += field.name;
        setterName += field.name;
    }
    vars["GETTER_NAME"] = getterName;
    vars["SETTER_NAME"] = setterName;
    
    // 生成序列化模板名称
    vars["SERIALIZE_TEMPLATE"] = getFieldTemplate(field.type->toString()) + "_SERIALIZE";
    vars["DESERIALIZE_TEMPLATE"] = getFieldTemplate(field.type->toString()) + "_DESERIALIZE";
    
    // 处理数组类型的元素类型
    if (field.type->toString().substr(0, 9) == "repeated ") {
        std::string elementType = field.type->toString().substr(9);
        vars["ITEM_TYPE"] = mapTypeFromConfig(elementType);
        vars["ELEMENT_TYPE"] = elementType;
        
        // 根据类型映射生成转换方法
        auto mappedType = mapTypeFromConfig(elementType);
        
        // 从配置获取类型转换映射
        auto typeConversionIt = config_.syntaxElements.find("TYPE_CONVERSION_" + mappedType);
        if (typeConversionIt != config_.syntaxElements.end()) {
            vars["CONVERT_METHOD"] = typeConversionIt->second;
        } else {
            // 回退到基于模式匹配的转换方法
            auto intPatternIt = config_.syntaxElements.find("INT_TYPE_PATTERN");
            auto floatPatternIt = config_.syntaxElements.find("FLOAT_TYPE_PATTERN");
            auto stringPatternIt = config_.syntaxElements.find("STRING_TYPE_PATTERN");
            auto boolPatternIt = config_.syntaxElements.find("BOOL_TYPE_PATTERN");
            auto byteArrayPatternIt = config_.syntaxElements.find("BYTE_ARRAY_TYPE_PATTERN");
            
            if (intPatternIt != config_.syntaxElements.end() && mappedType.find(intPatternIt->second) != std::string::npos) {
                vars["CONVERT_METHOD"] = config_.syntaxElements["INT_CONVERT_METHOD"];
            } else if (floatPatternIt != config_.syntaxElements.end() && mappedType.find(floatPatternIt->second) != std::string::npos) {
                vars["CONVERT_METHOD"] = config_.syntaxElements["FLOAT_CONVERT_METHOD"];
            } else if (stringPatternIt != config_.syntaxElements.end() && mappedType.find(stringPatternIt->second) != std::string::npos) {
                vars["CONVERT_METHOD"] = config_.syntaxElements["STRING_CONVERT_METHOD"];
            } else if (boolPatternIt != config_.syntaxElements.end() && mappedType.find(boolPatternIt->second) != std::string::npos) {
                vars["CONVERT_METHOD"] = config_.syntaxElements["BOOL_CONVERT_METHOD"];
            } else if (byteArrayPatternIt != config_.syntaxElements.end() && mappedType.find(byteArrayPatternIt->second) != std::string::npos) {
                vars["CONVERT_METHOD"] = config_.syntaxElements["BYTE_ARRAY_CONVERT_METHOD"];
            } else {
                auto defaultConvertIt = config_.syntaxElements.find("DEFAULT_CONVERT_METHOD");
                vars["CONVERT_METHOD"] = (defaultConvertIt != config_.syntaxElements.end()) ? 
                    defaultConvertIt->second : "Variant";
            }
        }
    }
    
    return vars;
}

std::string Generator::generateDefaultValue(const ast::Expr& expr, const std::string& fieldType) {
    switch (expr.nodeType()) {
        case ast::NodeType::Literal: {
            auto& literal = static_cast<const ast::Literal&>(expr);
            if (std::holds_alternative<std::string>(literal.value)) {
                return "\"" + std::get<std::string>(literal.value) + "\"";
            } else if (std::holds_alternative<int64_t>(literal.value)) {
                return std::to_string(std::get<int64_t>(literal.value));
            } else if (std::holds_alternative<double>(literal.value)) {
                return std::to_string(std::get<double>(literal.value));
            } else if (std::holds_alternative<bool>(literal.value)) {
                return std::get<bool>(literal.value) ? "true" : "false";
            }
            break;
        }
        case ast::NodeType::ArrayLiteral: {
            auto& arrayLiteral = static_cast<const ast::ArrayLiteral&>(expr);
            std::string result = "{";
            for (size_t i = 0; i < arrayLiteral.elements.size(); ++i) {
                if (i > 0) result += ", ";
                result += generateDefaultValue(*arrayLiteral.elements[i], fieldType);
            }
            result += "}";
            return result;
        }
        case ast::NodeType::Annotation: {
            auto& annotation = static_cast<const ast::Annotation&>(expr);
            // 对于注解默认值，生成构造函数调用
            std::string result = "QSharedPointer<" + formatTypeNameFromConfig(annotation.name, "annotation") + ">::create(";
            // 这里可以添加注解参数的处理
            result += ")";
            return result;
        }
        case ast::NodeType::Identifier: {
            auto& identifier = static_cast<const ast::Identifier&>(expr);
            // 对于标识符，可能是枚举值
            return identifier.name;
        }
        default:
            break;
    }
    return "";
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
            cleanContent += "\n        "; // 添加适当的缩进
        }
        cleanContent += line;
    }
    
    return renderTemplate(cleanContent, vars);
}

std::string Generator::generateFieldNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    for (size_t i = 0; i < fields.size(); ++i) {
        if (i > 0) result += ", ";
        
        TemplateVars stringVars;
        stringVars["STRING_VALUE"] = fields[i]->name;
        result += renderTemplate(stringTemplate, stringVars);
    }
    return result;
}

std::string Generator::generateFieldTypeLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        
        TemplateVars fieldNameVars;
        fieldNameVars["STRING_VALUE"] = field->name;
        std::string fieldNameStr = renderTemplate(stringTemplate, fieldNameVars);
        
        TemplateVars fieldTypeVars;
        fieldTypeVars["STRING_VALUE"] = field->type->toString();
        std::string fieldTypeStr = renderTemplate(stringTemplate, fieldTypeVars);
        
        result += "if (fieldName == " + fieldNameStr + ") return " + fieldTypeStr + ";";
    }
    if (!result.empty()) result += "\n        ";
    
    TemplateVars emptyVars;
    emptyVars["STRING_VALUE"] = "";
    result += "return " + renderTemplate(stringTemplate, emptyVars) + ";";
    return result;
}

std::string Generator::generateValueGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    std::string variantTemplate = config_.codeGeneration.variantTemplate.empty() ? 
        "QVariant::fromValue({{VALUE}})" : config_.codeGeneration.variantTemplate;
    
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        
        TemplateVars fieldNameVars;
        fieldNameVars["STRING_VALUE"] = field->name;
        std::string fieldNameStr = renderTemplate(stringTemplate, fieldNameVars);
        
        TemplateVars variantVars;
        variantVars["VALUE"] = field->name + "_";
        std::string variantStr = renderTemplate(variantTemplate, variantVars);
        
        result += "if (fieldName == " + fieldNameStr + ") return " + variantStr + ";";
    }
    if (!result.empty()) result += "\n        ";
    
    // 从语法元素配置获取空变体表示
    auto emptyVariantIt = config_.syntaxElements.find("EMPTY_VARIANT");
    std::string emptyVariant = (emptyVariantIt != config_.syntaxElements.end()) ? 
        emptyVariantIt->second : "QVariant()";
    result += "return " + emptyVariant + ";";
    return result;
}

std::string Generator::generateValueSetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    auto privateFieldSuffixIt = config_.syntaxElements.find("PRIVATE_FIELD_SUFFIX");
    std::string privateFieldSuffix = (privateFieldSuffixIt != config_.syntaxElements.end()) ? 
        privateFieldSuffixIt->second : "_";
    
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        
        TemplateVars fieldNameVars;
        fieldNameVars["STRING_VALUE"] = field->name;
        std::string fieldNameStr = renderTemplate(stringTemplate, fieldNameVars);
        
        result += "if (fieldName == " + fieldNameStr + ") {\n";
        result += "            " + field->name + privateFieldSuffix + " = value.value<" + mapTypeFromConfig(field->type->toString()) + ">();\n";
        result += "            return;\n";
        result += "        }";
    }
    return result;
}

std::string Generator::generateFieldAnnotationLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    // 从配置获取字段名变量
    auto fieldNameVarIt = config_.syntaxElements.find("FIELD_NAME_VARIABLE");
    std::string fieldNameVar = (fieldNameVarIt != config_.syntaxElements.end()) ? 
        fieldNameVarIt->second : "fieldName";
    
    // 从配置获取条件语句模板
    auto fieldConditionTemplateIt = config_.templateVariables.find("FIELD_CONDITION_TEMPLATE");
    std::string fieldConditionTemplate = (fieldConditionTemplateIt != config_.templateVariables.end()) ? 
        fieldConditionTemplateIt->second : "if ({{FIELD_NAME_VAR}} == {{FIELD_NAME_STR}}) {\n            {{FIELD_LOGIC}}\n        }";
    
    std::string result;
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        
        TemplateVars fieldNameVars;
        fieldNameVars["STRING_VALUE"] = field->name;
        std::string fieldNameStr = renderTemplate(stringTemplate, fieldNameVars);
        
        // 生成字段注解实例逻辑
        std::string fieldLogic;
        if (!field->annotations.empty()) {
            std::cout << "Generating annotation instances for field: " << field->name << ", annotations count: " << field->annotations.size() << std::endl;
            
            fieldLogic = generateAnnotationInstancesLogic(field->annotations);
            std::cout << "Generated annotation instances: " << fieldLogic << std::endl;
        } else {
            std::cout << "Generating annotation instances for field: " << field->name << ", annotations count: 0" << std::endl;
            fieldLogic = "\n            return QList<QSharedPointer<void>>();";
        }
        
        TemplateVars conditionVars;
        conditionVars["FIELD_NAME_VAR"] = fieldNameVar;
        conditionVars["FIELD_NAME_STR"] = fieldNameStr;
        conditionVars["FIELD_LOGIC"] = fieldLogic;
        
        std::string conditionResult = renderTemplate(fieldConditionTemplate, conditionVars);
        std::cout << "Generated field annotation logic: " << conditionResult << std::endl;
        result += conditionResult;
    }
    return result;
}

std::string Generator::generateArgumentGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    std::string result;
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    std::string variantTemplate = config_.codeGeneration.variantTemplate.empty() ? 
        "QVariant::fromValue({{VALUE}})" : config_.codeGeneration.variantTemplate;
    auto privateFieldSuffixIt = config_.syntaxElements.find("PRIVATE_FIELD_SUFFIX");
    std::string privateFieldSuffix = (privateFieldSuffixIt != config_.syntaxElements.end()) ? 
        privateFieldSuffixIt->second : "_";
    
    // 从配置获取参数名变量
    auto argumentNameVarIt = config_.syntaxElements.find("ARGUMENT_NAME_VARIABLE");
    std::string argumentNameVar = (argumentNameVarIt != config_.syntaxElements.end()) ? 
        argumentNameVarIt->second : "argumentName";
    
    // 从配置获取条件语句模板
    auto conditionTemplateIt = config_.templateVariables.find("ARGUMENT_CONDITION_TEMPLATE");
    std::string conditionTemplate = (conditionTemplateIt != config_.templateVariables.end()) ? 
        conditionTemplateIt->second : "if ({{ARGUMENT_NAME_VAR}} == {{FIELD_NAME_STR}}) return {{VARIANT_STR}};";
    
    for (const auto& field : fields) {
        if (!result.empty()) result += "\n        ";
        
        TemplateVars fieldNameVars;
        fieldNameVars["STRING_VALUE"] = field->name;
        std::string fieldNameStr = renderTemplate(stringTemplate, fieldNameVars);
        
        TemplateVars variantVars;
        variantVars["VALUE"] = field->name + privateFieldSuffix;
        std::string variantStr = renderTemplate(variantTemplate, variantVars);
        
        TemplateVars conditionVars;
        conditionVars["ARGUMENT_NAME_VAR"] = argumentNameVar;
        conditionVars["FIELD_NAME_STR"] = fieldNameStr;
        conditionVars["VARIANT_STR"] = variantStr;
        
        result += renderTemplate(conditionTemplate, conditionVars);
    }
    if (!result.empty()) result += "\n        ";
    
    auto emptyVariantIt = config_.syntaxElements.find("EMPTY_VARIANT");
    std::string emptyVariant = (emptyVariantIt != config_.syntaxElements.end()) ? 
        emptyVariantIt->second : "QVariant()";
    
    auto returnTemplateIt = config_.templateVariables.find("RETURN_TEMPLATE");
    std::string returnTemplate = (returnTemplateIt != config_.templateVariables.end()) ? 
        returnTemplateIt->second : "return {{VALUE}};";
    
    TemplateVars returnVars;
    returnVars["VALUE"] = emptyVariant;
    result += renderTemplate(returnTemplate, returnVars);
    
    return result;
}

std::string Generator::generateArgumentNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 使用与generateFieldNamesFromTemplate相同的逻辑
    return generateFieldNamesFromTemplate(fields);
}

std::string Generator::generate(const ast::Document& document, const std::string& outputPath) {
    return generateFile(document);
}

std::string Generator::generateFile(const ast::Document& document, const std::string& sourceFileName) {
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
    std::vector<std::string> includes;
    
    // 遍历文档中的所有声明
    for (const auto& node : document.declarations) {
        switch (node->nodeType()) {
            case ast::NodeType::IncludeDecl: {
                auto includeNode = static_cast<const ast::Include*>(node.get());
                
                // 使用配置的include指令处理
                std::string includePath = includeNode->path;
                std::string sourceExt = config_.includeDirective.sourceExtension.empty() ? ".mota" : config_.includeDirective.sourceExtension;
                std::string targetExt = config_.includeDirective.targetExtension.empty() ? ".h" : config_.includeDirective.targetExtension;
                
                if (includePath.ends_with(sourceExt)) {
                    includePath = includePath.substr(0, includePath.length() - sourceExt.length()) + targetExt;
                }
                
                // 使用配置的include模式
                std::string includePattern = config_.includeDirective.pattern.empty() ? 
                    "#include \"{{INCLUDE_PATH}}\"" : config_.includeDirective.pattern;
                
                TemplateVars includeVars;
                includeVars["INCLUDE_PATH"] = includePath;
                includes.push_back(renderTemplate(includePattern, includeVars));
                break;
            }
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
    std::cerr << "Source file name: '" << sourceFileName << "'" << std::endl;
    
    // 处理源文件名：只保留文件名，不包含路径信息，避免泄露开发者文件结构
    std::string sourceFileDisplay;
    if (sourceFileName.empty()) {
        sourceFileDisplay = "unknown.mota";
    } else {
        // 只使用文件名部分，不包含路径
        std::string fileName = extractFileName(sourceFileName);
        sourceFileDisplay = fileName + ".mota";
    }
    vars["SOURCE_FILE"] = sourceFileDisplay;
    
    std::string namespaceStr = extractNamespace(document);
    if (!namespaceStr.empty()) {
        vars["HAS_NAMESPACE"] = "true";
        
        // 使用配置的命名空间格式化
        std::string formattedNamespace = namespaceStr;
        
        // 从配置获取命名空间分隔符替换规则
        auto namespaceSeparatorIt = config_.syntaxElements.find("NAMESPACE_SEPARATOR_REPLACEMENT");
        if (namespaceSeparatorIt != config_.syntaxElements.end()) {
            // 使用配置的替换规则
            std::string replacementRule = namespaceSeparatorIt->second;
            // 格式: "source_char->target_string"
            size_t arrowPos = replacementRule.find("->");
            if (arrowPos != std::string::npos) {
                std::string sourceChar = replacementRule.substr(0, arrowPos);
                std::string targetString = replacementRule.substr(arrowPos + 2);
                
                // 替换所有源字符
                size_t pos = 0;
                while ((pos = formattedNamespace.find(sourceChar, pos)) != std::string::npos) {
                    formattedNamespace.replace(pos, sourceChar.length(), targetString);
                    pos += targetString.length();
                }
            }
        } else {
            // 回退到原来的逻辑：将点替换为双冒号
            std::string separator = config_.namespaceFormat.separator.empty() ? "::" : config_.namespaceFormat.separator;
            size_t pos = 0;
            while ((pos = formattedNamespace.find(".", pos)) != std::string::npos) {
                formattedNamespace.replace(pos, 1, separator);
                pos += separator.length();
            }
        }
        
        vars["NAMESPACE"] = formattedNamespace;
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
    
    // 处理include信息
    if (!includes.empty()) {
        vars["HAS_INCLUDES"] = "true";
        std::string allIncludes;
        for (const auto& include : includes) {
            if (!allIncludes.empty()) {
                allIncludes += "\n";
            }
            allIncludes += include;
        }
        vars["INCLUDES"] = allIncludes;
    } else {
        vars["HAS_INCLUDES"] = "";
        vars["INCLUDES"] = "";
    }
    
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
    
    TemplateVars vars = buildTemplateVars(structNode.name, "struct", structNode.fields, structNode.baseName);
    
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
    
    TemplateVars vars = buildTemplateVars(blockNode.name, "block", blockNode.fields, blockNode.baseName);
    
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
    
    // 构建枚举的模板变量
    TemplateVars vars = buildEnumTemplateVars(enumNode);
    
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
    // 使用基于模板的方法
    return generatePrivateFieldsFromTemplate(fields);
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
        // 使用基于模板的方法
        return generateSerializeFieldsFromTemplate(fields);
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
        // 使用基于模板的方法
        return generateDeserializeFieldsFromTemplate(fields);
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
    // 使用新的基于模板的方法
    return generateFieldNamesFromTemplate(fields);
}

std::string Generator::generateFieldTypeLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 使用新的基于模板的方法
    return generateFieldTypeLogicFromTemplate(fields);
}

std::string Generator::generateValueGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 使用新的基于模板的方法
    return generateValueGetterLogicFromTemplate(fields);
}

std::string Generator::generateValueSetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 使用新的基于模板的方法
    return generateValueSetterLogicFromTemplate(fields);
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
    // 使用新的基于模板的方法
    return generateArgumentGetterLogicFromTemplate(fields);
}

std::string Generator::mapType(const std::string& motaType) {
    // 使用新的基于配置的方法
    return mapTypeFromConfig(motaType);
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
    // 检查文档的命名空间字段
    if (document.m_namespace) {
        // 将命名空间的向量名称转换为点分隔的字符串
        std::string result;
        for (size_t i = 0; i < document.m_namespace->name.size(); ++i) {
            if (i > 0) result += ".";
            result += document.m_namespace->name[i];
        }
        return result;
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

TemplateVars Generator::buildEnumTemplateVars(const ast::Enum& enumNode) {
    TemplateVars vars;
    
    // 基础信息
    std::string className = formatTypeName(enumNode.name, "enum");
    vars["CLASS_NAME"] = className;
    vars["ENUM_NAME"] = enumNode.name;
    
    // 构建枚举值数据
    std::string enumValuesData;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) enumValuesData += "|";
        enumValuesData += enumNode.values[i]->name;
    }
    vars["ENUM_VALUES_DATA"] = enumValuesData;
    
    // 使用模板生成各个部分
    vars["ENUM_VALUES"] = generateEnumValuesFromTemplate(enumNode);
    vars["ENUM_TO_STRING_CASES"] = generateEnumToStringCasesFromTemplate(enumNode, className);
    vars["STRING_TO_ENUM_LOGIC"] = generateStringToEnumLogicFromTemplate(enumNode, className);
    vars["ENUM_STRING_VALUES"] = generateEnumStringValuesFromTemplate(enumNode);
    vars["ENUM_DISPLAY_NAMES"] = generateEnumDisplayNamesFromTemplate(enumNode);
    vars["ENUM_ANNOTATION_LOGIC"] = generateEnumAnnotationLogicFromTemplate(enumNode);
    vars["ENUM_VALUE_ANNOTATION_CASES"] = generateEnumValueAnnotationCasesFromTemplate(enumNode, className);
    vars["ENUM_VALUE_ANNOTATION_BY_NAME_LOGIC"] = generateEnumValueAnnotationByNameLogicFromTemplate(enumNode);
    
    // 默认值
    vars["DEFAULT_ENUM_VALUE"] = enumNode.values.empty() ? "" : enumNode.values[0]->name;
    
    return vars;
}

std::string Generator::generateEnumValuesFromTemplate(const ast::Enum& enumNode) {
    auto enumValueTemplateIt = config_.templateVariables.find("ENUM_VALUE_TEMPLATE");
    std::string enumValueTemplate = (enumValueTemplateIt != config_.templateVariables.end()) ? 
        enumValueTemplateIt->second : "{{ENUM_VALUE_NAME}} = {{ENUM_VALUE_INDEX}}";
    
    auto enumValueSeparatorIt = config_.syntaxElements.find("ENUM_VALUE_SEPARATOR");
    std::string enumValueSeparator = (enumValueSeparatorIt != config_.syntaxElements.end()) ? 
        enumValueSeparatorIt->second : ",\n    ";
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += enumValueSeparator;
        
        TemplateVars enumValueVars;
        enumValueVars["ENUM_VALUE_NAME"] = enumNode.values[i]->name;
        
        // 使用枚举的实际值，如果没有指定值则使用索引
        if (enumNode.values[i]->value) {
            // 获取枚举值的字面量
            if (enumNode.values[i]->value->nodeType() == ast::NodeType::Literal) {
                auto literal = static_cast<const ast::Literal*>(enumNode.values[i]->value.get());
                if (std::holds_alternative<int64_t>(literal->value)) {
                    int64_t actualValue = std::get<int64_t>(literal->value);
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(actualValue);
                } else if (std::holds_alternative<double>(literal->value)) {
                    double actualValue = std::get<double>(literal->value);
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(static_cast<int>(actualValue));
                } else if (std::holds_alternative<std::string>(literal->value)) {
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
                } else if (std::holds_alternative<bool>(literal->value)) {
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
                } else {
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
                }
            } else if (enumNode.values[i]->value->nodeType() == ast::NodeType::UnaryOp) {
                // 处理一元操作符（如负数）
                auto unaryOp = static_cast<const ast::UnaryOp*>(enumNode.values[i]->value.get());
                if (unaryOp->op == ast::UnaryOp::Op::Minus && unaryOp->operand && 
                    unaryOp->operand->nodeType() == ast::NodeType::Literal) {
                    auto literal = static_cast<const ast::Literal*>(unaryOp->operand.get());
                    if (std::holds_alternative<int64_t>(literal->value)) {
                        int64_t actualValue = -std::get<int64_t>(literal->value);
                        enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(actualValue);
                    } else if (std::holds_alternative<double>(literal->value)) {
                        double actualValue = -std::get<double>(literal->value);
                        enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(static_cast<int>(actualValue));
                    } else {
                        enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
                    }
                } else {
                    enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
                }
            } else {
                enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
            }
        } else {
            enumValueVars["ENUM_VALUE_INDEX"] = std::to_string(i);
        }
        
        result += renderTemplate(enumValueTemplate, enumValueVars);
    }
    return result;
}

std::string Generator::generateEnumToStringCasesFromTemplate(const ast::Enum& enumNode, const std::string& className) {
    auto caseTemplateIt = config_.templateVariables.find("ENUM_TO_STRING_CASE_TEMPLATE");
    std::string caseTemplate = (caseTemplateIt != config_.templateVariables.end()) ? 
        caseTemplateIt->second : "case {{CLASS_NAME}}::{{ENUM_VALUE_NAME}}:\n                return {{STRING_LITERAL}};";
    
    auto caseSeparatorIt = config_.syntaxElements.find("ENUM_CASE_SEPARATOR");
    std::string caseSeparator = (caseSeparatorIt != config_.syntaxElements.end()) ? 
        caseSeparatorIt->second : "\n            ";
    
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += caseSeparator;
        
        TemplateVars stringVars;
        stringVars["STRING_VALUE"] = enumNode.values[i]->name;
        std::string stringLiteral = renderTemplate(stringTemplate, stringVars);
        
        TemplateVars caseVars;
        caseVars["CLASS_NAME"] = className;
        caseVars["ENUM_VALUE_NAME"] = enumNode.values[i]->name;
        caseVars["STRING_LITERAL"] = stringLiteral;
        
        result += renderTemplate(caseTemplate, caseVars);
    }
    return result;
}

std::string Generator::generateStringToEnumLogicFromTemplate(const ast::Enum& enumNode, const std::string& className) {
    auto conditionTemplateIt = config_.templateVariables.find("STRING_TO_ENUM_CONDITION_TEMPLATE");
    std::string conditionTemplate = (conditionTemplateIt != config_.templateVariables.end()) ? 
        conditionTemplateIt->second : "if (str == {{STRING_LITERAL}}) {\n            return {{CLASS_NAME}}::{{ENUM_VALUE_NAME}};\n        }";
    
    auto conditionSeparatorIt = config_.syntaxElements.find("ENUM_CONDITION_SEPARATOR");
    std::string conditionSeparator = (conditionSeparatorIt != config_.syntaxElements.end()) ? 
        conditionSeparatorIt->second : " else ";
    
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += conditionSeparator;
        
        TemplateVars stringVars;
        stringVars["STRING_VALUE"] = enumNode.values[i]->name;
        std::string stringLiteral = renderTemplate(stringTemplate, stringVars);
        
        TemplateVars conditionVars;
        conditionVars["CLASS_NAME"] = className;
        conditionVars["ENUM_VALUE_NAME"] = enumNode.values[i]->name;
        conditionVars["STRING_LITERAL"] = stringLiteral;
        
        result += renderTemplate(conditionTemplate, conditionVars);
    }
    return result;
}

std::string Generator::generateEnumStringValuesFromTemplate(const ast::Enum& enumNode) {
    auto stringValueTemplateIt = config_.templateVariables.find("ENUM_STRING_VALUE_TEMPLATE");
    std::string stringValueTemplate = (stringValueTemplateIt != config_.templateVariables.end()) ? 
        stringValueTemplateIt->second : "<< {{STRING_LITERAL}}";
    
    auto stringValueSeparatorIt = config_.syntaxElements.find("ENUM_STRING_VALUE_SEPARATOR");
    std::string stringValueSeparator = (stringValueSeparatorIt != config_.syntaxElements.end()) ? 
        stringValueSeparatorIt->second : " ";
    
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += stringValueSeparator;
        
        TemplateVars stringVars;
        stringVars["STRING_VALUE"] = enumNode.values[i]->name;
        std::string stringLiteral = renderTemplate(stringTemplate, stringVars);
        
        TemplateVars valueVars;
        valueVars["STRING_LITERAL"] = stringLiteral;
        
        result += renderTemplate(stringValueTemplate, valueVars);
    }
    return result;
}

std::string Generator::generateEnumDisplayNamesFromTemplate(const ast::Enum& enumNode) {
    auto displayNameTemplateIt = config_.templateVariables.find("ENUM_DISPLAY_NAME_TEMPLATE");
    std::string displayNameTemplate = (displayNameTemplateIt != config_.templateVariables.end()) ? 
        displayNameTemplateIt->second : "<< {{STRING_LITERAL}}";
    
    auto displayNameSeparatorIt = config_.syntaxElements.find("ENUM_DISPLAY_NAME_SEPARATOR");
    std::string displayNameSeparator = (displayNameSeparatorIt != config_.syntaxElements.end()) ? 
        displayNameSeparatorIt->second : " ";
    
    std::string stringTemplate = config_.codeGeneration.stringLiteralTemplate.empty() ? 
        "QLatin1String(\"{{STRING_VALUE}}\")" : config_.codeGeneration.stringLiteralTemplate;
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += displayNameSeparator;
        
        // 获取显示名称（从注解中获取desc，如果没有则使用枚举值名称）
        std::string displayName = getEnumValueDisplayName(*enumNode.values[i]);
        
        TemplateVars stringVars;
        stringVars["STRING_VALUE"] = displayName;
        std::string stringLiteral = renderTemplate(stringTemplate, stringVars);
        
        TemplateVars displayVars;
        displayVars["STRING_LITERAL"] = stringLiteral;
        
        result += renderTemplate(displayNameTemplate, displayVars);
    }
    return result;
}

std::string Generator::getEnumValueDisplayName(const ast::EnumValue& enumValue) {
    // 默认使用枚举值名称
    std::string displayName = enumValue.name;
    
    // 从配置获取枚举值注解名称
    auto enumValueAnnotationNamesIt = config_.syntaxElements.find("ENUM_VALUE_ANNOTATION_NAMES");
    std::string enumValueAnnotationNames = (enumValueAnnotationNamesIt != config_.syntaxElements.end()) ? 
        enumValueAnnotationNamesIt->second : "yima.EnumValue|EnumValue";
    
    // 从配置获取描述参数名称
    auto descParamNameIt = config_.syntaxElements.find("DESC_PARAM_NAME");
    std::string descParamName = (descParamNameIt != config_.syntaxElements.end()) ? 
        descParamNameIt->second : "desc";
    
    // 解析注解名称列表
    std::vector<std::string> annotationNames;
    std::stringstream ss(enumValueAnnotationNames);
    std::string name;
    char separator = enumValueAnnotationNames.find('|') != std::string::npos ? '|' : ',';
    while (std::getline(ss, name, separator)) {
        annotationNames.push_back(name);
    }
    
    // 查找EnumValue注解中的desc参数
    for (const auto& annotation : enumValue.annotations) {
        bool isEnumValueAnnotation = false;
        for (const auto& annotationName : annotationNames) {
            if (annotation->name == annotationName) {
                isEnumValueAnnotation = true;
                break;
            }
        }
        
        if (isEnumValueAnnotation) {
            for (const auto& arg : annotation->arguments) {
                if (arg->name == descParamName) {
                    if (arg->value->nodeType() == ast::NodeType::Literal) {
                        auto literal = static_cast<const ast::Literal*>(arg->value.get());
                        if (std::holds_alternative<std::string>(literal->value)) {
                            displayName = std::get<std::string>(literal->value);
                            break;
                        }
                    } else if (arg->value->nodeType() == ast::NodeType::Identifier) {
                        // 处理字符串字面量被解析为标识符的情况
                        auto identifier = static_cast<const ast::Identifier*>(arg->value.get());
                        displayName = identifier->name;
                        break;
                    }
                }
            }
            break;
        }
    }
    
    return displayName;
}

std::string Generator::generateEnumAnnotationLogicFromTemplate(const ast::Enum& enumNode) {
    return generateAnnotationLogicFromTemplate(enumNode.annotations);
}

std::string Generator::generateEnumValueAnnotationCasesFromTemplate(const ast::Enum& enumNode, const std::string& className) {
    auto caseTemplateIt = config_.templateVariables.find("ENUM_VALUE_ANNOTATION_CASE_TEMPLATE");
    std::string caseTemplate = (caseTemplateIt != config_.templateVariables.end()) ? 
        caseTemplateIt->second : "case {{CLASS_NAME}}::{{ENUM_VALUE_NAME}}: {\n{{ANNOTATION_LOGIC}}\n            }";
    
    auto caseSeparatorIt = config_.syntaxElements.find("ENUM_ANNOTATION_CASE_SEPARATOR");
    std::string caseSeparator = (caseSeparatorIt != config_.syntaxElements.end()) ? 
        caseSeparatorIt->second : "\n            ";
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += caseSeparator;
        
        std::string annotationLogic = generateAnnotationLogicFromTemplate(enumNode.values[i]->annotations);
        
        TemplateVars caseVars;
        caseVars["CLASS_NAME"] = className;
        caseVars["ENUM_VALUE_NAME"] = enumNode.values[i]->name;
        caseVars["ANNOTATION_LOGIC"] = annotationLogic;
        
        result += renderTemplate(caseTemplate, caseVars);
    }
    return result;
}

std::string Generator::generateEnumValueAnnotationByNameLogicFromTemplate(const ast::Enum& enumNode) {
    auto conditionTemplateIt = config_.templateVariables.find("ENUM_VALUE_ANNOTATION_BY_NAME_CONDITION_TEMPLATE");
    std::string conditionTemplate = (conditionTemplateIt != config_.templateVariables.end()) ? 
        conditionTemplateIt->second : "if (valueName == \"{{ENUM_VALUE_NAME}}\") {\n{{ANNOTATION_LOGIC}}\n        }";
    
    auto conditionSeparatorIt = config_.syntaxElements.find("ENUM_ANNOTATION_CONDITION_SEPARATOR");
    std::string conditionSeparator = (conditionSeparatorIt != config_.syntaxElements.end()) ? 
        conditionSeparatorIt->second : " else ";
    
    std::string result;
    for (size_t i = 0; i < enumNode.values.size(); ++i) {
        if (i > 0) result += conditionSeparator;
        
        std::string annotationLogic = generateAnnotationLogicFromTemplate(enumNode.values[i]->annotations);
        
        TemplateVars conditionVars;
        conditionVars["ENUM_VALUE_NAME"] = enumNode.values[i]->name;
        conditionVars["ANNOTATION_LOGIC"] = annotationLogic;
        
        result += renderTemplate(conditionTemplate, conditionVars);
    }
    return result;
}

std::string Generator::generateAnnotationLogicFromTemplate(const std::vector<std::unique_ptr<ast::Annotation>>& annotations) {
    auto annotationListTemplateIt = config_.templateVariables.find("ANNOTATION_LIST_TEMPLATE");
    std::string annotationListTemplate = (annotationListTemplateIt != config_.templateVariables.end()) ? 
        annotationListTemplateIt->second : "QList<QSharedPointer<IAnnotation>> result;";
    
    auto todoCommentTemplateIt = config_.templateVariables.find("TODO_COMMENT_TEMPLATE");
    std::string todoCommentTemplate = (todoCommentTemplateIt != config_.templateVariables.end()) ? 
        todoCommentTemplateIt->second : "// TODO: 创建 {{ANNOTATION_NAME}} 注解实例";
    
    auto returnResultTemplateIt = config_.templateVariables.find("RETURN_RESULT_TEMPLATE");
    std::string returnResultTemplate = (returnResultTemplateIt != config_.templateVariables.end()) ? 
        returnResultTemplateIt->second : "return result;";
    
    std::string result = "                " + annotationListTemplate + "\n";
    for (const auto& annotation : annotations) {
        TemplateVars todoVars;
        todoVars["ANNOTATION_NAME"] = annotation->name;
        result += "                " + renderTemplate(todoCommentTemplate, todoVars) + "\n";
    }
    result += "                " + returnResultTemplate;
    
    return result;
}

std::string Generator::generateAnnotationInstancesLogic(const std::vector<std::unique_ptr<ast::Annotation>>& annotations) {
    std::string result = "QList<QSharedPointer<void>> result;\n";
    
    for (const auto& annotation : annotations) {
        std::string annotationClassName = formatTypeNameFromConfig(annotation->name, "annotation");
        result += "            auto " + annotation->name + "Instance = QSharedPointer<" + annotationClassName + ">::create();\n";
        
        // 设置注解参数
        for (const auto& arg : annotation->arguments) {
            std::string setterName = "set" + toPascalCase(arg->name);
            std::string argValue = generateAnnotationArgumentValue(*arg->value);
            result += "            " + annotation->name + "Instance->" + setterName + "(" + argValue + ");\n";
        }
        
        result += "            result.append(qSharedPointerCast<void>(" + annotation->name + "Instance));\n";
    }
    
    result += "\n            return result;";
    return result;
}

std::string Generator::generateAnnotationArgumentValue(const ast::Expr& expr) {
    switch (expr.nodeType()) {
        case ast::NodeType::Literal: {
            auto& literal = static_cast<const ast::Literal&>(expr);
            if (std::holds_alternative<std::string>(literal.value)) {
                return "\"" + std::get<std::string>(literal.value) + "\"";
            } else if (std::holds_alternative<int64_t>(literal.value)) {
                return std::to_string(std::get<int64_t>(literal.value));
            } else if (std::holds_alternative<double>(literal.value)) {
                return std::to_string(std::get<double>(literal.value));
            } else if (std::holds_alternative<bool>(literal.value)) {
                return std::get<bool>(literal.value) ? "true" : "false";
            }
            break;
        }
        case ast::NodeType::ArrayLiteral: {
            auto& arrayLiteral = static_cast<const ast::ArrayLiteral&>(expr);
            std::string result = "{";
            for (size_t i = 0; i < arrayLiteral.elements.size(); ++i) {
                if (i > 0) result += ", ";
                result += generateAnnotationArgumentValue(*arrayLiteral.elements[i]);
            }
            result += "}";
            return result;
        }
        case ast::NodeType::Annotation: {
            auto& annotation = static_cast<const ast::Annotation&>(expr);
            std::string annotationClassName = formatTypeNameFromConfig(annotation.name, "annotation");
            std::string result = "QSharedPointer<" + annotationClassName + ">::create()";
            // 这里可以进一步处理嵌套注解的参数
            return result;
        }
        case ast::NodeType::Identifier: {
            auto& identifier = static_cast<const ast::Identifier&>(expr);
            return identifier.name;
        }
        default:
            break;
    }
    return "nullptr";
}

} // namespace generator
} // namespace mota 