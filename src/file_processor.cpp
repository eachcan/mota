#include "file_processor.h"
#include "parser.h"
#include "lexer.h"
#include "generator.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

// ANSI颜色代码
namespace Colors {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string BOLD_RED = "\033[1;31m";
    const std::string BOLD_GREEN = "\033[1;32m";
    const std::string BOLD_BLUE = "\033[1;34m";
}

namespace mota {
namespace processor {

std::string getDeclType(const ast::NodeType& type) {
    if (type == ast::NodeType::Annotation) {
        return "Annotation";
    } else if (type == ast::NodeType::StructDecl) {
        return "Struct";
    } else if (type == ast::NodeType::EnumDecl) {
        return "Enum";
    } else if (type == ast::NodeType::BlockDecl) {
        return "Block";
    } else if (type == ast::NodeType::AnnotationDecl) {
        return "AnnotationDecl";
    } 
    return "Unknown";
}

bool FileProcessor::processMotaFile(
    const std::string& inputFile,
    const std::string& outputDir,
    const std::string& templateDir,
    const std::vector<std::string>& includePaths,
    bool verbose) {
    
    if (!verbose) {
        std::cout << Colors::BLUE << "Processing: " << Colors::RESET << inputFile << std::endl;
    } else {
        std::cout << "处理文件: " << inputFile << std::endl;
        std::cout << "输出目录: " << outputDir << std::endl;
        std::cout << "模板目录: " << templateDir << std::endl;
    }
    
    try {
        // 读取主文件
        std::string source = readFile(inputFile);
        if (source.empty()) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "无法读取文件 " << inputFile << std::endl;
            return false;
        }
        
        // 解析主文件
        auto root = parseFile(inputFile);
        if (!root) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "解析文件失败 " << inputFile << std::endl;
            return false;
        }
        
        // 构建包含注册表
        std::set<std::string> includedFiles = {fs::absolute(inputFile).string()};
        std::map<std::string, checker::KnownDecl> includedDeclarations;
        std::map<std::string, checker::KnownDecl> currentDeclarations;
        
        if (!buildIncludeRegistry(*root, inputFile, includedFiles, includePaths, includedDeclarations, verbose)) {
            return false;
        }
        
        checker::SyntaxChecker syntaxChecker;
        auto diagnostics = syntaxChecker.check(*root, inputFile, includedDeclarations, currentDeclarations);
        
        if (!diagnostics.empty()) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "在文件 " << inputFile << " 中发现语法错误:" << std::endl;
            for (const auto& diagnostic : diagnostics) {
                std::cerr << "  [" << diagnostic.line << ":" << diagnostic.column << "] " 
                         << diagnostic.message << std::endl;
            }
            return false;
        }
        
        if (verbose) {
            std::cout << "语法检查通过，初始化生成器..." << std::endl;
        }
        
