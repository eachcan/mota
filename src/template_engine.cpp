#include "template_engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stack>
#include <stdexcept>

namespace mota {
namespace template_engine {

TemplateEngine::TemplateEngine(const config::TemplateConfig& config, const std::string& templateDir)
    : config_(config), templateDir_(templateDir) {
}

std::string TemplateEngine::renderTemplate(const std::string& templateName, const TemplateVars& vars) {
    std::string templateContent = loadTemplate(templateName);
    if (templateContent.empty()) {
        return "";
    }
    return renderContent(templateContent, vars);
}

std::string TemplateEngine::renderContent(const std::string& templateContent, const TemplateVars& vars) {
    // 按照新的流程进行渲染
    // 1. 构建Token序列（文本和Tag的序列）
    auto tokens = buildTokenSequence(templateContent);
    
    // 2. 构建Tag树并检查成对标签
    auto tree = buildTagTree(tokens);
    
    // 3. 遍历渲染Tag树
    return renderTagTree(tree, vars);
}

std::string TemplateEngine::renderAnnoArgValue(const std::string& argType, const TemplateVars& vars) {
    // 根据注解参数类型调用不同的misc进行渲染
    std::string miscName;
    
    if (argType == "string") {
        miscName = "anno_arg_string";
    } else if (argType == "int32" || argType == "int64" || argType == "uint32" || argType == "uint64") {
        miscName = "anno_arg_int";
    } else if (argType == "bool") {
        miscName = "anno_arg_bool";
    } else if (argType == "float32" || argType == "float64") {
        miscName = "anno_arg_float";
    } else {
        // 对于其他注解类型，使用通用的注解参数misc
        miscName = "anno_arg_complex";
    }
    
    return renderMiscCall(miscName, vars);
}

std::string TemplateEngine::loadTemplate(const std::string& templateName) {
    // 检查缓存
    auto it = templateCache_.find(templateName);
    if (it != templateCache_.end()) {
        return it->second;
    }
    
    // 从配置中获取模板文件名
    auto templateIt = config_.templates.find(templateName);
    if (templateIt == config_.templates.end()) {
        std::cerr << "Template not found: " << templateName << std::endl;
        return "";
    }
    
    std::string templatePath = templateDir_ + "/" + templateIt->second;
    std::ifstream file(templatePath);
    if (!file.is_open()) {
        std::cerr << "Cannot open template file: " << templatePath << std::endl;
        return "";
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    
    // 缓存内容
    templateCache_[templateName] = content;
    return content;
}

std::string TemplateEngine::loadMisc(const std::string& miscName) {
    // Check cache
    auto it = miscCache_.find(miscName);
    if (it != miscCache_.end()) {
        return it->second;
    }
    
    // Load all misc files and parse
    for (const auto& miscFile : config_.miscs) {
        std::string miscPath = templateDir_ + "/" + miscFile;
        std::ifstream file(miscPath);
        if (!file.is_open()) {
            continue;
        }
        
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        
        // Parse misc fragments
        std::regex miscRegex("<%misc\\s+([^%>]+)%>([\\s\\S]*?)<%endmisc%>");
        std::sregex_iterator iter(content.begin(), content.end(), miscRegex);
        std::sregex_iterator end;
        
        while (iter != end) {
            std::smatch match = *iter;
            std::string name = match[1].str();
            std::string miscContent = match[2].str();
            
            // Trim whitespace
            name = trimWhitespace(name);
            miscCache_[name] = miscContent;
            ++iter;
        }
    }
    
    // Find requested misc fragment
    auto miscIt = miscCache_.find(miscName);
    if (miscIt != miscCache_.end()) {
        return miscIt->second;
    }
    
    return "";
}

std::vector<std::shared_ptr<TagNode>> TemplateEngine::buildTokenSequence(const std::string& content) {
    std::vector<std::shared_ptr<TagNode>> tokens;
    
    // 使用正则表达式查找所有Tag
    std::regex tagRegex("<%([\\s\\S]*?)%>");
    std::sregex_iterator iter(content.begin(), content.end(), tagRegex);
    std::sregex_iterator end;
    
    size_t lastPos = 0;
    
    while (iter != end) {
        std::smatch match = *iter;
        size_t tagStart = match.position();
        size_t tagEnd = tagStart + match.length();
        
        // 添加Tag之前的文本
        if (tagStart > lastPos) {
            auto textNode = std::make_shared<TagNode>(TagType::TEXT);
            textNode->content = content.substr(lastPos, tagStart - lastPos);
            textNode->start_pos = lastPos;
            textNode->end_pos = tagStart;
            tokens.push_back(textNode);
        }
        
        // 解析Tag
        std::string tagContent = match[1].str();
        auto tagNode = parseTag(tagContent, tagStart, tagEnd);
        if (tagNode) {
            tagNode->content = match[0].str();
            tokens.push_back(tagNode);
        }
        
        lastPos = tagEnd;
        ++iter;
    }
    
    // 添加最后的文本
    if (lastPos < content.length()) {
        auto textNode = std::make_shared<TagNode>(TagType::TEXT);
        textNode->content = content.substr(lastPos);
        textNode->start_pos = lastPos;
        textNode->end_pos = content.length();
        tokens.push_back(textNode);
    }
    
    return tokens;
}

std::shared_ptr<TagNode> TemplateEngine::parseTag(const std::string& tagContent, size_t start, size_t end) {
    std::string trimmed = trimWhitespace(tagContent);
    
    if (trimmed.empty()) {
        return nullptr;
    }
    
    // 解析不同类型的Tag
    if (trimmed.substr(0, 1) == "=") {
        // 变量或函数调用 <%=...%>
        std::string expr = trimWhitespace(trimmed.substr(1));
        if (expr.find('(') != std::string::npos && expr.find(')') != std::string::npos) {
            return parseFunctionCallTag(expr, start, end);
        } else {
            return parseVariableTag(expr, start, end);
        }
    } else if (trimmed.substr(0, 4) == "call" && isspace(trimmed[4])) {
        // misc调用 <%call misc_name%>
        return parseMiscCallTag(trimmed, start, end);
    } else if (trimmed.substr(0, 2) == "if") {
        // 条件语句 <%if (condition)%>
        return parseIfTag(trimmed, start, end);
    } else if (trimmed == "else") {
        // else分支 <%else%>
        auto node = std::make_shared<TagNode>(TagType::ELSE);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    } else if (trimmed == "endif") {
        // 条件结束 <%endif%>
        auto node = std::make_shared<TagNode>(TagType::END_IF);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    } else if (trimmed.substr(0, 7) == "foreach") {
        // 循环语句 <%foreach collection as item%>
        return parseForeachTag(trimmed, start, end);
    } else if (trimmed == "endforeach") {
        // 循环结束 <%endforeach%>
        auto node = std::make_shared<TagNode>(TagType::END_FOREACH);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    }

    throw std::runtime_error("invalid tag [" + std::to_string(start) + ", " + std::to_string(end) + "] " + tagContent);
    
    return nullptr;
}

std::shared_ptr<TagNode> TemplateEngine::parseVariableTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TagNode>(TagType::VARIABLE);
    node->variable_name = trimWhitespace(tagContent);
    node->start_pos = start;
    node->end_pos = end;
    return node;
}

std::shared_ptr<TagNode> TemplateEngine::parseFunctionCallTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TagNode>(TagType::FUNCTION_CALL);
    
