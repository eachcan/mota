#include "generator.h"
#include "parser.h"
#include "lexer.h"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

class GeneratorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 创建测试目录
        std::filesystem::create_directories("test/generated");
    }
    
    void TearDown() override {
        // 清理测试目录
        std::filesystem::remove_all("test/generated");
    }
    
    std::shared_ptr<mota::FileNode> parseFile(const std::string& content) {
        mota::Lexer lexer(content);
        auto tokens = lexer.tokenize();
        mota::Parser parser(tokens);
        return parser.parseFile();
    }
    
    void compareFiles(const std::string& expected, const std::string& actual) {
        std::ifstream expectedFile(expected);
        std::ifstream actualFile(actual);
        
        ASSERT_TRUE(expectedFile.is_open()) << "Cannot open expected file: " << expected;
        ASSERT_TRUE(actualFile.is_open()) << "Cannot open actual file: " << actual;
        
        std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)),
                                  std::istreambuf_iterator<char>());
        std::string actualContent((std::istreambuf_iterator<char>(actualFile)),
                                std::istreambuf_iterator<char>());
        
        if (expectedContent != actualContent) {
            std::cout << "\nExpected content:\n" << expectedContent 
                      << "\n\nActual content:\n" << actualContent << std::endl;
        }
        
        EXPECT_EQ(expectedContent, actualContent);
    }
    
    void saveGeneratedFiles(const std::vector<mota::GeneratedFile>& files) {
        for (const auto& file : files) {
            std::filesystem::path filePath("test/generated/" + file.filename);
            std::cout << "Saving generated file: " << filePath << std::endl;
            
            std::filesystem::create_directories(filePath.parent_path());
            std::ofstream out(filePath);
            ASSERT_TRUE(out.is_open()) << "Cannot create file: " << filePath;
            out << file.content;
        }
    }
};

