#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace mota {
namespace config {

// 文件路径配置
struct FilePathConfig {
    std::string path;
    std::string entry;
    std::string namespace_separator;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FilePathConfig, path, entry, namespace_separator)
};

// Include指令配置
struct IncludeDirectiveConfig {
    std::string pattern;
    std::string source_extension;
    std::string target_extension;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(IncludeDirectiveConfig, pattern, source_extension, target_extension)
};

// 声明前后缀配置
struct DeclarationPrefixSuffixConfig {
    std::string prefix = "";
    std::string suffix = "";
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DeclarationPrefixSuffixConfig, prefix, suffix)
};

// 声明类型配置
struct DeclarationTypesConfig {
    DeclarationPrefixSuffixConfig struct_decl;
    DeclarationPrefixSuffixConfig block_decl;
    DeclarationPrefixSuffixConfig enum_decl;
    DeclarationPrefixSuffixConfig annotation_decl;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DeclarationTypesConfig, struct_decl, block_decl, enum_decl, annotation_decl)
};

// 命名空间分隔符配置
struct NamespaceSeparatorConfig {
    std::string code = "::";
    std::string dir = "\\";
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NamespaceSeparatorConfig, code, dir)
};

// 命名空间配置
struct NamespaceConfig {
    NamespaceSeparatorConfig separator;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NamespaceConfig, separator)
};

// 模板配置类
class TemplateConfig {
public:
    std::string version;
    std::string encoding;
    std::unordered_map<std::string, std::string> templates;
    std::vector<std::string> miscs;
    std::unordered_map<std::string, std::string> type_mapping;
    std::string repeated_type_mapping_tpl;
    std::string map_type_mapping_tpl;
    NamespaceConfig namespace_config;
    std::vector<FilePathConfig> file_path;
    IncludeDirectiveConfig include_directive;
    DeclarationTypesConfig declaration_types;
    
    // 从JSON文件加载配置
    bool loadFromFile(const std::string& configPath);
    
    // 从JSON对象加载配置
    void loadFromJson(const nlohmann::json& json);
    
    // 转换为JSON
    nlohmann::json toJson() const;
    
private:
    void setDefaults();
};

// 编译器配置类
class CompilerConfig {
public:
    std::string output_dir = "output";
    std::string source_dir = ".";
    std::string language = "cpp";
    std::string template_dir;
    std::vector<std::string> include_paths;
    bool verbose = false;
    
    // 从JSON文件加载配置
    bool loadFromFile(const std::string& configPath);
    
    // 从JSON对象加载配置
    void loadFromJson(const nlohmann::json& json);
    
    // 转换为JSON
    nlohmann::json toJson() const;
    
    // 转换为JSON (用于序列化)
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompilerConfig, output_dir, source_dir, language, template_dir, include_paths, verbose)
    
private:
    void setDefaults();
};

} // namespace config
} // namespace mota 