#include "lexer.h"
#include "parser.h"
#include "config.h"
#include "version.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cxxopts.hpp>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace mota;

void processFile(const std::string& filePath) {
    // 读取文件
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // 读取文件内容
    std::string input((std::istreambuf_iterator<char>(file)), 
                     std::istreambuf_iterator<char>());

    // 创建词法分析器并进行词法分析
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    // 创建语法分析器并进行语法分析
    Parser parser(tokens);
    auto fileNode = parser.parseFile();

    // 这里可以添加生成代码的逻辑
    std::cout << "Successfully parsed: " << filePath << std::endl;
}

int main(int argc, char* argv[]) {
    // 在 Windows 下设置控制台编码为 UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        // 设置命令行选项
        cxxopts::Options options("mota", "Mota language processor");
        
        options.add_options()
            ("h,help", "Display this help message")
            ("version", "Display version information")
            ("config", "Config file path", cxxopts::value<std::string>())
            ("dest", "Output directory", cxxopts::value<std::string>())
            ("input", "Input files", cxxopts::value<std::vector<std::string>>())
            ;

        options.parse_positional({"input"});
        options.positional_help("mota_file1 mota_file2 ...");

        auto result = options.parse(argc, argv);

        // 显示帮助信息
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        // 显示版本信息
        if (result.count("version")) {
            std::cout << "Mota version " << MOTA_VERSION << std::endl;
            return 0;
        }

        // 检查配置文件
        Config config;
        if (result.count("config")) {
            std::string configPath = result["config"].as<std::string>();
            try {
                config = Config::loadFromFile(configPath);
            } catch (const std::exception& e) {
                std::cerr << "Error loading config file: " << e.what() << std::endl;
                return 1;
            }
        }

        // 检查输出目录
        std::string destDir = ".";
        if (result.count("dest")) {
            destDir = result["dest"].as<std::string>();
            if (!std::filesystem::exists(destDir)) {
                std::filesystem::create_directories(destDir);
            }
        }

        // 处理输入文件
        if (result.count("input")) {
            auto files = result["input"].as<std::vector<std::string>>();
            for (const auto& file : files) {
                try {
                    processFile(file);
                } catch (const std::exception& e) {
                    std::cerr << "Error processing file " << file << ": " 
                              << e.what() << std::endl;
                    return 1;
                }
            }
        } else {
            std::cerr << "No input files specified." << std::endl;
            std::cout << options.help() << std::endl;
            return 1;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
