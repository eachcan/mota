#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace mota;

int main() {
    // 在 Windows 下设置控制台编码为 UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // 设置控制台输出编码为 UTF-8
#endif

    // 输出当前目录
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    // 从 examples/example.mota 文件中读取代码
    std::ifstream file("../../../../examples/example.mota", std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // 读取文件内容
    std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // 创建词法分析器并进行词法分析
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    // 输出每个 token
    for (const auto& token : tokens) {
        // 输出 token 的类型和值以及所在行列信息
        std::cout << "Token: " << tokenTypeToString(token.type) 
                  << " Value: " << token.value 
                  << " Line: " << token.line 
                  << " Column: " << token.column << std::endl;
    }

    // 创建语法分析器并进行语法分析
    Parser parser(tokens);
    auto fileNode = parser.parseFile();

    // 输出解析结果
    std::cout << "Parsed file:" << std::endl;
    for (const auto& decl : fileNode->declarations) {
        if (auto include = std::dynamic_pointer_cast<IncludeDecl>(decl)) {
            std::cout << "Include: " << include->path << std::endl;
        } else if (auto ns = std::dynamic_pointer_cast<NamespaceDecl>(decl)) {
            std::cout << "Namespace: ";
            for (const auto& part : ns->path) {
                std::cout << part << ".";
            }
            std::cout << std::endl;
        } else if (auto enumDecl = std::dynamic_pointer_cast<EnumDecl>(decl)) {
            std::cout << "Enum: " << enumDecl->name << std::endl;
            for (const auto& value : enumDecl->values) {
                std::cout << "  " << value->name << std::endl;
            }
        } else if (auto structDecl = std::dynamic_pointer_cast<StructDecl>(decl)) {
            std::cout << "Struct: " << structDecl->name;
            if (structDecl->hasParent()) {
                std::cout << " : " << structDecl->parentType << " " << structDecl->parentName;
            }
            std::cout << std::endl;
            for (const auto& field : structDecl->fields) {
                std::cout << "  " << field->name << std::endl;
            }
        } else if (auto blockDecl = std::dynamic_pointer_cast<BlockDecl>(decl)) {
            std::cout << "Block: " << blockDecl->name;
            if (blockDecl->hasParent()) {
                std::cout << " : block " << blockDecl->parentName;
            }
            std::cout << std::endl;
            for (const auto& field : blockDecl->fields) {
                std::cout << "  " << field->name << std::endl;
            }
        }
    }

    return 0;
}
