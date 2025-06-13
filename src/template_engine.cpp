#include "template_engine.h"
#include "generator.h"
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
    auto tree = buildTagTree(templateContent, tokens);

    // 3. 遍历渲染Tag树
    return renderTagTree(tree, vars);
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
    if (is_loaded_misc_) {
        auto it = miscCache_.find(trimWhitespace(miscName));
        if (it != miscCache_.end()) {
            return it->second;
        }
        // 找不到misc时输出错误信息
        std::cerr << "Misc not found: " << miscName << std::endl;
        return "";
    }

    is_loaded_misc_ = true;
    
    // Load all misc files and parse
    for (const auto& miscFile : config_.miscs) {
        std::string miscPath = templateDir_ + "/" + miscFile;
        std::ifstream file(miscPath);
        if (!file.is_open()) {
            std::cerr << "Cannot open misc file: " << miscPath << std::endl;
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
        
        int fragmentCount = 0;
        while (iter != end) {
            std::smatch match = *iter;
            std::string name = match[1].str();
            std::string miscContent = match[2].str();

            if (miscCache_.find(name) != miscCache_.end()) {
                std::cerr << "Error: " << miscFile << std::endl;
                std::cerr << "Duplicate misc name: " << name << std::endl;
                continue;
            }
            
            // Trim whitespace
            name = trimWhitespace(name);
            
            // 对misc内容应用独占一行处理逻辑
            // 去掉开头的空格+换行符（<%misc name%>后面可能有空格然后换行）
            size_t pos = 0;
            // 跳过开头的空格和制表符
            while (pos < miscContent.length() && (miscContent[pos] == ' ' || miscContent[pos] == '\t')) {
                pos++;
            }
            // 如果接下来是换行符，则去掉空格+换行
            if (pos < miscContent.length() && miscContent[pos] == '\n') {
                miscContent = miscContent.substr(pos + 1);
            } else if (pos + 1 < miscContent.length() && miscContent[pos] == '\r' && miscContent[pos + 1] == '\n') {
                miscContent = miscContent.substr(pos + 2);
            }
            
            // 不去掉结尾的换行符，因为那是misc内容自己带的
            
            miscCache_[name] = miscContent;
            fragmentCount++;
            ++iter;
        }
        
        std::cout << "Loaded " << fragmentCount << " misc fragments from " << miscFile << std::endl;
    }
    
    std::cout << "Total misc fragments loaded: " << miscCache_.size() << std::endl;
    
    // Find requested misc fragment
    auto miscIt = miscCache_.find(miscName);
    if (miscIt != miscCache_.end()) {
        return miscIt->second;
    }
    
    std::cerr << "Misc not found: " << miscName << std::endl;

    return "";
}

