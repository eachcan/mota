#include "config.h"
#include <fstream>
#include <iostream>

namespace mota {
namespace config {

bool TemplateConfig::loadFromFile(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Cannot open config file: " << configPath << std::endl;
        setDefaults();
        return false;
    }
    
    try {
        nlohmann::json json;
        file >> json;
        loadFromJson(json);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing config file: " << e.what() << std::endl;
        setDefaults();
        return false;
    }
}

void TemplateConfig::loadFromJson(const nlohmann::json& json) {
    // 加载基本配置
    if (json.contains("version")) {
        version = json["version"].get<std::string>();
    }
    
    if (json.contains("encoding")) {
        encoding = json["encoding"].get<std::string>();
    }
    
    // 加载模板映射
    if (json.contains("templates")) {
        templates = json["templates"].get<std::unordered_map<std::string, std::string>>();
    }
    
    // 加载misc文件列表
    if (json.contains("miscs")) {
        miscs = json["miscs"].get<std::vector<std::string>>();
    }
    
    // 加载类型映射
    if (json.contains("type_mapping")) {
        type_mapping = json["type_mapping"].get<std::unordered_map<std::string, std::string>>();
    }
    
    // 加载文件路径配置
    if (json.contains("file_path")) {
        file_path = json["file_path"].get<std::vector<FilePathConfig>>();
    }
    
    // 加载include指令配置
    if (json.contains("include_directive")) {
        include_directive = json["include_directive"].get<IncludeDirectiveConfig>();
    }
    
    // 加载声明类型配置
    if (json.contains("declaration_types")) {
        declaration_types = json["declaration_types"].get<DeclarationTypesConfig>();
    } else {
        // 设置默认值
        declaration_types.struct_decl.suffix = "Model";
        declaration_types.block_decl.suffix = "Block";
        declaration_types.enum_decl.suffix = "";
        declaration_types.annotation_decl.suffix = "Annotation";
    }
}

nlohmann::json TemplateConfig::toJson() const {
    nlohmann::json json;
    json["version"] = version;
    json["encoding"] = encoding;
    json["templates"] = templates;
    json["miscs"] = miscs;
    json["type_mapping"] = type_mapping;
    json["file_path"] = file_path;
    json["include_directive"] = include_directive;
    json["declaration_types"] = declaration_types;
    return json;
}

void TemplateConfig::setDefaults() {
    version = "2.0";
    encoding = "UTF-8";
    templates.clear();
    miscs.clear();
    type_mapping.clear();
    file_path.clear();
    include_directive = IncludeDirectiveConfig{};
    
    // 设置声明类型默认值
    declaration_types.struct_decl.suffix = "Model";
    declaration_types.block_decl.suffix = "Block";
    declaration_types.enum_decl.suffix = "";
    declaration_types.annotation_decl.suffix = "Annotation";
}

bool CompilerConfig::loadFromFile(const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Cannot open config file: " << configPath << std::endl;
        setDefaults();
        return false;
    }
    
    try {
        nlohmann::json json;
        file >> json;
        loadFromJson(json);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing config file: " << e.what() << std::endl;
        setDefaults();
        return false;
    }
}

void CompilerConfig::loadFromJson(const nlohmann::json& json) {
    if (json.contains("output_dir")) {
        output_dir = json["output_dir"].get<std::string>();
    }
    
    if (json.contains("source_dir")) {
        source_dir = json["source_dir"].get<std::string>();
    }
    
    if (json.contains("language")) {
        language = json["language"].get<std::string>();
    }
    
    if (json.contains("template_dir")) {
        template_dir = json["template_dir"].get<std::string>();
    }
    
    if (json.contains("include_paths")) {
        include_paths = json["include_paths"].get<std::vector<std::string>>();
    }
    
    if (json.contains("verbose")) {
        verbose = json["verbose"].get<bool>();
    }
}

nlohmann::json CompilerConfig::toJson() const {
    nlohmann::json json;
    json["output_dir"] = output_dir;
    json["source_dir"] = source_dir;
    json["language"] = language;
    json["template_dir"] = template_dir;
    json["include_paths"] = include_paths;
    json["verbose"] = verbose;
    return json;
}

void CompilerConfig::setDefaults() {
    output_dir = "output";
    source_dir = ".";
    language = "cpp";
    template_dir = "";
    include_paths.clear();
    verbose = false;
}

} // namespace config
} // namespace mota 