TEST_F(GeneratorTest, GenerateSimpleEnum) {
    std::string input = R"(
        enum Color {
            Red = 1;
            Green = 2;
            Blue = 3;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    saveGeneratedFiles(files);
    
    // 比较文件
    compareFiles("examples/generated/expected_enum.h", "test/generated/models.h");
    compareFiles("examples/generated/expected_enum.cpp", "test/generated/models.cpp");
}

TEST_F(GeneratorTest, GenerateStructWithAnnotations) {
    std::string input = R"(
        @storage(file="config.dat", format="cbor")
        struct Config {
            string name = "default";
            optional int32 value;
            repeated string tags;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    // 写入和比较文件
    for (const auto& file : files) {
        std::filesystem::path filePath("test/generated/" + file.filename);
        std::ofstream out(filePath);
        ASSERT_TRUE(out.is_open());
        out << file.content;
    }
    
    compareFiles("examples/generated/expected_config.h", "test/generated/models.h");
    compareFiles("examples/generated/expected_config.cpp", "test/generated/models.cpp");
}

TEST_F(GeneratorTest, GenerateBlockWithInheritance) {
    std::string input = R"(
        block BaseTask {
            string id;
            string name;
            int32 priority = 0;
        }

        block DailyTask : BaseTask {
            string time;
            bool repeat = false;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    // 写入和比较文件
    for (const auto& file : files) {
        std::filesystem::path filePath("test/generated/" + file.filename);
        std::ofstream out(filePath);
        ASSERT_TRUE(out.is_open());
        out << file.content;
    }
    
    compareFiles("examples/generated/expected_task.h", "test/generated/models.h");
    compareFiles("examples/generated/expected_task.cpp", "test/generated/models.cpp");
}

TEST_F(GeneratorTest, GenerateWithNamespace) {
    std::string input = R"(
        namespace app.models;

        enum Status {
            Active = 1;
            Inactive = 2;
        }

        struct User {
            string name;
            Status status = Status::Active;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    // 写入和比较文件
    for (const auto& file : files) {
        std::filesystem::path filePath("test/generated/" + file.filename);
        std::ofstream out(filePath);
        ASSERT_TRUE(out.is_open());
        out << file.content;
    }
    
    compareFiles("examples/generated/expected_user.h", "test/generated/models.h");
    compareFiles("examples/generated/expected_user.cpp", "test/generated/models.cpp");
}

// 辅助函数：检查生成的代码中是否包含特定内容
void checkGeneratedContent(const std::string& content, const std::vector<std::string>& expectedParts) {
    for (const auto& part : expectedParts) {
        EXPECT_TRUE(content.find(part) != std::string::npos) 
            << "Expected to find: " << part;
    }
}

// 测试完整的枚举生成
TEST_F(GeneratorTest, GenerateComplexEnum) {
    std::string input = R"(
        // 状态枚举
        enum Status {
            // 初始状态
            Initial = 0;
            // 运行中
            Running = 1;
            // 已暂停
            Paused = 2;
            // 已完成
            Completed = 100;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    // 检查头文件内容
    std::vector<std::string> expectedHeader = {
        "// 状态枚举",
        "enum class Status {",
        "    // 初始状态",
        "    Initial = 0,",
        "    // 运行中",
        "    Running = 1,",
        "    // 已暂停",
        "    Paused = 2,",
        "    // 已完成",
        "    Completed = 100,",
        "};"
    };
    
    // 检查源文件内容
    std::vector<std::string> expectedSource = {
        "QString toString(Status value)",
        "switch (value)",
        "case Status::Initial: return \"Initial\";",
        "Status fromString(const QString& str)",
        "if (str == \"Initial\") return Status::Initial;"
    };
    
    for (const auto& file : files) {
        if (file.filename.find(".h") != std::string::npos) {
            checkGeneratedContent(file.content, expectedHeader);
        } else {
            checkGeneratedContent(file.content, expectedSource);
        }
    }
}

// 测试复杂结构体生成
TEST_F(GeneratorTest, GenerateComplexStruct) {
    std::string input = R"(
        @storage(file="config/app.json", format="json", level="user")
        struct AppConfig {
            // 应用名称
            string name = "MyApp";
            // 版本号
            string version = "1.0.0";
            // 是否启用调试
            optional bool debug;
            // 日志级别
            repeated string logLevels = ["info", "error"];
            // 端口配置
            map<string, int32> ports = {
                "http": 8080,
                "https": 8443
            };
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    std::vector<std::string> expectedHeader = {
        "class AppConfig : public mota::BaseModel {",
        "    // 应用名称",
        "    QString name = \"MyApp\";",
        "    // 版本号",
        "    QString version = \"1.0.0\";",
        "    // 是否启用调试",
        "    std::optional<bool> debug;",
        "    // 日志级别",
        "    QVector<QString> logLevels = {\"info\", \"error\"};",
        "    // 端口配置",
        "    QMap<QString, int32_t> ports;",
        "    QCborValue toCbor() const override;",
        "    void fromCbor(const QCborValue& cbor) override;"
    };
    
    std::vector<std::string> expectedSource = {
        "QCborValue AppConfig::toCbor() const {",
        "map.insert(\"name\", QCborValue(name));",
        "map.insert(\"debug\", debug.has_value() ? QCborValue(debug.value()) : QCborValue());",
        "map.insert(\"logLevels\", QCborArray::fromVariantList(logLevels));",
        "void AppConfig::fromCbor(const QCborValue& cbor) {",
        "auto map = cbor.toMap();"
    };
    
    for (const auto& file : files) {
        if (file.filename.find(".h") != std::string::npos) {
            checkGeneratedContent(file.content, expectedHeader);
        } else {
            checkGeneratedContent(file.content, expectedSource);
        }
    }
}

// 测试复杂继承关系的 Block 生成
TEST_F(GeneratorTest, GenerateComplexBlock) {
    std::string input = R"(
        // 基础任务
        block Task {
            string id;
            string name;
            Status status = Status::Initial;
            int32 priority = 0;
        }

        // 定时任务
        block TimedTask : Task {
            string cron;
            bool enabled = true;
            optional string lastRunTime;
        }

        // 数据同步任务
        block SyncTask : TimedTask {
            string source;
            string target;
            repeated string tables;
            map<string, string> mappings;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    std::vector<std::string> expectedHeader = {
        "// 基础任务",
        "class Task : public mota::BaseBlock {",
        "// 定时任务",
        "class TimedTask : public Task {",
        "// 数据同步任务",
        "class SyncTask : public TimedTask {",
        "QString source;",
        "QVector<QString> tables;",
        "QMap<QString, QString> mappings;"
    };
    
    std::vector<std::string> expectedSource = {
        "QCborValue Task::toCbor() const {",
        "QCborValue TimedTask::toCbor() const {",
        "auto parentMap = Task::toCbor().toMap();",
        "QCborValue SyncTask::toCbor() const {",
        "auto parentMap = TimedTask::toCbor().toMap();"
    };
    
    for (const auto& file : files) {
        if (file.filename.find(".h") != std::string::npos) {
            checkGeneratedContent(file.content, expectedHeader);
        } else {
            checkGeneratedContent(file.content, expectedSource);
        }
    }
}

// 测试命名空间和类型引用
TEST_F(GeneratorTest, GenerateWithNamespaceAndTypeRefs) {
    std::string input = R"(
        namespace app.models;

        enum LogLevel {
            Debug = 0;
            Info = 1;
            Warning = 2;
            Error = 3;
        }

        struct LogConfig {
            LogLevel defaultLevel = LogLevel::Info;
            repeated LogLevel enabledLevels = [LogLevel::Info, LogLevel::Error];
            map<string, LogLevel> moduleSettings;
        }

        block LogManager {
            LogConfig config;
            optional string logFile;
            repeated string modules;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    auto files = generator.generate();
    
    std::vector<std::string> expectedHeader = {
        "namespace app::models {",
        "enum class LogLevel {",
        "class LogConfig : public mota::BaseModel {",
        "    LogLevel defaultLevel = LogLevel::Info;",
        "    QVector<LogLevel> enabledLevels;",
        "    QMap<QString, LogLevel> moduleSettings;",
        "class LogManager : public mota::BaseBlock {",
        "    LogConfig config;",
        "    std::optional<QString> logFile;",
        "} // namespace app::models"
    };
    
    std::vector<std::string> expectedSource = {
        "namespace app::models {",
        "QString toString(LogLevel value)",
        "QCborValue LogConfig::toCbor()",
        "QCborValue LogManager::toCbor()",
        "} // namespace app::models"
    };
    
    for (const auto& file : files) {
        if (file.filename.find(".h") != std::string::npos) {
            checkGeneratedContent(file.content, expectedHeader);
        } else {
            checkGeneratedContent(file.content, expectedSource);
        }
    }
}

// 测试错误处理
TEST_F(GeneratorTest, HandleGenerationErrors) {
    // 测试循环继承
    std::string input = R"(
        block A : B {
            string name;
        }
        block B : A {
            int32 value;
        }
    )";
    
    auto ast = parseFile(input);
    mota::CppGenerator generator(ast);
    EXPECT_THROW(generator.generate(), std::runtime_error);
    
    // 测试未定义的类型引用
    input = R"(
        struct Config {
            UnknownType value;
        }
    )";
    
    ast = parseFile(input);
    generator = mota::CppGenerator(ast);
    EXPECT_THROW(generator.generate(), std::runtime_error);
}

// 添加更多测试... 