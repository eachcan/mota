#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <functional>
#include <nlohmann/json.hpp>
#include "parser.h"
#include "generator.h"
#include "syntax_checker.h"
#include <windows.h>

namespace fs = std::filesystem;
using json = nlohmann::json;

// 配置文件结构
struct ProjectConfig {
    std::string sourceDir;
    std::string outputDir;
    std::string lang;
};

struct ConfigFile {
    std::vector<std::string> includePaths;
    std::vector<ProjectConfig> projects;
};

struct Options {
    std::vector<std::string> includePaths;
    std::string outputDir = "output";
    std::string sourceDir = ".";
    std::string lang = "";
    std::string configPath;
    std::vector<std::string> files;
    bool showHelp = false;
    bool showVersion = false;
};

void showHelp() {
    std::cout << "mota [OPTIONS] [FILE] [...]" << std::endl;
    std::cout << std::endl;
    std::cout << "  mota 是一个配置文件编译器，类似于 Protocol Buffers，但主要用于配置文件描述类的编译。" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help      显示帮助信息" << std::endl;
    std::cout << "  -V, --version   显示版本信息" << std::endl;
    std::cout << "  -v, --verbose   显示详细信息" << std::endl;
    std::cout << "  -i, --include-path PATH" << std::endl;
    std::cout << "                  添加包含路径，可以指定多次。如果使用了 mota-config.json，本参数会在 mota-config.json 的 include_paths 基础上增加。" << std::endl;
    std::cout << "  -o, --output-dir PATH" << std::endl;
    std::cout << "                  设置输出目录，默认为 `output`，指定则忽略 -c 参数" << std::endl;
    std::cout << "  -s, --source-dir PATH" << std::endl;
    std::cout << "                  设置源文件目录，默认为当前目录，指定则忽略 -c 参数" << std::endl;
    std::cout << "  -l, --lang LANG" << std::endl;
    std::cout << "                  设置输出语言，可选值：cpp[默认]" << std::endl;
    std::cout << "  -c, --config PATH" << std::endl;
    std::cout << "                  设置配置文件路径。" << std::endl;
    std::cout << "                  本参数和 -o / -s / -l 互斥，配置文件中源文件和输出目录是可以多组的。" << std::endl;
    std::cout << "                  如果当前目录存在 mota-config.json，则会自动加载。" << std::endl;
    std::cout << std::endl;
    std::cout << "FILE" << std::endl;
    std::cout << "    指定要编译的 Mota 文件或目录路径，如果未指定，则从当前目录开始搜索，不会递归搜索。" << std::endl;
}

void showVersion() {
    std::cout << "mota version 1.0.0" << std::endl;
}

// 解析配置文件
ConfigFile parseConfigFile(const std::string& configPath) {
    ConfigFile config;
    
    std::ifstream file(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开配置文件: " + configPath);
    }
    
    try {
        json j;
        file >> j;
        
        // 解析 include_paths
        if (j.contains("include_paths") && j["include_paths"].is_array()) {
            for (const auto& path : j["include_paths"]) {
                if (path.is_string()) {
                    config.includePaths.push_back(path.get<std::string>());
                }
            }
        }
        
        // 解析 projects
        if (j.contains("projects") && j["projects"].is_array()) {
            for (const auto& project : j["projects"]) {
                if (project.is_object()) {
                    ProjectConfig projectConfig;
                    
                    if (project.contains("source_dir") && project["source_dir"].is_string()) {
                        projectConfig.sourceDir = project["source_dir"].get<std::string>();
                    }
                    
                    if (project.contains("output_dir") && project["output_dir"].is_string()) {
                        projectConfig.outputDir = project["output_dir"].get<std::string>();
                    }
                    
                    if (project.contains("lang") && project["lang"].is_string()) {
                        projectConfig.lang = project["lang"].get<std::string>();
                    }
                    
                    config.projects.push_back(projectConfig);
                }
            }
        }
        
    } catch (const json::exception& e) {
        throw std::runtime_error("配置文件格式错误: " + std::string(e.what()));
    }
    
    return config;
}

