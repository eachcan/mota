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
#include "file_processor.h"
#include <windows.h>
#include "version.h"
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;
using json = nlohmann::json;

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

// 启用Windows控制台颜色支持
void enableConsoleColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

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
    std::string lang = "";
    std::string configPath;
    std::vector<std::string> files;
    bool showHelp = false;
    bool showVersion = false;
    bool verbose = false;
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
    std::cout << "                  设置输出目录，默认为 `output`" << std::endl;
    std::cout << "  -l, --lang LANG" << std::endl;
    std::cout << "                  设置输出语言，可选值：yima-cpp[默认]" << std::endl;
    std::cout << "  -c, --config PATH" << std::endl;
    std::cout << "                  设置配置文件路径。" << std::endl;
    std::cout << "                  本参数和 FILE 互斥，如果指定了 FILE 则忽略配置文件。" << std::endl;
    std::cout << "                  如果当前目录存在 mota-config.json，且未指定 FILE，则会自动加载。" << std::endl;
    std::cout << std::endl;
    std::cout << "FILE" << std::endl;
    std::cout << "    指定要编译的 Mota 文件或目录路径，如果未指定，则使用配置文件或从当前目录开始搜索，不会递归搜索。" << std::endl;
}

void showVersion() {
    std::cout << "mota version " << MOTA_VERSION << std::endl;
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
        } else if (arg == "-v" || arg == "--verbose") {
            options.verbose = true;
        } else if (arg == "-i" || arg == "--include-path") {
            if (i + 1 < argc) {
                options.includePaths.push_back(argv[++i]);
            } else {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-o" || arg == "--output-dir") {
            if (i + 1 < argc) {
                options.outputDir = argv[++i];
            } else {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-l" || arg == "--lang") {
            if (i + 1 < argc) {
                options.lang = argv[++i];
                if (options.lang.empty()) {
                    options.lang = "yima-cpp";
                }
            } else {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << arg << " requires a language argument" << std::endl;
                exit(1);
            }
        } else if (arg == "-c" || arg == "--config") {
            if (i + 1 < argc) {
                options.configPath = argv[++i];
            } else {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << arg << " requires a path argument" << std::endl;
                exit(1);
            }
        } else if (arg[0] != '-') {
            // FILE参数
            options.files.push_back(arg);
        } else {
            std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "Unknown option: " << arg << std::endl;
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
        std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "accessing directory " << directory << ": " << e.what() << std::endl;
    }
    
    return motaFiles;
}

std::string getExecutableDirectory() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    fs::path exePath(buffer);
    return exePath.parent_path().string();
}

