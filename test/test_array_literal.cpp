#include <gtest/gtest.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <windows.h>

using namespace mota;
using namespace mota::ast;
using namespace mota::parser;

class ArrayLiteralTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 设置控制台输出为UTF-8编码
        SetConsoleOutputCP(CP_UTF8);
    }
    
    void TearDown() override {
        // 清理工作
    }
    
    std::shared_ptr<Document> parse(const std::string& source) {
        lexer::Lexer lexer(source);
        Parser parser(lexer);
        return parser.parse();
    }
};

TEST_F(ArrayLiteralTest, Parse_EmptyArray) {
    std::string source = R"(
        struct S {
            repeated int32 values = [];
        }
    )";
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    auto s = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(s, nullptr);
    ASSERT_EQ(s->fields.size(), 1);
    
    auto arrayLiteral = dynamic_cast<ArrayLiteral*>(s->fields[0]->defaultValue.get());
    ASSERT_NE(arrayLiteral, nullptr);
    EXPECT_EQ(arrayLiteral->elements.size(), 0);
}

TEST_F(ArrayLiteralTest, Parse_ArrayWithLiterals) {
    std::string source = R"(
        struct S {
            repeated int32 values = [1, 2, 3];
        }
    )";
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    auto s = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(s, nullptr);
    ASSERT_EQ(s->fields.size(), 1);
    
    auto arrayLiteral = dynamic_cast<ArrayLiteral*>(s->fields[0]->defaultValue.get());
    ASSERT_NE(arrayLiteral, nullptr);
    EXPECT_EQ(arrayLiteral->elements.size(), 3);
    
    // 检查第一个元素
    auto literal1 = dynamic_cast<Literal*>(arrayLiteral->elements[0].get());
    ASSERT_NE(literal1, nullptr);
    EXPECT_EQ(std::get<int64_t>(literal1->value), 1);
}

TEST_F(ArrayLiteralTest, Parse_ArrayWithAnnotations) {
    std::string source = R"(
        annotation FieldAnnotation {
            string description;
        }
        
        struct S {
            @FieldAnnotation(description = "这是一个字符串数组字段")
            repeated string modes = ["normal", "debug"];
        }
    )";
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    auto s = dynamic_cast<Struct*>(doc->declarations[1].get());
    ASSERT_NE(s, nullptr);
    ASSERT_EQ(s->fields.size(), 1);
    
    // 检查字段有注解
    EXPECT_EQ(s->fields[0]->annotations.size(), 1);
    EXPECT_EQ(s->fields[0]->annotations[0]->name, "FieldAnnotation");
    
    // 检查字段默认值是数组字面量
    auto arrayLiteral = dynamic_cast<ArrayLiteral*>(s->fields[0]->defaultValue.get());
    ASSERT_NE(arrayLiteral, nullptr);
    EXPECT_EQ(arrayLiteral->elements.size(), 2);
    
    // 检查第一个元素是字符串字面量
    auto literal1 = dynamic_cast<Literal*>(arrayLiteral->elements[0].get());
    ASSERT_NE(literal1, nullptr);
    EXPECT_EQ(std::get<std::string>(literal1->value), "normal");
}

TEST_F(ArrayLiteralTest, Parse_NestedArrays) {
    std::string source = R"(
        struct S {
            repeated repeated int32 matrix = [[1, 2], [3, 4]];
        }
    )";
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    auto s = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(s, nullptr);
    ASSERT_EQ(s->fields.size(), 1);
    
    auto outerArray = dynamic_cast<ArrayLiteral*>(s->fields[0]->defaultValue.get());
    ASSERT_NE(outerArray, nullptr);
    EXPECT_EQ(outerArray->elements.size(), 2);
    
    // 检查第一个内部数组
    auto innerArray1 = dynamic_cast<ArrayLiteral*>(outerArray->elements[0].get());
    ASSERT_NE(innerArray1, nullptr);
    EXPECT_EQ(innerArray1->elements.size(), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 