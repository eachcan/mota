#pragma once

#include "ast.h"
#include <string>
#include <vector>
#include <set>
#include <map>

namespace mota {
namespace checker {

// 单条语法诊断信息
struct SyntaxDiagnostic {
    enum class Level {
        Error,
        Warning,
        Info
    };
    Level level;
    std::string message;
    std::string file;
    uint32_t line = 0;
    uint32_t column = 0;
};

// 语法检查器
class SyntaxChecker {
public:
    // 对文档进行语法检查，返回所有诊断信息
    std::vector<SyntaxDiagnostic> check(const ast::Document& doc, const std::string& entryFile = "");
    
    // 对文档进行语法检查，使用外部提供的注解定义
    std::vector<SyntaxDiagnostic> checkWithExternalAnnotations(const ast::Document& doc, const std::string& entryFile, const std::set<std::string>& externalAnnotations);
};

} // namespace checker
} // namespace mota 