    size_t parenPos = tagContent.find('(');
    if (parenPos != std::string::npos) {
        node->function_name = trimWhitespace(tagContent.substr(0, parenPos));
        
        size_t endParenPos = tagContent.rfind(')');
        if (endParenPos != std::string::npos && endParenPos > parenPos) {
            node->function_args = trimWhitespace(tagContent.substr(parenPos + 1, endParenPos - parenPos - 1));
        }
    }
    
    node->start_pos = start;
    node->end_pos = end;
    return node;
}

std::shared_ptr<TagNode> TemplateEngine::parseMiscCallTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TagNode>(TagType::MISC_CALL);
    
    // 提取misc名称 "call misc_name"
    std::string miscPart = trimWhitespace(tagContent.substr(4)); // 跳过"call"
    node->misc_name = miscPart;
    node->start_pos = start;
    node->end_pos = end;
    
    return node;
}

std::shared_ptr<TagNode> TemplateEngine::parseIfTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TagNode>(TagType::IF);
    
    // 提取条件 "if (condition)"
    size_t parenStart = tagContent.find('(');
    size_t parenEnd = tagContent.rfind(')');
    
    if (parenStart != std::string::npos && parenEnd != std::string::npos && parenEnd > parenStart) {
        node->condition = trimWhitespace(tagContent.substr(parenStart + 1, parenEnd - parenStart - 1));
    }
    
    node->start_pos = start;
    node->end_pos = end;
    return node;
}

