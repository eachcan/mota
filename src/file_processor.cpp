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
    
    std::cout << "处理文件: " << inputFile << std::endl;
    if (verbose) {
        std::cout << "输出目录: " << outputDir << std::endl;
        std::cout << "模板目录: " << templateDir << std::endl;
    }
    
    try {
        // 读取主文件
        std::string source = readFile(inputFile);
        if (source.empty()) {
            std::cerr << "错误: 无法读取文件 " << inputFile << std::endl;
            return false;
        }
        
        // 解析主文件
        auto root = parseFile(inputFile);
        if (!root) {
            std::cerr << "错误: 解析文件失败 " << inputFile << std::endl;
            return false;
        }
        
        // 构建包含注册表
        std::set<std::string> includedFiles = {fs::absolute(inputFile).string()};
        std::map<std::string, checker::KnownDecl> includedDeclarations;
        std::map<std::string, checker::KnownDecl> currentDeclarations;
        
        buildIncludeRegistry(*root, inputFile, includedFiles, includePaths, includedDeclarations, verbose);
        
        checker::SyntaxChecker syntaxChecker;
        auto diagnostics = syntaxChecker.check(*root, inputFile, includedDeclarations, currentDeclarations);
        
        if (!diagnostics.empty()) {
            std::cerr << "在文件 " << inputFile << " 中发现语法错误:" << std::endl;
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
            std::cerr << "错误: 生成器初始化失败，模板目录: " << templateDir << std::endl;
            return false;
        }
        
        if (verbose) {
            std::cout << "生成器初始化成功，开始生成代码..." << std::endl;
        }
        
        auto filePaths = generator.getConfig().file_path;
        for (const auto& filePath : filePaths) {
            std::string generatedCode = generator.generateCode(root, filePath.entry);
            if (generatedCode.empty()) {
                std::cerr << "错误: 代码生成失败 " << inputFile << std::endl;
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
                std::cerr << "错误: 无法创建输出文件 " << outputFilePath << std::endl;
                return false;
            }
            
            outFile << generatedCode;
            outFile.close();
            if (verbose) {
                std::cout << "已生成到: " << outputFilePath << std::endl;
            }
        }
        
        std::cout << "生成完成: " << root->location.filename << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "错误: 未知异常" << std::endl;
        return false;
    }
}

void FileProcessor::buildIncludeRegistry(
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
            if (verbose) {
                std::cout << "警告: 解析包含文件失败 " << absoluteIncludePath << std::endl;
            }
            continue;
        }
        
        // 递归处理下级包含
        std::map<std::string, checker::KnownDecl> nextIncludeDeclarations;
        buildIncludeRegistry(*doc, absoluteIncludePath, includedFiles, includePaths, nextIncludeDeclarations, verbose);
        
        // 对包含的文档进行语法检查
        checker::SyntaxChecker syntaxChecker;
        std::map<std::string, checker::KnownDecl> docDeclarations;
        auto diagnostics = syntaxChecker.check(*doc, absoluteIncludePath, nextIncludeDeclarations, docDeclarations);
        
        if (!diagnostics.empty()) {
            if (verbose) {
                std::cout << "警告: 包含文件中有语法错误 " << absoluteIncludePath << std::endl;
                for (const auto& diagnostic : diagnostics) {
                    std::cout << "  [" << diagnostic.line << ":" << diagnostic.column << "] " 
                             << diagnostic.message << std::endl;
                }
            }
        }
        
        // 合并声明到上级
        mergeDeclarations(includedDeclarations, nextIncludeDeclarations);
        mergeDeclarations(includedDeclarations, docDeclarations);
    }
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

std::unique_ptr<ast::Document> FileProcessor::parseFile(const std::string& filePath) const {
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

} // namespace processor  
} // namespace mota 