std::vector<std::shared_ptr<TemplateToken>> TemplateEngine::buildTokenSequence(const std::string& content) {
    std::vector<std::shared_ptr<TemplateToken>> tokens;
    
    // 使用正则表达式查找所有Tag
    std::regex tagRegex("<%([\\s\\S]*?)%>");
    std::sregex_iterator iter(content.begin(), content.end(), tagRegex);
    std::sregex_iterator end;
    
    size_t lastPos = 0;
    
    while (iter != end) {
        std::smatch match = *iter;
        size_t tagStart = match.position();
        size_t tagEnd = tagStart + match.length();
        
        // 检查标签是否独占一行
        bool tagOnOwnLine = false;
        size_t lineStart = tagStart;
        size_t lineEnd = tagEnd;
        
        // 向前查找行首，检查是否只有空白字符
        while (lineStart > 0 && content[lineStart - 1] != '\n' && content[lineStart - 1] != '\r') {
            lineStart--;
        }
        bool onlySpacesBeforeTag = true;
        for (size_t i = lineStart; i < tagStart; i++) {
            if (content[i] != ' ' && content[i] != '\t') {
                onlySpacesBeforeTag = false;
                break;
            }
        }
        
        // 向后查找行尾，检查是否只有空格然后是换行符
        bool directlyFollowedByNewline = false;
        size_t pos = tagEnd;
        // 跳过标签后面的空格和制表符
        while (pos < content.length() && (content[pos] == ' ' || content[pos] == '\t')) {
            pos++;
        }
        // 检查是否是换行符
        if (pos < content.length() && (content[pos] == '\n' || content[pos] == '\r')) {
            directlyFollowedByNewline = true;
            lineEnd = pos + 1;
            if (pos + 1 < content.length() && content[pos] == '\r' && content[pos + 1] == '\n') {
                lineEnd = pos + 2;
            }
        }
        
        tagOnOwnLine = onlySpacesBeforeTag && directlyFollowedByNewline;
        
        // 添加Tag之前的文本
        if (tagStart > lastPos) {
            auto textNode = std::make_shared<TemplateToken>(TokenType::TEXT);
            std::string text;
            
            if (tagOnOwnLine) {
                // 如果标签独占一行，则去掉前面的空白字符
                text = content.substr(lastPos, lineStart - lastPos);
            } else {
                text = content.substr(lastPos, tagStart - lastPos);
            }
            
            if (!text.empty()) {
                textNode->outer_content = text;
                textNode->start_pos = lastPos;
                textNode->end_pos = tagOnOwnLine ? lineStart : tagStart;
                tokens.push_back(textNode);
            }
        }
        
        // 解析Tag
        std::string tagContent = match[1].str();
        auto tagNode = parseTag(tagContent, tagStart, tagEnd);
        if (tagNode) {
            tagNode->tag_content = match[0].str();
            tagNode->is_on_own_line = tagOnOwnLine;
            tokens.push_back(tagNode);
        }
        
        // 如果标签独占一行，跳过后面的换行符
        lastPos = tagOnOwnLine ? lineEnd : tagEnd;
        ++iter;
    }
    
    // 添加最后的文本
    if (lastPos < content.length()) {
        auto textNode = std::make_shared<TemplateToken>(TokenType::TEXT);
        std::string text = content.substr(lastPos);
        
        if (!text.empty()) {
            textNode->outer_content = text;
            textNode->start_pos = lastPos;
            textNode->end_pos = content.length();
            tokens.push_back(textNode);
        }
    }
    
    return tokens;
}

std::shared_ptr<TemplateToken> TemplateEngine::parseTag(const std::string& tagContent, size_t start, size_t end) {
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
        auto node = std::make_shared<TemplateToken>(TokenType::ELSE);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    } else if (trimmed == "endif") {
        // 条件结束 <%endif%>
        auto node = std::make_shared<TemplateToken>(TokenType::END_IF);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    } else if (trimmed.substr(0, 7) == "foreach") {
        // 循环语句 <%foreach collection as item%>
        return parseForeachTag(trimmed, start, end);
    } else if (trimmed == "endforeach") {
        // 循环结束 <%endforeach%>
        auto node = std::make_shared<TemplateToken>(TokenType::END_FOREACH);
        node->start_pos = start;
        node->end_pos = end;
        return node;
    }

    throw std::runtime_error("invalid tag [" + std::to_string(start) + ", " + std::to_string(end) + "] " + tagContent);
    
    return nullptr;
}

std::shared_ptr<TemplateToken> TemplateEngine::parseVariableTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TemplateToken>(TokenType::VARIABLE);
    node->variable_name = trimWhitespace(tagContent);
    node->start_pos = start;
    node->end_pos = end;
    return node;
}

std::shared_ptr<TemplateToken> TemplateEngine::parseFunctionCallTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TemplateToken>(TokenType::FUNCTION_CALL);
    
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

std::shared_ptr<TemplateToken> TemplateEngine::parseMiscCallTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TemplateToken>(TokenType::MISC_CALL);
    
    // 提取misc名称 "call misc_name"
    std::string miscPart = trimWhitespace(tagContent.substr(4)); // 跳过"call"
    node->misc_name = miscPart;
    node->start_pos = start;
    node->end_pos = end;
    
    return node;
}

std::shared_ptr<TemplateToken> TemplateEngine::parseIfTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TemplateToken>(TokenType::IF);
    
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