std::shared_ptr<TagNode> TemplateEngine::parseForeachTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TagNode>(TagType::FOREACH);
    
    // 提取集合和项目名称 "foreach collection as item"
    std::string foreachPart = trimWhitespace(tagContent.substr(7)); // 跳过"foreach"
    size_t asPos = foreachPart.find(" as ");
    
    if (asPos != std::string::npos) {
        node->collection = trimWhitespace(foreachPart.substr(0, asPos));
        node->item_name = trimWhitespace(foreachPart.substr(asPos + 4));
    }
    
    node->start_pos = start;
    node->end_pos = end;
    return node;
}

std::vector<std::shared_ptr<TagNode>> TemplateEngine::buildTagTree(const std::vector<std::shared_ptr<TagNode>>& tokens) {
    std::vector<std::shared_ptr<TagNode>> result;
    size_t i = 0;
    
    while (i < tokens.size()) {
        auto token = tokens[i];
        
        if (token->type == TagType::IF) {
            // 解析if块的内容
            size_t ifStart = i;
            size_t level = 1;
            size_t elsePos = SIZE_MAX;
            size_t endPos = SIZE_MAX;
            
            // 查找匹配的endif和else
            for (size_t j = i + 1; j < tokens.size(); ++j) {
                if (tokens[j]->type == TagType::IF) {
                    level++;
                } else if (tokens[j]->type == TagType::END_IF) {
                    level--;
                    if (level == 0) {
                        endPos = j;
                        break;
                    }
                } else if (tokens[j]->type == TagType::ELSE && level == 1 && elsePos == SIZE_MAX) {
                    elsePos = j;
                }
            }
            
            if (endPos == SIZE_MAX) {
                std::cerr << "Unmatched if tag" << std::endl;
                return result;
            }
            
            // 创建if节点并设置内容
            auto ifNode = token;
            
            // 提取if块的内容
            std::string ifContent;
            for (size_t j = ifStart + 1; j < (elsePos != SIZE_MAX ? elsePos : endPos); ++j) {
                ifContent += tokens[j]->content;
            }
            ifNode->data = ifContent; // 使用data字段存储原始内容
            
            // 如果有else分支，提取else内容
            if (elsePos != SIZE_MAX) {
                std::string elseContent;
                for (size_t j = elsePos + 1; j < endPos; ++j) {
                    elseContent += tokens[j]->content;
                }
                // 创建一个虚拟的else节点来存储else内容
                auto elseNode = std::make_shared<TagNode>(TagType::ELSE);
                elseNode->data = elseContent;
                ifNode->else_children.push_back(elseNode);
            }
            
            result.push_back(ifNode);
            i = endPos + 1; // 跳过整个if块
            
        } else if (token->type == TagType::FOREACH) {
            // 解析foreach块的内容
            size_t foreachStart = i;
            size_t level = 1;
            size_t endPos = SIZE_MAX;
            
            // 查找匹配的endforeach
            for (size_t j = i + 1; j < tokens.size(); ++j) {
                if (tokens[j]->type == TagType::FOREACH) {
                    level++;
                } else if (tokens[j]->type == TagType::END_FOREACH) {
                    level--;
                    if (level == 0) {
                        endPos = j;
                        break;
                    }
                }
            }
            
            if (endPos == SIZE_MAX) {
                std::cerr << "Unmatched foreach tag" << std::endl;
                return result;
            }
            
            // 创建foreach节点并设置内容
            auto foreachNode = token;
            
            // 提取foreach块的内容
            std::string foreachContent;
            for (size_t j = foreachStart + 1; j < endPos; ++j) {
                foreachContent += tokens[j]->content;
            }
            foreachNode->data = foreachContent; // 使用data字段存储原始内容
            
            result.push_back(foreachNode);
            i = endPos + 1; // 跳过整个foreach块
            
        } else if (token->type == TagType::ELSE || token->type == TagType::END_IF || token->type == TagType::END_FOREACH) {
            // 这些标签应该在上面的逻辑中处理，如果到这里说明有语法错误
            std::cerr << "Unexpected tag: " << static_cast<int>(token->type) << std::endl;
            i++;
        } else {
            // 普通标签或文本
            result.push_back(token);
            i++;
        }
    }
    
    return result;
}

