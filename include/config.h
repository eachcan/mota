#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include "ast.h"
#include <filesystem>

namespace mota {

class Config {
public:
    Config() = default;

    // 设置/获取搜索路径
    void addSearchPath(const std::string& path);
    std::vector<std::string> getSearchPaths() const { return searchPaths; }

    // 文件解析状态
    enum class FileState {
        NotParsed,
        Parsing,    // 用于检测循环引用
        Parsed
    };

    // 记录文件解析状态
    void setFileState(const std::string& filepath, FileState state) {
        fileStates[filepath] = state;
    }
    
    FileState getFileState(const std::string& filepath) const {
        auto it = fileStates.find(filepath);
        return it == fileStates.end() ? FileState::NotParsed : it->second;
    }

    // 类型注册和查找
    void registerType(const std::string& fullName, const std::string& kind, const std::string& sourceFile) {
        typeRegistry[fullName] = TypeInfo{kind, sourceFile};
    }
    
    bool isTypeRegistered(const std::string& fullName) const {
        return typeRegistry.find(fullName) != typeRegistry.end();
    }
    
    std::string getTypeKind(const std::string& fullName) const {
        auto it = typeRegistry.find(fullName);
        return it == typeRegistry.end() ? "" : it->second.kind;
    }
    
    std::string getTypeSourceFile(const std::string& fullName) const {
        auto it = typeRegistry.find(fullName);
        return it == typeRegistry.end() ? "" : it->second.sourceFile;
    }

private:
    std::vector<std::string> searchPaths;
    std::unordered_map<std::string, FileState> fileStates;
    
    struct TypeInfo {
        std::string kind;
        std::string sourceFile;
    };
    std::unordered_map<std::string, TypeInfo> typeRegistry;
};

}
