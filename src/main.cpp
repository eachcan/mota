#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "parser.h"
#include "generator.h"
#include "syntax_checker.h"
#include <windows.h>

namespace fs = std::filesystem;

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

Options parseCommandLine(int argc, char* argv[]) {
    Options options;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
        } else if (arg == "-v" || arg == "--version") {
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

bool processMotaFile(const std::string& inputFile, const std::string& outputDir, const std::string& templateDir) {
    // 读取输入文件
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << inputFile << std::endl;
        return false;
    }
    
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    
    try {
        // 词法分析和语法分析
        mota::lexer::Lexer lexer(source);
        mota::parser::Parser parser(lexer);
        auto document = parser.parse();
        
        if (!document) {
            std::cerr << "Error: Failed to parse document " << inputFile << std::endl;
            return false;
        }
        
        // 语法检查
        mota::checker::SyntaxChecker checker;
        auto errors = checker.check(*document);
        
        if (!errors.empty()) {
            std::cerr << "Syntax errors found in " << inputFile << ":" << std::endl;
            for (const auto& error : errors) {
                std::cerr << "  " << error.message << std::endl;
            }
            return false;
        }
        
        // 代码生成
        mota::generator::Generator generator(templateDir);
        
        // 加载配置
        std::string configPath = templateDir + "/config.json5";
        generator.loadConfig(configPath);
        
        // 生成代码
        std::string generatedCode = generator.generateFile(*document);
        
        if (generatedCode.empty()) {
            std::cerr << "Error: Failed to generate code for " << inputFile << std::endl;
            return false;
        }
        
        // 确保输出目录存在
        fs::create_directories(outputDir);
        
        // 根据输入文件名生成输出文件名
        fs::path inputPath(inputFile);
        // TODO: 根据配置文件中的 file_path 生成输出文件名
        std::string outputFile = (fs::path(outputDir) / inputPath.stem()).string() + ".h";
        
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
    
    // TODO: 处理配置文件
    if (!options.configPath.empty()) {
        std::cout << "Note: Config file support is not implemented yet: " << options.configPath << std::endl;
    }
    
    // 确定要处理的文件列表
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
    std::string templateDir = "template/";
    if (options.lang.empty()) {
        templateDir = "template/yima-cpp";
    } else {
        templateDir = "template/" + options.lang;
    }
    std::cout << "templateDir: " << templateDir << std::endl;
    
    // 处理每个文件
    int successCount = 0;
    int totalCount = filesToProcess.size();
    
    std::cout << "Processing " << totalCount << " file(s)..." << std::endl;
    
    for (const auto& file : filesToProcess) {
        std::cout << "Processing: " << file << std::endl;
        if (processMotaFile(file, options.outputDir, templateDir)) {
            successCount++;
        }
    }
    
    std::cout << std::endl;
    std::cout << "Completed: " << successCount << "/" << totalCount << " files processed successfully." << std::endl;
    
    if (successCount == totalCount) {
        return 0;
    } else {
        return 1;
    }
} 