std::string TemplateEngine::renderTagTree(const std::vector<std::shared_ptr<TagNode>>& tree, const TemplateVars& vars) {
    std::string result;
    
    for (const auto& node : tree) {
        result += renderTagNode(node, vars);
    }
    
    return result;
}

std::string TemplateEngine::renderTagNode(const std::shared_ptr<TagNode>& node, const TemplateVars& vars) {
    switch (node->type) {
        case TagType::TEXT:
            return node->content;
            
        case TagType::VARIABLE:
            return renderVariable(node->variable_name, vars);
            
        case TagType::FUNCTION_CALL:
            return renderFunctionCall(node->function_name, node->function_args, vars);
            
        case TagType::MISC_CALL:
            return renderMiscCall(node->misc_name, vars);
            
        case TagType::IF:
            return renderIfBlock(node, vars);
            
        case TagType::FOREACH:
            return renderForeachBlock(node, vars);
            
        case TagType::ELSE:
        case TagType::END_IF:
        case TagType::END_FOREACH:
            // 结束标签和else标签不应该单独渲染
            return "";
            
        default:
            return "";
    }
}

std::string TemplateEngine::renderVariable(const std::string& varName, const TemplateVars& vars) {
    // 支持对象属性访问，如 field.name
    size_t dotPos = varName.find('.');
    if (dotPos != std::string::npos) {
        std::string objectName = varName.substr(0, dotPos);
        std::string propertyName = varName.substr(dotPos + 1);
        
        if (vars.contains(objectName) && vars[objectName].is_object()) {
            const auto& obj = vars[objectName];
            if (obj.contains(propertyName)) {
                const auto& value = obj[propertyName];
                if (value.is_string()) {
                    return value.get<std::string>();
                } else if (value.is_number()) {
                    return value.dump();
                } else if (value.is_boolean()) {
                    return value.get<bool>() ? "true" : "false";
                } else {
                    return value.dump();
                }
            }
        }
        return "";
    }
    
    if (!vars.contains(varName)) {
        return "";
    }
    
    const auto& value = vars[varName];
    if (value.is_string()) {
        return value.get<std::string>();
    } else if (value.is_number()) {
        return value.dump();
    } else if (value.is_boolean()) {
        return value.get<bool>() ? "true" : "false";
    } else {
        return value.dump();
    }
}

std::string TemplateEngine::renderFunctionCall(const std::string& funcName, const std::string& args, const TemplateVars& vars) {
    // 解析参数列表，支持多个参数
    std::vector<std::string> parsedArgs = parseArguments(args);
    
    // 对每个参数进行求值，支持嵌套函数调用和变量引用
    std::vector<std::string> evaluatedArgs;
    for (const auto& arg : parsedArgs) {
        evaluatedArgs.push_back(evaluateExpression(arg, vars));
    }
    
    // 调用内置函数
    return callBuiltinFunction(funcName, evaluatedArgs, vars);
}

std::string TemplateEngine::renderMiscCall(const std::string& miscName, const TemplateVars& vars) {
    return callMisc(miscName, vars);
}

std::string TemplateEngine::renderIfBlock(const std::shared_ptr<TagNode>& ifNode, const TemplateVars& vars) {
    bool conditionResult = evaluateCondition(ifNode->condition, vars);
    
    if (conditionResult) {
        // 重新解析并渲染if块的内容
        return renderContent(ifNode->data, vars);
    } else {
        // 渲染else分支
        if (!ifNode->else_children.empty()) {
            // 获取else内容并重新解析渲染
            return renderContent(ifNode->else_children[0]->data, vars);
        }
        return "";
    }
}