std::shared_ptr<TemplateToken> TemplateEngine::parseForeachTag(const std::string& tagContent, size_t start, size_t end) {
    auto node = std::make_shared<TemplateToken>(TokenType::FOREACH);
    
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

nlohmann::json TemplateEngine::getVarValue(const std::string &varName, const TemplateVars &vars)
{
    if (varName.empty()) {
        return nlohmann::json();
    }
    if (varName == "true") {
        return true;
    }
    if (varName == "false") {
        return false;
    }
    
    // 如果是数字则直接返回
    if (isdigit(varName[0])) {
        return std::stoi(varName);
    }

    // 循环访问属性，不支持数组，可访问 a.b.c.d 这样的属性
    nlohmann::json result = vars;
    std::vector<std::string> parts = splitString(varName, '.');
    for (const auto &part : parts) {
        if (!result.is_object()) {
            std::cerr << "Error: " << varName << " is not an object" << std::endl;
            return nlohmann::json();
        
        }
        if (result.contains(part)) {
            result = result[part];
        } else {
            std::cerr << "Error: " << varName << " not found" << std::endl;
            return nlohmann::json();
        }
    }
    return result;
}

std::vector<std::shared_ptr<TagNode>> TemplateEngine::buildTagTree(const std::string& templateContent, const std::vector<std::shared_ptr<TemplateToken>>& tokens) {
    std::vector<std::shared_ptr<TagNode>> result;
    size_t i = 0;
    
    while (i < tokens.size()) {
        auto token = tokens[i];
        
        if (token->type == TokenType::IF) {
            // 解析if块的内容
            size_t level = 1;
            size_t elseIndex = SIZE_MAX;
            size_t endIndex = SIZE_MAX;
            
            // 查找匹配的endif和else
            for (size_t j = i + 1; j < tokens.size(); ++j) {
                if (tokens[j]->type == TokenType::IF) {
                    level++;
                } else if (tokens[j]->type == TokenType::END_IF) {
                    level--;
                    if (level == 0) {
                        endIndex = j;
                        break;
                    }
                } else if (tokens[j]->type == TokenType::ELSE && level == 1) {
                    if (elseIndex != SIZE_MAX) {
                        std::cerr << "Error: " << tokens[j]->tag_content << std::endl;
                        std::cerr << "Duplicate else tag" << std::endl;
                        return result;
                    }
                    elseIndex = j;
                }
            }
            
            if (endIndex == SIZE_MAX) {
                std::cerr << "Unmatched if tag" << std::endl;
                return result;
            }
            
            // 创建if节点并设置内容
            auto ifNode = std::make_shared<TagNode>(TokenType::IF);
            ifNode->start_pos = token->start_pos;
            ifNode->end_pos = tokens[endIndex]->end_pos;
            ifNode->condition = token->condition;

            // 从token序列中重建内容，而不是直接从原始内容提取
            std::string innerContent;
            std::string elseContent;
            
            size_t contentStart = i + 1;
            size_t contentEnd = (elseIndex == SIZE_MAX) ? endIndex : elseIndex;
            size_t elseStart = (elseIndex == SIZE_MAX) ? SIZE_MAX : elseIndex + 1;
            
            // 构建if块内容
            for (size_t k = contentStart; k < contentEnd; k++) {
                if (tokens[k]->type == TokenType::TEXT) {
                    innerContent += tokens[k]->outer_content;
                } else {
                    innerContent += tokens[k]->tag_content;
                }
            }
            
            // 构建else块内容
            if (elseIndex != SIZE_MAX) {
                for (size_t k = elseStart; k < endIndex; k++) {
                    if (tokens[k]->type == TokenType::TEXT) {
                        elseContent += tokens[k]->outer_content;
                    } else {
                        elseContent += tokens[k]->tag_content;
                    }
                }
            }
            
            ifNode->inner_text = innerContent;
            ifNode->else_text = elseContent;
            
            result.push_back(ifNode);
            i = endIndex + 1; // 跳过整个if块
        } else if (token->type == TokenType::FOREACH) {
            // 解析foreach块的内容
            size_t level = 1;
            size_t endIndex = SIZE_MAX;
            
            // 查找匹配的endforeach
            for (size_t j = i + 1; j < tokens.size(); ++j) {
                if (tokens[j]->type == TokenType::FOREACH) {
                    level++;
                } else if (tokens[j]->type == TokenType::END_FOREACH) {
                    level--;
                    if (level == 0) {
                        endIndex = j;
                        break;
                    }
                }
            }
            
            if (endIndex == SIZE_MAX) {
                std::cerr << "Unmatched foreach tag" << std::endl;
                return result;
            }
            
            // 创建foreach节点并设置内容
            auto foreachNode = std::make_shared<TagNode>(TokenType::FOREACH);
            foreachNode->start_pos = token->start_pos;
            foreachNode->end_pos = tokens[endIndex]->end_pos;
            foreachNode->collection = token->collection;
            foreachNode->item_name = token->item_name;
            
            // 从token序列中重建内容，而不是直接从原始内容提取
            std::string innerContent;
            for (size_t k = i + 1; k < endIndex; k++) {
                if (tokens[k]->type == TokenType::TEXT) {
                    innerContent += tokens[k]->outer_content;
                } else {
                    innerContent += tokens[k]->tag_content;
                }
            }
            foreachNode->inner_text = innerContent;
            
            result.push_back(foreachNode);
            i = endIndex + 1; // 跳过整个foreach块
            
        } else if (token->type == TokenType::ELSE || token->type == TokenType::END_IF || token->type == TokenType::END_FOREACH) {
            // 这些标签应该在上面的逻辑中处理，如果到这里说明有语法错误
            std::cerr << "Unexpected tag: " << static_cast<int>(token->type) << std::endl;
            i++;
        } else if (token->type == TokenType::VARIABLE) {
            auto node = std::make_shared<TagNode>(TokenType::VARIABLE);
            node->start_pos = token->start_pos;
            node->end_pos = token->end_pos;
            node->variable_name = token->variable_name;
            result.push_back(node);
            i++;
        } else if (token->type == TokenType::FUNCTION_CALL) {
            auto node = std::make_shared<TagNode>(TokenType::FUNCTION_CALL);
            node->start_pos = token->start_pos;
            node->end_pos = token->end_pos;
            node->function_name = token->function_name;
            node->function_args = token->function_args;
            result.push_back(node);
            i++;
        } else if (token->type == TokenType::MISC_CALL) {
            auto node = std::make_shared<TagNode>(TokenType::MISC_CALL);
            node->start_pos = token->start_pos;
            node->end_pos = token->end_pos;
            node->misc_name = token->misc_name;
            result.push_back(node);
            i++;
        } else {
            // 普通标签或文本
            auto node = std::make_shared<TagNode>(TokenType::TEXT);
            node->start_pos = token->start_pos;
            node->end_pos = token->end_pos;
            node->inner_text = token->outer_content;
            result.push_back(node);
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
        case TokenType::TEXT:
            return node->inner_text;

        case TokenType::VARIABLE:
            return renderVariable(node->variable_name, vars);

        case TokenType::FUNCTION_CALL:
            return renderFunctionCall(node->function_name, node->function_args, vars);
            
        case TokenType::MISC_CALL:
            return renderMiscCall(node->misc_name, vars);
            
        case TokenType::IF:
            return renderIfBlock(node, vars);
            
        case TokenType::FOREACH:
            return renderForeachBlock(node, vars);
            
        case TokenType::ELSE:
        case TokenType::END_IF:
        case TokenType::END_FOREACH:
            // 结束标签和else标签不应该单独渲染
            return "";
            
        default:
            return "";
    }
}

std::string TemplateEngine::renderVariable(const std::string& varName, const TemplateVars& vars) {
    try {
        auto result =  getVarValue(varName, vars);
        if (result.is_string()) {
            return result.get<std::string>();
        } else if (result.is_number()) {
            return std::to_string(result.get<int>());
        } else if (result.is_boolean()) {
            return result.get<bool>() ? "true" : "false";
        } else if (result.is_null()) {
            return "";
        } else {
            return result.dump(4);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}

std::string TemplateEngine::renderFunctionCall(const std::string& funcName, const std::string& args, const TemplateVars& vars) {
    // 解析参数列表，支持多个参数
    std::vector<std::string> parsedArgs = parseArguments(args);
    
    // 对每个参数进行求值，支持嵌套函数调用和变量引用
    std::vector<nlohmann::json> evaluatedArgs;
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
        return renderContent(ifNode->inner_text, vars);
    } else {
        // 渲染else分支
        return renderContent(ifNode->else_text, vars);
    }
}

std::string TemplateEngine::renderForeachBlock(const std::shared_ptr<TagNode>& foreachNode, const TemplateVars& vars) {
    // 查找集合数据
    auto collection = getVarValue(foreachNode->collection, vars);
    if (collection.empty()) {
        return "";
    }
    
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
            
            // 添加是否为第一个/最后一个的标志
            itemVars["is_first"] = (i == 0);
            itemVars["is_last"] = (i == jsonArray.size() - 1);
            
            // 重新解析并渲染foreach块的内容
            result += renderContent(foreachNode->inner_text, itemVars);
        }
    }
    
    return result;
}

bool TemplateEngine::evaluateCondition(const std::string& condition, const TemplateVars& vars) {
    // 检查相等条件
    size_t eqPos = condition.find("==");
    if (eqPos != std::string::npos) {
        std::string left = condition.substr(0, eqPos);
        std::string right = condition.substr(eqPos + 2);
        
        try {
        // 使用 evaluateExpression 执行等号两侧的表达式
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
            
            // 比较结果
            return leftValue == rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    size_t notPos = condition.find("!=");
    if (notPos != std::string::npos) {
        std::string left = condition.substr(0, notPos);
        std::string right = condition.substr(notPos + 2);
        
        try {
            // 使用 evaluateExpression 执行不等号两侧的表达式
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
        
            // 比较结果
            return leftValue != rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return true;
        }
    }

    size_t gtPos = condition.find(">");
    if (gtPos != std::string::npos) {
        std::string left = condition.substr(0, gtPos);
        std::string right = condition.substr(gtPos + 1);
        
        try {
            // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
        
            // 比较结果
            return leftValue > rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    size_t ltPos = condition.find("<");
    if (ltPos != std::string::npos) {
        std::string left = condition.substr(0, ltPos);
        std::string right = condition.substr(ltPos + 1);
        
        try {
            // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
        
            // 比较结果
            return leftValue < rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    size_t gtePos = condition.find(">=");
    if (gtePos != std::string::npos) {
        std::string left = condition.substr(0, gtePos);
        std::string right = condition.substr(gtePos + 2);
        
        try {
            // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
        
        // 比较结果
        return leftValue >= rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    size_t ltePos = condition.find("<=");
    if (ltePos != std::string::npos) {
        std::string left = condition.substr(0, ltePos);
        std::string right = condition.substr(ltePos + 2);
        
        try {
            // 使用 evaluateExpression 执行不等号两侧的表达式，并转为数字
            auto leftValue = evaluateExpression(left, vars);
            auto rightValue = evaluateExpression(right, vars);
        
        // 比较结果
        return leftValue <= rightValue;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
    }

    // 检查变量存在性
    std::string varName = trimWhitespace(condition);
    
    const auto& value = evaluateExpression(varName, vars);
    if (value.is_boolean()) {
        return value.get<bool>();
    } else if (value.is_string()) {
        std::string strValue = value.get<std::string>();
        return !strValue.empty() && strValue != "false";
    } else if (value.is_null()) {
        return false;
    } else if (value.is_number()) {
        return value.get<int>() != 0;
    }
    
    return true;
}

std::string TemplateEngine::callMisc(const std::string& miscName, const TemplateVars& vars) {
    std::string miscContent = loadMisc(miscName);
    if (miscContent.empty()) {
        return "[MISSING_MISC:" + miscName + "]";
    }
    
    // 递归渲染misc内容
    std::string result = renderContent(miscContent, vars);
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
    // 如果有Generator引用，使用Generator的mapType方法（包含声明注册表查询）
    if (generator_) {
        return generator_->mapType(motaType);
    }
    
    // 否则使用传统的类型映射
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

nlohmann::json TemplateEngine::evaluateExpression(const std::string& expr, const TemplateVars& vars) {
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

        std::vector<std::string> parsedArgs = parseArguments(funcArgs);
    
        // 对每个参数进行求值，支持嵌套函数调用和变量引用
        std::vector<nlohmann::json> evaluatedArgs;
        for (const auto& arg : parsedArgs) {
            evaluatedArgs.push_back(evaluateExpression(arg, vars));
        }
    
    // 调用内置函数
    return callBuiltinFunction(funcName, evaluatedArgs, vars);
    }
    
    return getVarValue(trimmedExpr, vars);
}

nlohmann::json TemplateEngine::callBuiltinFunction(const std::string& funcName, const std::vector<nlohmann::json>& args, const TemplateVars& vars) {
    // 单参数函数
    if (args.size() == 1) {
        const auto& arg = args[0];
        
        if (funcName == "pascal_case") {
            return toPascalCase(arg.get<std::string>());
        } else if (funcName == "camel_case") {
            return toCamelCase(arg.get<std::string>());
        } else if (funcName == "map_type") {
            return mapType(arg.get<std::string>());
        } else if (funcName == "is_base_type") {
            return generator_->isBuiltinType(arg.get<std::string>());
        } else if (funcName == "escape_string") {
            return escapeString(arg.get<std::string>());
        } else if (funcName == "first_namespace_part") {
            return getFirstNamespacePart(arg.get<std::string>());
        } else if (funcName == "has_nested_namespace") {
            return hasNestedNamespace(arg.get<std::string>()) ? "true" : "false";
        } else if (funcName == "namespace_path") {
            return formatNamespacePath(arg.get<std::string>());
        } else if (funcName == "as_string") {
            if (arg.is_number()) {
                return std::to_string(arg.get<int>());
            } else if (arg.is_boolean()) {
                return arg.get<bool>() ? "true" : "false";
            } else if (arg.is_null()) {
                return "null";
            } else if (arg.is_string()) {
                return arg.get<std::string>();
            } else {
                return arg.dump();
            }
        } else if (funcName == "reverse") {
            nlohmann::json result = arg;
            if (result.is_array()) {
                std::reverse(result.begin(), result.end());
            } else if (result.is_string()) {
                std::reverse(result.begin(), result.end());
            } else {
                return arg;
            }
            return result;
        } else if (funcName == "length" || funcName == "size" || funcName == "count") {
            if (arg.is_array()) {
                return arg.size();
            } else if (arg.is_string()) {
                return arg.get<std::string>().size();
            } else if (arg.is_object()) {
                return arg.size();
            } else if (arg.is_null()) {
                return 0;
            } else {
                return 1;
            }
        } else if (funcName == "basename") {
            // 提取文件名（不包含路径和扩展名）
            std::string filename = arg.get<std::string>();
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
        const nlohmann::json& arg1 = args[0];
        const nlohmann::json& arg2 = args[1];
        
        if (funcName == "join") {
            // join(separator, array_var_name)
            std::string separator = arg1.get<std::string>();
            nlohmann::json array = arg2;
            if (array.is_array()) {
                std::string result;
                const auto& jsonArray = array;
                for (size_t i = 0; i < jsonArray.size(); ++i) {
                    if (i > 0) {
                        result += arg1.get<std::string>();
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
            std::string result = arg1.get<std::string>();
            std::string oldPattern = arg2.get<std::string>();
            std::string newPattern = args.size() > 2 ? args[2] : "";
            
            size_t pos = 0;
            while ((pos = result.find(oldPattern, pos)) != std::string::npos) {
                result.replace(pos, oldPattern.length(), newPattern);
                pos += newPattern.length();
            }
            return result;
        } else if (funcName == "repeat") {
            // repeat(string, count)
            std::string result = "";
            int count = arg2.get<int>();
            for (int i = 0; i < count; ++i) {
                result += arg1.get<std::string>();
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