#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <regex>
#include <nlohmann/json.hpp>
#include "config.h"

namespace mota {

// 前向声明
namespace generator {
    class Generator;
}

namespace template_engine {

// 模板变量类型
using TemplateVars = nlohmann::json;

// Tag类型枚举
enum class TokenType {
    TEXT,           // 普通文本
    VARIABLE,       // 变量引用 <%=var%>
    FUNCTION_CALL,  // 函数调用 <%=func(arg)%>
    MISC_CALL,      // misc调用 <%call misc_name%>
    IF,             // 条件语句 <%if (condition)%>
    ELSE,           // else分支 <%else%>
    FOREACH,        // 循环语句 <%foreach collection as item%>
    END_IF,         // 条件结束 <%endif%>
    END_FOREACH     // 循环结束 <%endforeach%>
};

// Tag节点结构
struct TemplateToken {
    TokenType type;
    std::string inner_content;      // 标签内部内容
    std::string tag_content;            // 标签内容
    std::string outer_content;            // 整个标签的内容
    size_t start_pos;               // 在原文本中的起始位置 <%if 的开头
    size_t end_pos;                 // 在原文本中的结束位置 endif%> 的结尾
    
    // 特定于不同类型的属性
    std::string variable_name;      // 变量名
    std::string function_name;      // 函数名
    std::string function_args;      // 函数参数
    std::string misc_name;          // misc名称
    std::string condition;          // 条件表达式
    std::string collection;         // 集合变量名
    std::string item_name;          // 循环项变量名
    std::string else_content;       // else 分支的内容
    
    TemplateToken(TokenType t = TokenType::TEXT) : type(t), start_pos(0), end_pos(0) {}
};

struct TagNode {
    TokenType type;

    std::string inner_text; // TEXT 节点，或 IF / FOREACH 节点的内容
    std::string else_text; // IF 节点的 else 分支的内容
    size_t start_pos; // 整个标签的开始位置
    size_t end_pos; // 整个标签的结束位置

    // 特定于不同类型的属性
    std::string variable_name;      // 变量名
    std::string function_name;      // 函数名
    std::string function_args;      // 函数参数
    std::string misc_name;          // misc名称
    std::string condition;          // 条件表达式
    std::string collection;         // 集合变量名
    std::string item_name;          // 循环项变量名
    std::string else_content;       // else 分支的内容
};

// 模板引擎类
class TemplateEngine {
public:
    explicit TemplateEngine(const config::TemplateConfig& config, const std::string& templateDir);
    
    // 渲染模板
    std::string renderTemplate(const std::string& templateName, const TemplateVars& vars);
    
    // 直接渲染模板内容
    std::string renderContent(const std::string& templateContent, const TemplateVars& vars);
    
    // 获取模板配置
    const config::TemplateConfig& getConfig() const { return config_; }
    
    // 设置Generator引用（用于访问声明注册表）
    void setGenerator(generator::Generator* generator) { generator_ = generator; }
    
private:
    // 加载模板文件
    std::string loadTemplate(const std::string& templateName);
    
    // 加载misc片段
    std::string loadMisc(const std::string& miscName);
    
    // 第二步：确定普通文本和Tag的序列
    std::vector<std::shared_ptr<TemplateToken>> buildTokenSequence(const std::string& content);
    
    // 第三步：构建Tag树并检查成对标签
    std::vector<std::shared_ptr<TagNode>> buildTagTree(const std::string& templateContent, const std::vector<std::shared_ptr<TemplateToken>>& tokens);
    
    // 第四步：遍历渲染
    std::string renderTagTree(const std::vector<std::shared_ptr<TagNode>>& tree, const TemplateVars& vars);
    
    // 渲染单个Tag节点
    std::string renderTagNode(const std::shared_ptr<TagNode>& node, const TemplateVars& vars);
    
    // 解析Tag的通用方法
    std::shared_ptr<TemplateToken> parseTag(const std::string& tagContent, size_t start, size_t end);
    
    // 解析特定类型的Tag
    std::shared_ptr<TemplateToken> parseVariableTag(const std::string& tagContent, size_t start, size_t end);
    std::shared_ptr<TemplateToken> parseFunctionCallTag(const std::string& tagContent, size_t start, size_t end);
    std::shared_ptr<TemplateToken> parseMiscCallTag(const std::string& tagContent, size_t start, size_t end);
    std::shared_ptr<TemplateToken> parseIfTag(const std::string& tagContent, size_t start, size_t end);
    std::shared_ptr<TemplateToken> parseForeachTag(const std::string& tagContent, size_t start, size_t end);
    
    // 获得 Var 的值
    nlohmann::json getVarValue(const std::string& varName, const TemplateVars& vars);
    
    // 渲染特定类型的Tag
    std::string renderVariable(const std::string& varName, const TemplateVars& vars);
    std::string renderFunctionCall(const std::string& funcName, const std::string& args, const TemplateVars& vars);
    std::string renderMiscCall(const std::string& miscName, const TemplateVars& vars);
    std::string renderIfBlock(const std::shared_ptr<TagNode>& ifNode, const TemplateVars& vars);
    std::string renderForeachBlock(const std::shared_ptr<TagNode>& foreachNode, const TemplateVars& vars);
    
    // 增强的函数调用处理
    std::vector<std::string> parseArguments(const std::string& args);
    nlohmann::json evaluateExpression(const std::string& expr, const TemplateVars& vars);
    nlohmann::json callBuiltinFunction(const std::string& funcName, const std::vector<nlohmann::json>& args, const TemplateVars& vars);
    
    // 条件评估
    bool evaluateCondition(const std::string& condition, const TemplateVars& vars);
    
    // misc调用
    std::string callMisc(const std::string& miscName, const TemplateVars& vars);
    
    // 内置函数
    std::string toPascalCase(const std::string& str);
    std::string toCamelCase(const std::string& str);
    std::string mapType(const std::string& motaType);
    std::string escapeString(const std::string& str);

    std::string getFirstNamespacePart(const std::string& namespaceStr);
    bool hasNestedNamespace(const std::string& namespaceStr);
    std::string formatNamespacePath(const std::string& namespaceStr);
    
    // 工具函数
    std::string trimWhitespace(const std::string& str);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    
private:
    const config::TemplateConfig& config_;
    std::string templateDir_;
    std::unordered_map<std::string, std::string> templateCache_;
    std::unordered_map<std::string, std::string> miscCache_;
    generator::Generator* generator_ = nullptr; // 用于访问声明注册表
    bool is_loaded_misc_ = false;
};

} // namespace template_engine
} // namespace mota 