std::string TemplateEngine::renderForeachBlock(const std::shared_ptr<TagNode>& foreachNode, const TemplateVars& vars) {
    // 查找集合数据
    if (!vars.contains(foreachNode->collection)) {
        return "";
    }
    
    const auto& collection = vars[foreachNode->collection];
    std::string result;
    
    // 解析JSON数组
    if (collection.is_array()) {
        const auto& jsonArray = collection;
        
        for (size_t i = 0; i < jsonArray.size(); ++i) {
            const auto& itemObj = jsonArray[i];
            
            // 创建循环项的变量上下文
            TemplateVars itemVars = vars; // 复制原始变量
            
            // 直接添加项目变量，使用item_name作为key
            itemVars[foreachNode->item_name] = itemObj;
            
            // 添加索引变量
            itemVars["index"] = i;
            itemVars["INDEX"] = i;
            
            // 添加是否为第一个/最后一个的标志
            itemVars["is_first"] = (i == 0);
            itemVars["is_last"] = (i == jsonArray.size() - 1);
            itemVars["IS_FIRST"] = (i == 0);
            itemVars["IS_LAST"] = (i == jsonArray.size() - 1);
            
            // 重新解析并渲染foreach块的内容
            result += renderContent(foreachNode->data, itemVars);
        }
    }
    
    return result;
}

bool TemplateEngine::evaluateCondition(const std::string& condition, const TemplateVars& vars) {
    // std::cout << "DEBUG: evaluateCondition called with: '" << condition << "'" << std::endl;
    
    // 检查相等条件
    size_t eqPos = condition.find("==");
    if (eqPos != std::string::npos) {
        std::string left = condition.substr(0, eqPos);
        std::string right = condition.substr(eqPos + 2);
        
        // 使用 evaluateExpression 执行等号两侧的表达式
        std::string leftValue = evaluateExpression(left, vars);
        std::string rightValue = evaluateExpression(right, vars);
        
        // std::cout << "DEBUG: Condition '" << condition << "' -> left: '" << leftValue << "', right: '" << rightValue << "', result: " << (leftValue == rightValue) << std::endl;
        
        // 比较结果
        return leftValue == rightValue;
    }

    size_t notPos = condition.find("!=");
    if (notPos != std::string::npos) {
        std::string left = condition.substr(0, notPos);
        std::string right = condition.substr(notPos + 2);
        
        // 使用 evaluateExpression 执行不等号两侧的表达式
        std::string leftValue = evaluateExpression(left, vars);
        std::string rightValue = evaluateExpression(right, vars);
        
        // 比较结果
        return leftValue != rightValue;
    }

    size_t gtPos = condition.find(">");
    if (gtPos != std::string::npos) {
        std::string left = condition.substr(0, gtPos);
        std::string right = condition.substr(gtPos + 1);
        
        // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
        double leftValue = std::stod(evaluateExpression(left, vars));
        double rightValue = std::stod(evaluateExpression(right, vars));
        
        // 比较结果
        return leftValue > rightValue;
    }

    size_t ltPos = condition.find("<");
    if (ltPos != std::string::npos) {
        std::string left = condition.substr(0, ltPos);
        std::string right = condition.substr(ltPos + 1);
        
        // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
        double leftValue = std::stod(evaluateExpression(left, vars));
        double rightValue = std::stod(evaluateExpression(right, vars));
        
        // 比较结果
        return leftValue < rightValue;
    }

    size_t gtePos = condition.find(">=");
    if (gtePos != std::string::npos) {
        std::string left = condition.substr(0, gtePos);
        std::string right = condition.substr(gtePos + 2);
        
        // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
        double leftValue = std::stod(evaluateExpression(left, vars));
        double rightValue = std::stod(evaluateExpression(right, vars));
        
        // 比较结果
        return leftValue >= rightValue;
    }

    size_t ltePos = condition.find("<=");
    if (ltePos != std::string::npos) {
        std::string left = condition.substr(0, ltePos);
        std::string right = condition.substr(ltePos + 2);
        
        // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
        double leftValue = std::stod(evaluateExpression(left, vars));
        double rightValue = std::stod(evaluateExpression(right, vars));
        
        // 比较结果
        return leftValue <= rightValue;
    }

    // 检查变量存在性
    std::string varName = trimWhitespace(condition);
    if (!vars.contains(varName)) {
        return false;
    }
    
    const auto& value = vars[varName];
    if (value.is_boolean()) {
        return value.get<bool>();
    } else if (value.is_string()) {
        std::string strValue = value.get<std::string>();
        return !strValue.empty() && strValue != "false";
    }
    
    return true;
}

