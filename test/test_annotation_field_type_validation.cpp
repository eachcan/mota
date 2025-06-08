#include <gtest/gtest.h>
#include "parser.h"
#include "lexer.h"
#include "syntax_checker.h"
#include "ast.h"
#include <windows.h>

using namespace mota;
using namespace mota::ast;
using namespace mota::parser;
using namespace mota::checker;

class AnnotationFieldTypeValidationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 设置控制台输出为UTF-8编码
        SetConsoleOutputCP(CP_UTF8);
    }
    
    std::unique_ptr<Document> parse(const std::string& source) {
        lexer::Lexer lexer(source);
        Parser parser(lexer);
        return parser.parse();
    }
};

TEST_F(AnnotationFieldTypeValidationTest, AllowAnnotationAsAnnotationFieldType) {
    std::string source = R"(
        annotation MyAnnotation {
            string value;
        }
        
        annotation ValidAnnotation {
            MyAnnotation field;  // 这应该被允许
            repeated MyAnnotation items;  // 这也应该被允许
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    SyntaxChecker checker;
    auto diagnostics = checker.check(*doc, "test.mota");
    
    // 不应该有注解字段类型相关的错误
    for (const auto& diag : diagnostics) {
        EXPECT_TRUE(diag.message.find("注解字段只能使用内置类型或其他注解类型") == std::string::npos)
            << "不应该有注解字段类型错误: " << diag.message;
    }
}

TEST_F(AnnotationFieldTypeValidationTest, RejectStructAsAnnotationFieldType) {
    std::string source = R"(
        struct MyStruct {
            string value;
        }
        
        annotation InvalidAnnotation {
            MyStruct field;  // 这应该被拒绝
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    SyntaxChecker checker;
    auto diagnostics = checker.check(*doc, "test.mota");
    
    // 应该有一个错误：注解字段只能使用内置类型或其他注解类型
    ASSERT_GT(diagnostics.size(), 0);
    bool foundError = false;
    for (const auto& diag : diagnostics) {
        if (diag.message.find("注解字段只能使用内置类型或其他注解类型") != std::string::npos) {
            foundError = true;
            EXPECT_EQ(diag.level, SyntaxDiagnostic::Level::Error);
            break;
        }
    }
    EXPECT_TRUE(foundError) << "应该检测到注解字段类型错误";
}

TEST_F(AnnotationFieldTypeValidationTest, RejectAnnotationAsStructFieldType) {
    std::string source = R"(
        annotation MyAnnotation {
            string value;
        }
        
        struct InvalidStruct {
            MyAnnotation field;  // 这应该被拒绝
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    SyntaxChecker checker;
    auto diagnostics = checker.check(*doc, "test.mota");
    
    // 应该有一个错误：不能将注解用作字段类型
    ASSERT_GT(diagnostics.size(), 0);
    bool foundError = false;
    for (const auto& diag : diagnostics) {
        if (diag.message.find("不能将注解用作字段类型") != std::string::npos) {
            foundError = true;
            EXPECT_EQ(diag.level, SyntaxDiagnostic::Level::Error);
            break;
        }
    }
    EXPECT_TRUE(foundError) << "应该检测到struct字段类型错误";
}

TEST_F(AnnotationFieldTypeValidationTest, RejectStructAsStructFieldType) {
    std::string source = R"(
        struct MyStruct {
            string value;
        }
        
        struct InvalidStruct {
            MyStruct field;  // 这应该被拒绝
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    SyntaxChecker checker;
    auto diagnostics = checker.check(*doc, "test.mota");
    
    // 应该有一个错误：不能将struct用作字段类型
    ASSERT_GT(diagnostics.size(), 0);
    bool foundError = false;
    for (const auto& diag : diagnostics) {
        if (diag.message.find("不能将struct用作字段类型") != std::string::npos) {
            foundError = true;
            EXPECT_EQ(diag.level, SyntaxDiagnostic::Level::Error);
            break;
        }
    }
    EXPECT_TRUE(foundError) << "应该检测到struct字段类型错误";
}

TEST_F(AnnotationFieldTypeValidationTest, AllowValidFieldTypes) {
    std::string source = R"(
        enum MyEnum {
            VALUE1 = 0;
            VALUE2 = 1;
        }
        
        block MyBlock {
            string name;
        }
        
        annotation BaseAnnotation {
            string description;
        }
        
        annotation ValidAnnotation {
            string text;
            int32 number;
            bool flag;
            repeated string items;
            BaseAnnotation nested;  // 注解可以包含其他注解
            repeated BaseAnnotation annotations;
        }
        
        struct ValidStruct {
            string text;
            int32 number;
            MyEnum enumField;
            MyBlock blockField;
            repeated string items;
        }
        
        block ValidBlock {
            string text;
            MyEnum enumField;
            MyBlock nestedBlock;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    SyntaxChecker checker;
    auto diagnostics = checker.check(*doc, "test.mota");
    
    // 不应该有任何字段类型相关的错误
    for (const auto& diag : diagnostics) {
        EXPECT_TRUE(diag.message.find("字段类型") == std::string::npos ||
                   diag.message.find("字段类型未定义") != std::string::npos) 
            << "不应该有字段类型错误: " << diag.message;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 