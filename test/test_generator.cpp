#include <gtest/gtest.h>
#include "parser.h"
#include "generator.h"
#include <sstream>
#include <filesystem>
#include <fstream>

using namespace mota;

class GeneratorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 尝试不同的模板目录路径
        std::vector<std::string> possiblePaths = {
            "template/yima-cpp",
            "../template/yima-cpp", 
            "../../template/yima-cpp",
            "../../../template/yima-cpp",
            "../../../../template/yima-cpp"
        };
        
        for (const auto& path : possiblePaths) {
            // 首先尝试 config.json5
            std::ifstream testFile5(path + "/config.json5");
            if (testFile5.is_open()) {
                templateDir_ = path;
                testFile5.close();
                break;
            }
            
            // 如果 config.json5 不存在，尝试 config.json
            std::ifstream testFile(path + "/config.json");
            if (testFile.is_open()) {
                templateDir_ = path;
                testFile.close();
                break;
            }
        }
        
        if (templateDir_.empty()) {
            templateDir_ = "template/yima-cpp"; // 默认路径
        }
        
        generator_ = std::make_shared<generator::Generator>();
        
        // 初始化生成器
        bool success = generator_->initialize(templateDir_);
        ASSERT_TRUE(success) << "Failed to initialize generator with template directory: " << templateDir_;
    }
    
    std::shared_ptr<ast::Document> parse(const std::string& source) {
        lexer::Lexer lexer(source);
        parser::Parser parser(lexer);
        return parser.parse();
    }
    
    std::string templateDir_;
    std::shared_ptr<generator::Generator> generator_;
};

TEST_F(GeneratorTest, GenerateSimpleStruct) {
    std::string source = R"(
        struct Person {
            string name;
            int32 age;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    std::string result = generator_->generateCode(doc, "file");
    
    // 检查生成的代码包含期望的内容
    EXPECT_TRUE(result.find("class MODEL_EXPORT Person") != std::string::npos);
    EXPECT_TRUE(result.find("QString name_") != std::string::npos);
    EXPECT_TRUE(result.find("int32_t age_") != std::string::npos);
    EXPECT_TRUE(result.find("getName()") != std::string::npos);
    EXPECT_TRUE(result.find("setAge(") != std::string::npos);
    
    std::cout << "Generated struct code:\n" << result << std::endl;
}

TEST_F(GeneratorTest, GenerateSimpleBlock) {
    std::string source = R"(
        block Rectangle {
            int16 width;
            int16 height;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    std::string result = generator_->generateCode(doc, "file");
    
    // 检查生成的代码包含期望的内容
    EXPECT_TRUE(result.find("class MODEL_EXPORT Rectangle") != std::string::npos);
    EXPECT_TRUE(result.find("IBlock") != std::string::npos);
    EXPECT_TRUE(result.find("int16_t width_") != std::string::npos);
    EXPECT_TRUE(result.find("int16_t height_") != std::string::npos);
    EXPECT_TRUE(result.find("toCbor()") != std::string::npos);
    EXPECT_TRUE(result.find("fromCbor(") != std::string::npos);
    
    std::cout << "Generated block code:\n" << result << std::endl;
}

TEST_F(GeneratorTest, GenerateEnum) {
    std::string source = R"(
        enum Color {
            Red = 0;
            Green = 1;
            Blue = 2;
        }
        
        enum Status {
            Unknown = -1;
            Active = 1;
            Inactive = 0;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    std::string result = generator_->generateCode(doc, "file");
    
    // 检查生成的代码包含期望的内容
    EXPECT_TRUE(result.find("Color") != std::string::npos);
    EXPECT_TRUE(result.find("Red = 0") != std::string::npos);
    EXPECT_TRUE(result.find("Green = 1") != std::string::npos);
    EXPECT_TRUE(result.find("Blue = 2") != std::string::npos);
    
    EXPECT_TRUE(result.find("Status") != std::string::npos);
    EXPECT_TRUE(result.find("Unknown = -1") != std::string::npos);
    EXPECT_TRUE(result.find("Active = 1") != std::string::npos);
    EXPECT_TRUE(result.find("Inactive = 0") != std::string::npos);
    
    std::cout << "Generated enum code:\n" << result << std::endl;
}

TEST_F(GeneratorTest, GenerateAnnotation) {
    std::string source = R"(
        annotation Range {
            int32 min;
            int32 max;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    std::string result = generator_->generateCode(doc, "file");
    
    // 检查生成的代码包含期望的内容
    EXPECT_TRUE(result.find("class MODEL_EXPORT Range") != std::string::npos);
    EXPECT_TRUE(result.find("IAnnotation") != std::string::npos);
    EXPECT_TRUE(result.find("int32_t min_") != std::string::npos);
    EXPECT_TRUE(result.find("int32_t max_") != std::string::npos);
    EXPECT_TRUE(result.find("getMin()") != std::string::npos);
    EXPECT_TRUE(result.find("setMax(") != std::string::npos);
    
    std::cout << "Generated annotation code:\n" << result << std::endl;
}

TEST_F(GeneratorTest, GenerateWithNamespace) {
    std::string source = R"(
        namespace yima;
        
        block Point {
            int16 x;
            int16 y;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    std::string result = generator_->generateCode(doc, "file");
    
    // 检查生成的代码包含期望的内容
    EXPECT_TRUE(result.find("namespace yima") != std::string::npos);
    EXPECT_TRUE(result.find("} // namespace yima") != std::string::npos);
    EXPECT_TRUE(result.find("class MODEL_EXPORT Point") != std::string::npos);
    
    std::cout << "Generated code with namespace:\n" << result << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 