        // 模板引擎生成
        generator::Generator generator;
        if (!generator.initialize(templateDir)) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "生成器初始化失败，模板目录: " << templateDir << std::endl;
            return false;
        }
        
        if (verbose) {
            std::cout << "生成器初始化成功，开始生成代码..." << std::endl;
        }
        
        // 构建声明注册表
        if (verbose) {
            std::cout << "[DEBUG] 开始构建声明注册表..." << std::endl;
        }
        DeclarationRegistry declarationRegistry;
        buildDeclarationRegistry(includedDeclarations, currentDeclarations, declarationRegistry, generator.getConfig());
        if (verbose) {
            std::cout << "[DEBUG] 声明注册表构建完成，包含 " << declarationRegistry.size() << " 个声明" << std::endl;
        }
        
        // 设置声明注册表到生成器
        if (verbose) {
            std::cout << "[DEBUG] 开始设置声明注册表..." << std::endl;
        }
        generator.setDeclarationRegistry(declarationRegistry);
        if (verbose) {
            std::cout << "[DEBUG] 声明注册表设置完成" << std::endl;
        }
        
        generator.setCurrentNamespace(root->hasNamespace() ? 
            [&]() {
                std::string ns;
                for (size_t i = 0; i < root->m_namespace->name.size(); ++i) {
                    if (i > 0) ns += ".";
                    ns += root->m_namespace->name[i];
                }
                return ns;
            }() : "");
        if (verbose) {
            std::cout << "[DEBUG] 命名空间设置完成" << std::endl;
        }
        
        if (verbose) {
            std::cout << "[DEBUG] 准备获取配置..." << std::endl;
        }
        auto filePaths = generator.getConfig().file_path;
        if (verbose) {
            std::cout << "[DEBUG] 配置获取成功" << std::endl;
            std::cout << "[DEBUG] 找到 " << filePaths.size() << " 个文件路径配置" << std::endl;
        }
        
        for (const auto& filePath : filePaths) {
            if (verbose) {
                std::cout << "[DEBUG] 处理文件路径: " << filePath.entry << std::endl;
            }
            std::string generatedCode = generator.generateCode(root, filePath.entry, verbose);
            if (verbose) {
                std::cout << "[DEBUG] generateCode 返回，长度: " << generatedCode.length() << std::endl;
            }
            if (generatedCode.empty()) {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "代码生成失败 " << inputFile << std::endl;
                return false;
            }

            // 提取命名空间信息
            std::string namespaceStr = "";
            if (root->hasNamespace()) {
                for (size_t i = 0; i < root->m_namespace->name.size(); ++i) {
                    if (i > 0) namespaceStr += filePath.namespace_separator;
                    namespaceStr += root->m_namespace->name[i];
                }
            }

            auto vars = nlohmann::json::object();
            vars["NAMESPACE"] = nlohmann::json::object();
            vars["NAMESPACE"]["path"] = namespaceStr;
            vars["SOURCE_FILE"] = inputFile;
            vars["INCLUDE_PATH"] = nlohmann::json::object();
            vars["INCLUDE_PATH"]["path"] = includePaths;
            vars["INCLUDE_PATH"]["path"] = includePaths;
            
            auto outputFilePath = generator.getTemplateEngine().renderContent(filePath.path, vars);
            #ifdef _WIN32
            if (outputFilePath[1] != ':') {
                outputFilePath = outputDir + "/" + outputFilePath;
            }
            #else
            if (outputFilePath[0] != '/') {
                outputFilePath = outputDir + "/" + outputFilePath;
            }
            #endif
            
            // 确保输出目录存在
            fs::create_directories(fs::path(outputFilePath).parent_path());
            
            // 写入生成的代码
            std::ofstream outFile(outputFilePath);
            if (!outFile.is_open()) {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "无法创建输出文件 " << outputFilePath << std::endl;
                return false;
            }
            
            outFile << generatedCode;
            outFile.close();
            if (!verbose) {
                std::cout << Colors::BOLD << "Generated: " << Colors::RESET << outputFilePath << std::endl;
            } else {
                std::cout << "已生成到: " << outputFilePath << std::endl;
            }
        }
        
        if (verbose) {
            std::cout << "生成完成: " << root->location.filename << std::endl;
        }
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "未知异常" << std::endl;
        return false;
    }
}

bool FileProcessor::buildIncludeRegistry(
    const ast::Document& root,
    const std::string& rootFile,
    std::set<std::string>& includedFiles,
    const std::vector<std::string>& includePaths,
    std::map<std::string, checker::KnownDecl>& includedDeclarations,
    bool verbose) {
    
    // 获取直接包含的文件
    auto directIncludes = getDirectIncludes(root);
    
    for (const auto& includeFilePath : directIncludes) {
        std::string currentFileDir = fs::path(rootFile).parent_path().string();
        std::string absoluteIncludePath = getAbsolutePath(includeFilePath, includePaths, currentFileDir);
        
        if (absoluteIncludePath.empty()) {
            if (verbose) {
                std::cout << "警告: 无法找到包含文件 " << includeFilePath << std::endl;
            }
            continue;
        }
        
        // 检查是否已经处理过
        if (includedFiles.find(absoluteIncludePath) != includedFiles.end()) {
            continue;
        }
        
        // 标记为已处理，避免重复处理
        includedFiles.insert(absoluteIncludePath);
        
        if (verbose) {
            std::cout << "处理包含文件: " << absoluteIncludePath << std::endl;
        }
        
        // 解析包含的文档
        auto doc = parseFile(absoluteIncludePath);
        if (!doc) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "解析包含文件失败 " << absoluteIncludePath << std::endl;
            return false;
        }
        
        // 递归处理下级包含
        std::map<std::string, checker::KnownDecl> nextIncludeDeclarations;
        if (!buildIncludeRegistry(*doc, absoluteIncludePath, includedFiles, includePaths, nextIncludeDeclarations, verbose)) {
            return false; // 递归调用失败，直接返回
        }
        
        // 对包含的文档进行语法检查
        // 需要将当前已收集的声明和下级包含的声明合并后传递给语法检查
        std::map<std::string, checker::KnownDecl> allAvailableDeclarations = includedDeclarations;
        mergeDeclarations(allAvailableDeclarations, nextIncludeDeclarations);
        
        checker::SyntaxChecker syntaxChecker;
        std::map<std::string, checker::KnownDecl> docDeclarations;
        auto diagnostics = syntaxChecker.check(*doc, absoluteIncludePath, allAvailableDeclarations, docDeclarations);
        
        if (!diagnostics.empty()) {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "在包含文件 " << absoluteIncludePath << " 中发现语法错误:" << std::endl;
            for (const auto& diagnostic : diagnostics) {
                std::cerr << "  [" << diagnostic.line << ":" << diagnostic.column << "] " 
                         << diagnostic.message << std::endl;
            }
            return false; // 发现语法错误，返回失败
        }
        
        // 合并声明到上级
        mergeDeclarations(includedDeclarations, nextIncludeDeclarations);
        mergeDeclarations(includedDeclarations, docDeclarations);
    }
    
    return true; // 成功处理所有包含文件
}