Options parseCommandLine(int argc, char* argv[]) {
    Options options;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
        } else if (arg == "-V" || arg == "--version") {
            options.showVersion = true;
        } else if (arg == "-i" || arg == "--include-path") {
            if (i + 1 < argc) {
                options.includePaths.push_back(argv[++i]);
            } else {
                std::cerr << "Error: " << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-o" || arg == "--output-dir") {
            if (i + 1 < argc) {
                options.outputDir = argv[++i];
            } else {
                std::cerr << "Error: " << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-s" || arg == "--source-dir") {
            if (i + 1 < argc) {
                options.sourceDir = argv[++i];
            } else {
                std::cerr << "Error: " << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-l" || arg == "--lang") {
            if (i + 1 < argc) {
                options.lang = argv[++i];
                if (options.lang != "cpp") {
                    std::cerr << "Error: Unsupported language: " << options.lang << std::endl;
                    std::cerr << "Currently supported languages: cpp" << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Error: " << arg << " requires a language argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-c" || arg == "--config") {
            if (i + 1 < argc) {
                options.configPath = argv[++i];
            } else {
                std::cerr << "Error: " << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg[0] != '-') {
            // FILE参数
            options.files.push_back(arg);
        } else {
            std::cerr << "Error: Unknown option: " << arg << std::endl;
            exit(1);
        }
    }
    
    return options;
}

std::vector<std::string> findMotaFiles(const std::string& directory) {
    std::vector<std::string> motaFiles;
    
    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".mota") {
                motaFiles.push_back(entry.path().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory " << directory << ": " << e.what() << std::endl;
    }
    
    return motaFiles;
}

std::string getExecutableDirectory() {
    // 获取可执行文件的完整路径
    char buffer[MAX_PATH];
    DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (length == 0) {
        return "."; // 如果获取失败，返回当前目录
    }
    
    // 提取目录部分
    fs::path exePath(buffer);
    return exePath.parent_path().string();
}

std::string findTemplateDirectory(const std::string& lang) {
    // 确定模板子目录名称
    std::string templateSubDir;
    if (lang.empty()) {
        templateSubDir = "yima-cpp";
    } else {
        templateSubDir = lang;
    }
    
    // 获取可执行文件所在目录
    std::string exeDir = getExecutableDirectory();
    
    // 候选路径列表：从可执行文件目录及其上级目录查找
    std::vector<std::string> candidatePaths = {
        // 当前工作目录的template目录（兼容性）
        ("template/" + templateSubDir),
        // 可执行文件同级的template目录
        (fs::path(exeDir) / "template" / templateSubDir).string(),
        // 可执行文件上级目录的template目录
        (fs::path(exeDir) / ".." / "template" / templateSubDir).string(),
        // 默认路径
        "template/yima-cpp"
    };
    
    // 查找第一个存在的模板目录
    for (const auto& path : candidatePaths) {
        fs::path templatePath(path);
        if (fs::exists(templatePath) && fs::is_directory(templatePath)) {
            // 检查是否包含config.json5文件
            fs::path configPath = templatePath / "config.json5";
            if (fs::exists(configPath)) {
                return templatePath.string();
            }
        }
    }
    
    // 如果都没找到，返回第一个候选路径（让后续处理报错）
    return candidatePaths[0];
}

// 查找include文件的路径
std::string findIncludeFile(const std::string& includePath, const std::vector<std::string>& includePaths, const std::string& currentFileDir) {
    // 候选路径列表
    std::vector<std::string> candidatePaths;
    
    // 1. 相对于当前文件的路径
    candidatePaths.push_back((fs::path(currentFileDir) / includePath).string());
    
    // 2. 在指定的include路径中查找
    for (const auto& includeDir : includePaths) {
        candidatePaths.push_back((fs::path(includeDir) / includePath).string());
    }
    
    // 3. 在默认的mota-include目录中查找
    candidatePaths.push_back((fs::path("mota-include") / includePath).string());
    
    // 4. 在可执行文件目录的mota-include中查找
    std::string exeDir = getExecutableDirectory();
    candidatePaths.push_back((fs::path(exeDir) / "mota-include" / includePath).string());
    candidatePaths.push_back((fs::path(exeDir) / ".." / "mota-include" / includePath).string());
    
    // 查找第一个存在的文件
    for (const auto& path : candidatePaths) {
        if (fs::exists(path) && fs::is_regular_file(path)) {
            return path;
        }
    }
    
    return ""; // 未找到
}

// 递归处理include文件，合并所有声明到一个document中
std::unique_ptr<mota::ast::Document> processIncludesRecursively(
    const std::string& filePath, 
    const std::vector<std::string>& includePaths,
    std::set<std::string>& processedFiles) {
    
    // 获取文件的绝对路径，避免重复处理
    std::string absolutePath = fs::absolute(filePath).string();
    if (processedFiles.count(absolutePath)) {
        // 文件已经处理过，返回空document避免循环包含
        return std::make_unique<mota::ast::Document>();
    }
    processedFiles.insert(absolutePath);
    
    // 读取文件
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open include file " << filePath << std::endl;
        return nullptr;
    }
    
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    
    try {
        // 解析当前文件
        mota::lexer::Lexer lexer(source, filePath);
        mota::parser::Parser parser(lexer);
        auto document = parser.parse();
        
        if (!document) {
            std::cerr << "Error: Failed to parse include file " << filePath << std::endl;
            return nullptr;
        }
        
        // 获取当前文件所在目录
        std::string currentFileDir = fs::path(filePath).parent_path().string();
        
        // 处理include声明 - 验证include文件存在但保留include声明
        for (auto& decl : document->declarations) {
            if (decl->nodeType() == mota::ast::NodeType::IncludeDecl) {
                // 这是一个include声明，验证文件存在
                auto includeDecl = static_cast<mota::ast::Include*>(decl.get());
                std::string includeFile = findIncludeFile(includeDecl->path, includePaths, currentFileDir);
                
                if (includeFile.empty()) {
                    std::cerr << "Error: Include file not found: " << includeDecl->path << std::endl;
                    return nullptr;
                }
                
                // 递归处理include文件以验证其语法正确性
                auto includedDoc = processIncludesRecursively(includeFile, includePaths, processedFiles);
                if (!includedDoc) {
                    return nullptr;
                }
                
                // 注意：我们不合并include文件的内容，只是验证它们的存在和语法正确性
                // include声明会保留在当前文档中，由代码生成器转换为#include指令
            }
        }
        
        return document;
        
    } catch (const std::exception& e) {
        std::cerr << "Error processing include file " << filePath << ": " << e.what() << std::endl;
        return nullptr;
    }
}

bool processMotaFile(const std::string& inputFile, const std::string& outputDir, const std::string& templateDir, const std::vector<std::string>& includePaths) {
    try {
        // 处理include文件，获取合并后的document
        std::set<std::string> processedFiles;
        auto document = processIncludesRecursively(inputFile, includePaths, processedFiles);
        
        if (!document) {
            std::cerr << "Error: Failed to process file with includes " << inputFile << std::endl;
            return false;
        }
        
        // 语法检查 - 需要收集所有include文件的注解定义
        mota::checker::SyntaxChecker checker;
        
        // 收集include文件中的注解定义
        std::set<std::string> allAnnotations;
        std::function<void(const mota::ast::Document&)> collectAnnotations = [&](const mota::ast::Document& doc) {
            std::string currentNamespace = "";
            for (const auto& decl : doc.declarations) {
                if (decl->nodeType() == mota::ast::NodeType::NamespaceDecl) {
                    auto namespaceDecl = static_cast<const mota::ast::Namespace*>(decl.get());
                    currentNamespace = "";
                    for (size_t i = 0; i < namespaceDecl->name.size(); ++i) {
                        if (i > 0) currentNamespace += ".";
                        currentNamespace += namespaceDecl->name[i];
                    }
                } else if (decl->nodeType() == mota::ast::NodeType::AnnotationDecl) {
                    auto annotationDecl = static_cast<const mota::ast::AnnotationDecl*>(decl.get());
                    std::string fullName = annotationDecl->name;
                    if (!currentNamespace.empty()) {
                        fullName = currentNamespace + "." + annotationDecl->name;
                    }
                    allAnnotations.insert(fullName);
                }
            }
        };
        
        // 收集include文件的注解
        std::set<std::string> processedForAnnotations;
        std::function<void(const std::string&)> processIncludeForAnnotations = [&](const std::string& filePath) {
            std::string absolutePath = fs::absolute(filePath).string();
            if (processedForAnnotations.count(absolutePath)) {
                return;
            }
            processedForAnnotations.insert(absolutePath);
            
            std::ifstream file(filePath);
            if (!file.is_open()) return;
            
            std::string source((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
            file.close();
            
            try {
                mota::lexer::Lexer lexer(source, filePath);
                mota::parser::Parser parser(lexer);
                auto includeDoc = parser.parse();
                if (includeDoc) {
                    collectAnnotations(*includeDoc);
                    
                    // 处理嵌套include
                    std::string currentFileDir = fs::path(filePath).parent_path().string();
                    for (const auto& includeDecl : includeDoc->includes) {
                        std::string includeFile = findIncludeFile(includeDecl->path, includePaths, currentFileDir);
                        if (!includeFile.empty()) {
                            processIncludeForAnnotations(includeFile);
                        }
                    }
                }
            } catch (...) {
                // 忽略解析错误，在主语法检查中会报告
            }
        };
        
        // 先收集当前文件本身的注解
        collectAnnotations(*document);
        
        // 处理当前文件的include
        std::string currentFileDir = fs::path(inputFile).parent_path().string();
        for (const auto& includeDecl : document->includes) {
            std::string includeFile = findIncludeFile(includeDecl->path, includePaths, currentFileDir);
            if (!includeFile.empty()) {
                processIncludeForAnnotations(includeFile);
            }
        }
        
        auto errors = checker.checkWithExternalAnnotations(*document, inputFile, allAnnotations);
        
        if (!errors.empty()) {
            std::cerr << "Syntax errors found in " << inputFile << ":" << std::endl;
            for (const auto& error : errors) {
                std::cerr << "  " << error.message << std::endl;
            }
            return false;
        }
        
        // 代码生成
        mota::generator::Generator generator;
        
        // 初始化生成器
        if (!generator.initialize(templateDir)) {
            std::cerr << "Error: Failed to initialize generator with template directory: " << templateDir << std::endl;
            return false;
        }
        
        // 生成代码
        std::string generatedCode = generator.generateCode(document, "file");
        
        if (generatedCode.empty()) {
            std::cerr << "Error: Failed to generate code for " << inputFile << std::endl;
            return false;
        }
        
        // 根据配置文件生成输出文件路径
        fs::path inputPath(inputFile);
        std::string fileName = inputPath.stem().string();
        
        // 提取命名空间信息
        std::string namespaceStr = "";
        for (const auto& node : document->declarations) {
            if (node->nodeType() == mota::ast::NodeType::NamespaceDecl) {
                auto namespaceNode = static_cast<const mota::ast::Namespace*>(node.get());
                for (size_t i = 0; i < namespaceNode->name.size(); ++i) {
                    if (i > 0) namespaceStr += ".";
                    namespaceStr += namespaceNode->name[i];
                }
                break;
            }
        }
        
        // 构建输出路径
        std::string outputFile = outputDir;
        if (!namespaceStr.empty()) {
            // 将命名空间的点替换为路径分隔符
            std::string namespacePath = namespaceStr;
            std::replace(namespacePath.begin(), namespacePath.end(), '.', '/');
            outputFile = (fs::path(outputDir) / namespacePath / (fileName + ".h")).string();
        } else {
            outputFile = (fs::path(outputDir) / (fileName + ".h")).string();
        }
        
        // 确保输出目录存在
        fs::create_directories(fs::path(outputFile).parent_path());
        
        std::ofstream outFile(outputFile);
        if (outFile.is_open()) {
            outFile << generatedCode;
            outFile.close();
            std::cout << "Generated: " << outputFile << std::endl;
            return true;
        } else {
            std::cerr << "Error: Cannot write to file " << outputFile << std::endl;
            return false;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error processing " << inputFile << ": " << e.what() << std::endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    
    Options options = parseCommandLine(argc, argv);
    
    if (options.showHelp) {
        showHelp();
        return 0;
    }
    
    if (options.showVersion) {
        showVersion();
        return 0;
    }
    
    // 检查是否自动加载mota-config.json
    if (options.configPath.empty() && fs::exists("mota-config.json")) {
        options.configPath = "mota-config.json";
        std::cout << "Auto-loading config: mota-config.json" << std::endl;
    }
    
    // 处理配置文件
    ConfigFile configFile;
    bool useConfigFile = false;
    
    if (!options.configPath.empty()) {
        std::cout << "Using config file: " << options.configPath << std::endl;
        try {
            configFile = parseConfigFile(options.configPath);
            useConfigFile = true;
            
            // 合并命令行指定的 include 路径
            for (const auto& path : options.includePaths) {
                configFile.includePaths.push_back(path);
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    
    int successCount = 0;
    int totalCount = 0;
    
    if (useConfigFile) {
        // 使用配置文件处理多个项目
        for (const auto& project : configFile.projects) {
            std::vector<std::string> filesToProcess;
            
            if (options.files.empty()) {
                // 如果没有指定文件，从项目源目录搜索.mota文件
                filesToProcess = findMotaFiles(project.sourceDir);
                if (filesToProcess.empty()) {
                    std::cout << "No .mota files found in directory: " << project.sourceDir << std::endl;
                    continue;
                }
            } else {
                // 处理指定的文件/目录
                for (const auto& file : options.files) {
                    if (fs::is_directory(file)) {
                        auto dirFiles = findMotaFiles(file);
                        filesToProcess.insert(filesToProcess.end(), dirFiles.begin(), dirFiles.end());
                    } else if (fs::is_regular_file(file)) {
                        filesToProcess.push_back(file);
                    } else {
                        std::cerr << "Warning: File not found: " << file << std::endl;
                    }
                }
            }
            
            if (filesToProcess.empty()) {
                continue;
            }
            
            // 确定模板目录
            std::string templateDir = findTemplateDirectory(project.lang);
            
            // 处理项目中的每个文件
            std::cout << "Processing project: " << project.sourceDir << " -> " << project.outputDir << std::endl;
            
            for (const auto& file : filesToProcess) {
                totalCount++;
                if (processMotaFile(file, project.outputDir, templateDir, configFile.includePaths)) {
                    successCount++;
                }
            }
        }
    } else {
        // 使用命令行参数处理单个项目
        std::vector<std::string> filesToProcess;
        
        if (options.files.empty()) {
            // 如果没有指定文件，从源目录搜索.mota文件
            filesToProcess = findMotaFiles(options.sourceDir);
            if (filesToProcess.empty()) {
                std::cout << "No .mota files found in directory: " << options.sourceDir << std::endl;
                return 0;
            }
        } else {
            // 处理指定的文件/目录
            for (const auto& file : options.files) {
                if (fs::is_directory(file)) {
                    auto dirFiles = findMotaFiles(file);
                    filesToProcess.insert(filesToProcess.end(), dirFiles.begin(), dirFiles.end());
                } else if (fs::is_regular_file(file)) {
                    filesToProcess.push_back(file);
                } else {
                    std::cerr << "Warning: File not found: " << file << std::endl;
                }
            }
        }
        
        if (filesToProcess.empty()) {
            std::cout << "No files to process." << std::endl;
            return 0;
        }
        
        // 确定模板目录
        std::string templateDir = findTemplateDirectory(options.lang);
        
        // 处理每个文件
        totalCount = filesToProcess.size();
        
        for (const auto& file : filesToProcess) {
            if (processMotaFile(file, options.outputDir, templateDir, options.includePaths)) {
                successCount++;
            }
        }
    }
    
    std::cout << "Completed: " << successCount << "/" << totalCount << " files processed successfully." << std::endl;
    
    if (successCount == totalCount) {
        return 0;
    } else {
        return 1;
    }
} 