std::string findTemplateDirectory(const std::string& lang, bool verbose = false) {
    std::string exeDir = getExecutableDirectory();

    std::string templateLang = lang;
    if (templateLang.empty()) {
        templateLang = "yima-cpp";
    }
    
    std::vector<std::string> searchPaths = {
        exeDir + "/template/" + templateLang,
        exeDir + "/../template/" + templateLang,
        exeDir + "/../../template/" + templateLang,
        "./template/" + templateLang
    };
    
    if (verbose) {
        std::cout << "Searching for template directory for language: " << lang << std::endl;
    }
    
    for (const auto& path : searchPaths) {
        if (verbose) {
            std::cout << "  Checking: " << path << std::endl;
        }
        
        fs::path templatePath(path);
        if (fs::exists(templatePath) && fs::is_directory(templatePath)) {
            if (verbose) {
                std::cout << "  Found template directory: " << path << std::endl;
            }
            return templatePath.string();
        }
    }
    
    std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << "Template directory not found for language: " << lang << std::endl;
    std::cerr << "Searched paths:" << std::endl;
    for (const auto& path : searchPaths) {
        std::cerr << "  " << path << std::endl;
    }
    
    return "";
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    enableConsoleColors();
    
    Options options = parseCommandLine(argc, argv);
    
    if (options.verbose) {
        std::cout << "Starting mota compiler..." << std::endl;
        std::cout << "Arguments count: " << argc << std::endl;
        for (int i = 0; i < argc; ++i) {
            std::cout << "  arg[" << i << "]: " << argv[i] << std::endl;
        }
        
        std::cout << "Parsed options:" << std::endl;
        std::cout << "  outputDir: " << options.outputDir << std::endl;
        std::cout << "  lang: " << options.lang << std::endl;
        std::cout << "  files count: " << options.files.size() << std::endl;
        for (const auto& file : options.files) {
            std::cout << "    file: " << file << std::endl;
        }
    }
    
    if (options.showHelp) {
        showHelp();
        return 0;
    }
    
    if (options.showVersion) {
        showVersion();
        return 0;
    }

    std::string exeDir = getExecutableDirectory();
    if (options.verbose) {
        std::cout << "exeDir: " << exeDir << std::endl;
    }
    
    int successCount = 0;
    int totalCount = 0;
    
    // 创建文件处理器
    mota::processor::FileProcessor processor;
    
    if (!options.files.empty()) {
        // 如果指定了 FILE，则忽略配置文件，使用命令行参数处理
        std::vector<std::string> filesToProcess;
        
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
        
        if (filesToProcess.empty()) {
            if (options.verbose) {
                std::cout << "No files to process." << std::endl;
            }
            return 0;
        }
        
        // 确定模板目录
        std::string templateDir = findTemplateDirectory(options.lang, options.verbose);
        if (templateDir.empty()) {
            return 1;
        }
        
        // 显示语言信息（非verbose模式）
        if (!options.verbose) {
            std::cout << "Language: " << options.lang << std::endl;
        }
        
        // 处理每个文件
        totalCount = filesToProcess.size();
        
        for (const auto& file : filesToProcess) {
            if (processor.processMotaFile(file, options.outputDir, templateDir, options.includePaths, options.verbose)) {
                successCount++;
            }
        }
    } else {
        // 如果没有指定 FILE，则检查配置文件
        if (options.configPath.empty() && fs::exists("mota-config.json")) {
            options.configPath = "mota-config.json";
            if (options.verbose) {
                std::cout << "Auto-loading config: mota-config.json" << std::endl;
            }
        }
        
        if (!options.configPath.empty()) {
            // 使用配置文件处理多个项目
            ConfigFile configFile;
            try {
                configFile = parseConfigFile(options.configPath);
                
                // 合并命令行指定的 include 路径
                for (const auto& path : options.includePaths) {
                    configFile.includePaths.push_back(path);
                }
                
            } catch (const std::exception& e) {
                std::cerr << Colors::BOLD_RED << "Error: " << Colors::RESET << e.what() << std::endl;
                return 1;
            }
            
            for (const auto& project : configFile.projects) {
                std::vector<std::string> filesToProcess;
                
                // 从项目源目录搜索.mota文件
                filesToProcess = findMotaFiles(project.sourceDir);
                if (filesToProcess.empty()) {
                    if (options.verbose) {
                        std::cout << "No .mota files found in directory: " << project.sourceDir << std::endl;
                    }
                    continue;
                }
                
                // 确定模板目录
                std::string templateDir = findTemplateDirectory(project.lang, options.verbose);
                if (templateDir.empty()) {
                    return 1;
                }
                
                // 显示语言信息（非verbose模式，只显示一次）
                if (!options.verbose && totalCount == 0) {
                    std::cout << "Language: " << project.lang << std::endl;
                }
                
                // 处理项目中的每个文件
                if (options.verbose) {
                    std::cout << "Processing project: " << project.sourceDir << " -> " << project.outputDir << std::endl;
                }
                
                for (const auto& file : filesToProcess) {
                    totalCount++;
                    if (processor.processMotaFile(file, project.outputDir, templateDir, configFile.includePaths, options.verbose)) {
                        successCount++;
                    }
                }
            }
        } else {
            // 既没有指定文件，也没有配置文件，从当前目录搜索
            std::vector<std::string> filesToProcess = findMotaFiles(".");
            if (filesToProcess.empty()) {
                if (options.verbose) {
                    std::cout << "No .mota files found in current directory." << std::endl;
                }
                return 0;
            }
            
            // 确定模板目录
            std::string templateDir = findTemplateDirectory(options.lang, options.verbose);
            if (templateDir.empty()) {
                return 1;
            }
            
            // 显示语言信息（非verbose模式）
            if (!options.verbose) {
                std::cout << "Language: " << options.lang << std::endl;
            }
            
            // 处理每个文件
            totalCount = filesToProcess.size();
            
            for (const auto& file : filesToProcess) {
                if (processor.processMotaFile(file, options.outputDir, templateDir, options.includePaths, options.verbose)) {
                    successCount++;
                }
            }
        }
    }
    
    if (successCount == totalCount) {
        std::cout << Colors::BOLD_GREEN << "Completed: " << successCount << "/" << totalCount << " files processed successfully." << Colors::RESET << std::endl;
    } else {
        std::cout << Colors::BOLD_RED << "Completed: " << successCount << "/" << totalCount << " files processed successfully." << Colors::RESET << std::endl;
    }
    
    if (successCount == totalCount) {
        return 0;
    } else {
        return 1;
    }
} 