std::string FileProcessor::readFile(const std::string& filePath) const {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }
    
    return std::string(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

std::shared_ptr<ast::Document> FileProcessor::parseFile(const std::string& filePath) const {
    std::string source = readFile(filePath);
    if (source.empty()) {
        return nullptr;
    }
    
    try {
        lexer::Lexer lexer(source, filePath);
        parser::Parser parser(lexer);
        auto doc = parser.parse();
        doc->location.filename = filePath;
        return doc;
    } catch (const std::exception& e) {
        std::cerr << "解析错误 " << filePath << ": " << e.what() << std::endl;
        return nullptr;
    }
}

std::vector<std::string> FileProcessor::getDirectIncludes(const ast::Document& doc) const {
    std::vector<std::string> includes;
    
    for (const auto& include : doc.includes) {
        includes.push_back(include->path);
    }
    
    return includes;
}

std::string FileProcessor::getAbsolutePath(
    const std::string& includeFilePath,
    const std::vector<std::string>& includePaths,
    const std::string& currentFileDir) const {

    bool isAbsolute = false;
    #ifdef _WIN32
        isAbsolute = includeFilePath.find(':') != std::string::npos;
    #else
        isAbsolute = includeFilePath.find('/') == 0;
    #endif

    if (isAbsolute) {
        if (fs::exists(includeFilePath)) {
            return fs::absolute(includeFilePath).string();
        }
        return "";
    }

    // 首先尝试相对于当前文件的路径
    fs::path relativePath = fs::path(currentFileDir) / includeFilePath;
    if (fs::exists(relativePath)) {
        return fs::absolute(relativePath).string();
    }
    
    // 然后尝试命令行指定的include路径
    for (const auto& includeDir : includePaths) {
        fs::path candidatePath = fs::path(includeDir) / includeFilePath;
        if (fs::exists(candidatePath)) {
            return fs::absolute(candidatePath).string();
        }
    }
    
    // 默认的mota-include目录查找
    std::vector<std::string> defaultIncludePaths = {
        "mota-include",  // 当前工作目录的mota-include
        "./mota-include", // 显式当前目录
        "../mota-include" // 上级目录的mota-include
    };
    
    // 获取可执行文件目录，添加更多默认路径
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        fs::path exePath(buffer);
        std::string exeDir = exePath.parent_path().string();
        
        defaultIncludePaths.push_back(exeDir + "/mota-include");
        defaultIncludePaths.push_back(exeDir + "/../mota-include");
        defaultIncludePaths.push_back(exeDir + "/mota-install/mota-include");
    #endif
    
    for (const auto& defaultPath : defaultIncludePaths) {
        fs::path candidatePath = fs::path(defaultPath) / includeFilePath;
        if (fs::exists(candidatePath)) {
            return fs::absolute(candidatePath).string();
        }
    }
    
    // 最后尝试绝对路径
    if (fs::exists(includeFilePath)) {
        return fs::absolute(includeFilePath).string();
    }
    
    return "";
}

void FileProcessor::mergeDeclarations(
    std::map<std::string, checker::KnownDecl>& target,
    const std::map<std::string, checker::KnownDecl>& source) const {
    
    for (const auto& pair : source) {
        // 如果声明完全一样则可以忽略（已存在的优先）
        auto existing = target.find(pair.first);
        if (existing == target.end()) {
            target[pair.first] = pair.second;
        }
        // 如果已存在，我们保持原有的，不覆盖
    }
}

void FileProcessor::buildDeclarationRegistry(
    const std::map<std::string, checker::KnownDecl>& includedDeclarations,
    const std::map<std::string, checker::KnownDecl>& currentDeclarations,
    DeclarationRegistry& registry,
    const config::TemplateConfig& config) {
    
    auto buildDeclarationInfo = [](const std::string& qualifiedName, const checker::KnownDecl& knownDecl, 
                                  const std::string& prefix, const std::string& suffix) -> DeclarationInfo {
        DeclarationInfo info;
        info.name = knownDecl.name;
        info.qualified_name = qualifiedName;
        info.namespace_name = knownDecl.namespaceName;
        info.file_path = knownDecl.file;
        info.node = knownDecl.node;
        
        // 根据节点类型设置声明类型和类名
        switch (knownDecl.type) {
            case ast::NodeType::StructDecl:
                info.type = "struct";
                info.class_name = prefix + knownDecl.name + suffix;
                break;
            case ast::NodeType::BlockDecl:
                info.type = "block";
                info.class_name = prefix + knownDecl.name + suffix;
                break;
            case ast::NodeType::EnumDecl:
                info.type = "enum";
                info.class_name = prefix + knownDecl.name + suffix;
                break;
            case ast::NodeType::AnnotationDecl:
                info.type = "annotation_decl";
                info.class_name = prefix + knownDecl.name + suffix;
                
                // 提取注解字段信息
                if (knownDecl.node) {
                    const auto* annotationDecl = static_cast<const ast::AnnotationDecl*>(knownDecl.node.get());
                    for (const auto& field : annotationDecl->fields) {
                        DeclarationInfo::FieldInfo fieldInfo;
                        fieldInfo.name = field->name;
                        
                        // 提取类型信息
                        if (field->type->nodeType() == ast::NodeType::NamedType) {
                            const auto* namedType = static_cast<const ast::NamedType*>(field->type.get());
                            fieldInfo.type_name = namedType->name;
                            fieldInfo.container_type = "none";
                        } else if (field->type->nodeType() == ast::NodeType::ContainerType) {
                            const auto* containerType = static_cast<const ast::ContainerType*>(field->type.get());
                            if (containerType->elementType->nodeType() == ast::NodeType::NamedType) {
                                const auto* elementType = static_cast<const ast::NamedType*>(containerType->elementType.get());
                                fieldInfo.type_name = elementType->name;
                                switch (containerType->kind) {
                                    case ast::ContainerType::Kind::Array:
                                        fieldInfo.container_type = "array";
                                        break;
                                    case ast::ContainerType::Kind::Optional:
                                        fieldInfo.container_type = "optional";
                                        break;
                                    case ast::ContainerType::Kind::Map:
                                        fieldInfo.container_type = "map";
                                        break;
                                }
                            }
                        }
                        
                        // 提取默认值信息
                        if (field->defaultValue) {
                            fieldInfo.has_default_value = true;
                            // 这里可以根据需要提取默认值，暂时留空
                        }
                        
                        info.fields.push_back(fieldInfo);
                    }
                }
                break;
            default:
                break;
        }
        
        return info;
    };
    
    auto getPrefixSuffix = [&config](ast::NodeType type) -> std::pair<std::string, std::string> {
        switch (type) {
            case ast::NodeType::StructDecl:
                return {config.declaration_types.struct_decl.prefix, config.declaration_types.struct_decl.suffix};
            case ast::NodeType::BlockDecl:
                return {config.declaration_types.block_decl.prefix, config.declaration_types.block_decl.suffix};
            case ast::NodeType::EnumDecl:
                return {config.declaration_types.enum_decl.prefix, config.declaration_types.enum_decl.suffix};
            case ast::NodeType::AnnotationDecl:
                return {config.declaration_types.annotation_decl.prefix, config.declaration_types.annotation_decl.suffix};
            default:
                return {"", ""};
        }
    };
    
    // 处理包含的声明
    for (const auto& [qualifiedName, knownDecl] : includedDeclarations) {
        auto [prefix, suffix] = getPrefixSuffix(knownDecl.type);
        if (knownDecl.type == ast::NodeType::StructDecl || knownDecl.type == ast::NodeType::BlockDecl ||
            knownDecl.type == ast::NodeType::EnumDecl || knownDecl.type == ast::NodeType::AnnotationDecl) {
            auto info = buildDeclarationInfo(qualifiedName, knownDecl, prefix, suffix);
            registry[qualifiedName] = info;
        }
    }
    
    // 处理当前文档的声明
    for (const auto& [qualifiedName, knownDecl] : currentDeclarations) {
        auto [prefix, suffix] = getPrefixSuffix(knownDecl.type);
        if (knownDecl.type == ast::NodeType::StructDecl || knownDecl.type == ast::NodeType::BlockDecl ||
            knownDecl.type == ast::NodeType::EnumDecl || knownDecl.type == ast::NodeType::AnnotationDecl) {
            auto info = buildDeclarationInfo(qualifiedName, knownDecl, prefix, suffix);
            registry[qualifiedName] = info;
        }
    }
}

} // namespace processor  
} // namespace mota 