std::string TemplateEngine::callMisc(const std::string& miscName, const TemplateVars& vars) {
    std::cout << "DEBUG: callMisc called with name: " << miscName << std::endl;
    std::string miscContent = loadMisc(miscName);
    std::cout << "DEBUG: miscContent length: " << miscContent.length() << std::endl;
    if (miscContent.empty()) {
        std::cout << "DEBUG: misc content is empty!" << std::endl;
        return "[MISSING_MISC:" + miscName + "]";
    }
    
    std::cout << "DEBUG: misc content: " << miscContent.substr(0, 100) << "..." << std::endl;
    
    // 递归渲染misc内容
    std::string result = renderContent(miscContent, vars);
    std::cout << "DEBUG: rendered result length: " << result.length() << std::endl;
    std::cout << "DEBUG: rendered result: " << result.substr(0, 100) << "..." << std::endl;
    return result;
}

std::string TemplateEngine::toPascalCase(const std::string& str) {
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

std::string TemplateEngine::toCamelCase(const std::string& str) {
    std::string pascal = toPascalCase(str);
    if (!pascal.empty()) {
        pascal[0] = std::tolower(pascal[0]);
    }
    return pascal;
}

std::string TemplateEngine::mapType(const std::string& motaType) {
    auto it = config_.type_mapping.find(motaType);
    if (it != config_.type_mapping.end()) {
        return it->second;
    }
    return motaType;
}

std::string TemplateEngine::escapeString(const std::string& str) {
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



std::string TemplateEngine::getFirstNamespacePart(const std::string& namespaceStr) {
    if (namespaceStr.empty()) {
        return "";
    }
    
    size_t dotPos = namespaceStr.find('.');
    if (dotPos == std::string::npos) {
        return namespaceStr;
    }
    
    return namespaceStr.substr(0, dotPos);
}

bool TemplateEngine::hasNestedNamespace(const std::string& namespaceStr) {
    return namespaceStr.find('.') != std::string::npos;
}

std::string TemplateEngine::formatNamespacePath(const std::string& namespaceStr) {
    if (namespaceStr.empty()) {
        return "";
    }
    
    std::string result = namespaceStr;
    std::replace(result.begin(), result.end(), '.', '/');
    return result;
}

std::string TemplateEngine::trimWhitespace(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> TemplateEngine::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(trimWhitespace(item));
    }
    
    return result;
}

std::vector<std::string> TemplateEngine::parseArguments(const std::string& args) {
    std::vector<std::string> result;
    if (args.empty()) {
        return result;
    }
    
    std::string current;
    int parenLevel = 0;
    int quoteState = 0; // 0: 无引号, 1: 单引号, 2: 双引号
    bool escaped = false;
    
    for (size_t i = 0; i < args.length(); ++i) {
        char c = args[i];
        
        if (escaped) {
            current += c;
            escaped = false;
            continue;
        }
        
        if (c == '\\') {
            escaped = true;
            current += c;
            continue;
        }
        
        if (quoteState == 0) {
            if (c == '\'') {
                quoteState = 1;
                current += c;
            } else if (c == '"') {
                quoteState = 2;
                current += c;
            } else if (c == '(') {
                parenLevel++;
                current += c;
            } else if (c == ')') {
                parenLevel--;
                current += c;
            } else if (c == ',' && parenLevel == 0) {
                if (current.empty()) {
                    throw std::runtime_error("invalid function arguments: " + args);
                }

                // 找到参数分隔符
                result.push_back(trimWhitespace(current));
                current.clear();
            } else {
                current += c;
            }
        } else {
            current += c;
            if ((quoteState == 1 && c == '\'') || (quoteState == 2 && c == '"')) {
                quoteState = 0;
            }
        }
    }

    if (parenLevel != 0) {
        throw std::runtime_error("invalid function arguments: " + args);
    }
    
    // 添加最后一个参数
    if (!current.empty()) {
        result.push_back(trimWhitespace(current));
    }
    
    return result;
}

std::string TemplateEngine::evaluateExpression(const std::string& expr, const TemplateVars& vars) {
    std::string trimmedExpr = trimWhitespace(expr);
    if (trimmedExpr.empty()) {
        return "";
    }
    
    // 检查是否是字符串字面量
    if ((trimmedExpr.front() == '"' && trimmedExpr.back() == '"') ||
        (trimmedExpr.front() == '\'' && trimmedExpr.back() == '\'')) {
        // 去掉引号并处理转义字符
        std::string content = trimmedExpr.substr(1, trimmedExpr.length() - 2);
        std::string result;
        result.reserve(content.length());
        
        for (size_t i = 0; i < content.length(); ++i) {
            if (content[i] == '\\' && i + 1 < content.length()) {
                char next = content[i + 1];
                switch (next) {
                    case 'n': result += '\n'; break;
                    case 't': result += '\t'; break;
                    case 'r': result += '\r'; break;
                    case '\\': result += '\\'; break;
                    case '"': result += '"'; break;
                    case '\'': result += '\''; break;
                    default: 
                        result += '\\';
                        result += next;
                        break;
                }
                ++i; // 跳过转义字符
            } else {
                result += content[i];
            }
        }
        return result;
    }
    
    // 检查是否是嵌套函数调用
    size_t parenPos = trimmedExpr.find('(');
    if (parenPos != std::string::npos && trimmedExpr.back() == ')') {
        std::string funcName = trimWhitespace(trimmedExpr.substr(0, parenPos));
        std::string funcArgs = trimmedExpr.substr(parenPos + 1, trimmedExpr.length() - parenPos - 2);
        return renderFunctionCall(funcName, funcArgs, vars);
    }
    
    // 检查是否是对象属性访问
    size_t dotPos = trimmedExpr.find('.');
    if (dotPos != std::string::npos) {
        // std::cout << "DEBUG: Processing property path: " << trimmedExpr << std::endl;
        
        // 支持多级对象属性访问，如 obj.prop1.prop2.prop3
        std::vector<std::string> propertyPath;
        std::string remaining = trimmedExpr;
        
        // 分解属性路径
        while (!remaining.empty()) {
            size_t pos = remaining.find('.');
            if (pos == std::string::npos) {
                if (remaining.empty()) {
                    throw std::runtime_error("invalid property path: " + trimmedExpr);
                }
                propertyPath.push_back(remaining);
                break;
            } else {
                auto segment = remaining.substr(0, pos);
                if (segment.empty()) {
                    throw std::runtime_error("invalid property path: " + trimmedExpr);
                }
                propertyPath.push_back(segment);
                remaining = remaining.substr(pos + 1);
            }
        }
        
        // std::cout << "DEBUG: Property path segments: " << trimmedExpr << std::endl;
        
        if (propertyPath.empty()) {
            throw std::runtime_error("invalid property path: " + trimmedExpr);
        }
        
        // 从根对象开始逐级访问
        if (!vars.contains(propertyPath[0])) {
            return "";  // 返回空字符串而不是抛异常
        }
        
        const nlohmann::json* currentObj = &(vars[propertyPath[0]]);
        
        // 逐级访问属性
        for (size_t i = 1; i < propertyPath.size(); ++i) {
            if (!currentObj->is_object()) {
                return "";  // 返回空字符串而不是抛异常
            }
            
            if (!currentObj->contains(propertyPath[i])) {
                return "";  // 返回空字符串而不是抛异常
            }
            
            currentObj = &((*currentObj)[propertyPath[i]]);
        }
        
        // 返回最终值
        if (currentObj->is_string()) {
            return currentObj->get<std::string>();
        } else if (currentObj->is_number()) {
            return currentObj->dump();
        } else if (currentObj->is_boolean()) {
            return currentObj->get<bool>() ? "true" : "false";
        } else {
            return currentObj->dump();
        }
    }
    
    // 检查是否是变量引用
    std::cout << "DEBUG: evaluateExpression checking variable: '" << trimmedExpr << "'" << std::endl;
    if (vars.contains(trimmedExpr)) {
        const auto& value = vars[trimmedExpr];
        std::cout << "DEBUG: Found variable '" << trimmedExpr << "' = " << value.dump() << std::endl;
        if (value.is_string()) {
            return value.get<std::string>();
        } else if (value.is_number()) {
            return value.dump();
        } else if (value.is_boolean()) {
            return value.get<bool>() ? "true" : "false";
        } else {
            return value.dump();
        }
    }
    
    std::cout << "DEBUG: Variable '" << trimmedExpr << "' not found, returning literal" << std::endl;
    // 默认返回原始表达式
    return trimmedExpr;
}

std::string TemplateEngine::callBuiltinFunction(const std::string& funcName, const std::vector<std::string>& args, const TemplateVars& vars) {
    // 单参数函数
    if (args.size() == 1) {
        const std::string& arg = args[0];
        
        if (funcName == "pascal_case") {
            return toPascalCase(arg);
        } else if (funcName == "camel_case") {
            return toCamelCase(arg);
        } else if (funcName == "map_type") {
            return mapType(arg);
        } else if (funcName == "escape_string") {
            return escapeString(arg);
        } else if (funcName == "first_namespace_part") {
            return getFirstNamespacePart(arg);
        } else if (funcName == "has_nested_namespace") {
            return hasNestedNamespace(arg) ? "true" : "false";
        } else if (funcName == "namespace_path") {
            return formatNamespacePath(arg);
        } else if (funcName == "basename") {
            // 提取文件名（不包含路径和扩展名）
            std::string filename = arg;
            size_t lastSlash = filename.find_last_of("/\\");
            if (lastSlash != std::string::npos) {
                filename = filename.substr(lastSlash + 1);
            }
            size_t lastDot = filename.find_last_of('.');
            if (lastDot != std::string::npos) {
                filename = filename.substr(0, lastDot);
            }
            return filename;
        }
    }
    
    // 双参数函数
    if (args.size() == 2) {
        const std::string& arg1 = args[0];
        const std::string& arg2 = args[1];
        
        if (funcName == "join") {
            // join(separator, array_var_name)
            if (vars.contains(arg2) && vars[arg2].is_array()) {
                std::string result;
                const auto& jsonArray = vars[arg2];
                for (size_t i = 0; i < jsonArray.size(); ++i) {
                    if (i > 0) {
                        result += arg1;
                    }
                    if (jsonArray[i].is_string()) {
                        result += jsonArray[i].get<std::string>();
                    } else {
                        result += jsonArray[i].dump();
                    }
                }
                return result;
            }
            return "";
        } else if (funcName == "replace") {
            // replace(string, old_pattern, new_pattern) - 这里简化为双参数版本
            std::string result = arg1;
            std::string oldPattern = arg2;
            std::string newPattern = args.size() > 2 ? args[2] : "";
            
            size_t pos = 0;
            while ((pos = result.find(oldPattern, pos)) != std::string::npos) {
                result.replace(pos, oldPattern.length(), newPattern);
                pos += newPattern.length();
            }
            return result;
        } else if (funcName == "repeat") {
            // repeat(string, count)
            std::string result = arg1;
            int count = std::stoi(arg2);
            for (int i = 0; i < count; ++i) {
                result += arg1;
            }
            return result;
        }
    }
    
    // 三参数函数
    if (args.size() == 3) {
        if (funcName == "replace") {
            // replace(string, old_pattern, new_pattern)
            std::string result = args[0];
            const std::string& oldPattern = args[1];
            const std::string& newPattern = args[2];
            
            size_t pos = 0;
            while ((pos = result.find(oldPattern, pos)) != std::string::npos) {
                result.replace(pos, oldPattern.length(), newPattern);
                pos += newPattern.length();
            }
            return result;
        }
    }
    
    // 可变参数函数
    if (funcName == "concat") {
        std::string result;
        for (const auto& arg : args) {
            result += arg;
        }
        return result;
    }
    
    // 未知函数或参数数量不匹配
    return "";
}

} // namespace template_engine
} // namespace mota 