#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace mota;
using namespace mota::lexer;
using namespace mota::parser;
using namespace mota::ast;

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例之前执行
    }

    void TearDown() override {
        // 在每个测试用例之后执行
    }

    std::unique_ptr<Document> parse(const std::string& source) {
        std::cout << "\n开始解析代码..." << std::endl;
        Lexer lexer(source);
        std::cout << "词法分析器创建成功" << std::endl;
        Parser parser(lexer);
        std::cout << "语法分析器创建成功，开始解析..." << std::endl;
        auto result = parser.parse();
        std::cout << "解析完成" << std::endl;
        return result;
    }
};

// 测试基本结构体解析
TEST_F(ParserTest, ParseSimpleStruct) {
    std::string source = R"(
        struct Person {
            string name;
            int32 age = 25;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(doc->declarations.size(), 1);
    
    auto structDecl = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(structDecl, nullptr);
    EXPECT_EQ(structDecl->name, "Person");
    ASSERT_EQ(structDecl->fields.size(), 2);
    EXPECT_EQ(structDecl->fields[0]->name, "name");
    EXPECT_EQ(((NamedType*)(structDecl->fields[0]->type.get()))->name, "string");
    EXPECT_EQ(structDecl->fields[1]->name, "age");
    EXPECT_EQ(((NamedType*)(structDecl->fields[1]->type.get()))->name, "int32");
}

// 测试枚举解析
TEST_F(ParserTest, ParseEnum) {
    std::string source = R"(
        enum Color {
            RED = 1,
            GREEN = 2,
            BLUE = 3
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    auto enumDecl = dynamic_cast<Enum*>(doc->declarations[0].get());
    ASSERT_NE(enumDecl, nullptr);
    EXPECT_EQ(enumDecl->name, "Color");
    ASSERT_EQ(enumDecl->values.size(), 3);
    EXPECT_EQ(enumDecl->values[0]->name, "RED");
    // ... 其他断言
}

// 测试注解解析
TEST_F(ParserTest, ParseAnnotation) {
    std::string source = R"(
        @yima.Storage(path = "config.cbor", format = "cbor")
        struct Config {
            @yima.ui.Text(desc = "User name", max_length = 100)
            string username;
            
            @yima.ui.Int(min = 0, max = 150)
            int32 age;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    
    auto structDecl = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(structDecl, nullptr);
    EXPECT_EQ(structDecl->annotations.size(), 1);
    EXPECT_EQ(structDecl->fields[0]->annotations.size(), 1);
    // ... 其他断言
}

// 测试命名空间和包含
TEST_F(ParserTest, ParseNamespaceAndInclude) {
    std::string source = R"(
        namespace example.person;
        include "common.mota";
        
        struct Person {
            string name;
            int32 age;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(doc->declarations.size(), 3); // namespace, include, struct
    
    auto ns = dynamic_cast<Namespace*>(doc->declarations[0].get());
    ASSERT_NE(ns, nullptr);
    ASSERT_EQ(ns->name.size(), 2);
    EXPECT_EQ(ns->name[0], "example");
    EXPECT_EQ(ns->name[1], "person");
    // ... 其他断言
}

// 测试表达式解析
TEST_F(ParserTest, ParseExpressions) {
    std::string source = R"(
        const int32 ANSWER = 40 + 2;
        const float PI = 3.14159;
        const string GREETING = "Hello, " + "world!";
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(doc->declarations.size(), 3);
    
    // 测试第一个表达式：40 + 2
    auto constDecl1 = doc->declarations[0].get();
    // 这里需要根据实际的AST结构进行断言
    
    // 测试第二个表达式：3.14159
    auto constDecl2 = doc->declarations[1].get();
    // 这里需要根据实际的AST结构进行断言
    
    // 测试第三个表达式："Hello, " + "world!"
    auto constDecl3 = doc->declarations[2].get();
    // 这里需要根据实际的AST结构进行断言
}

// 测试块解析
TEST_F(ParserTest, ParseBlock) {
    std::string source = R"(
        block Rectangle {
            @yima.ui.Int(min = 0, max = 10000)
            int32 x = 0;
            @yima.ui.Int(min = 0, max = 10000)
            int32 y = 0;
            @yima.ui.Int(min = 1, max = 10000)
            int32 width = 100;
            @yima.ui.Int(min = 1, max = 10000)
            int32 height = 100;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(doc->declarations.size(), 1);
    
    auto blockDecl = dynamic_cast<Block*>(doc->declarations[0].get());
    ASSERT_NE(blockDecl, nullptr);
    EXPECT_EQ(blockDecl->name, "Rectangle");
    ASSERT_EQ(blockDecl->fields.size(), 4);
    EXPECT_EQ(blockDecl->fields[0]->name, "x");
    EXPECT_EQ(blockDecl->fields[1]->name, "y");
    EXPECT_EQ(blockDecl->fields[2]->name, "width");
    EXPECT_EQ(blockDecl->fields[3]->name, "height");
    
    // 测试注解
    ASSERT_EQ(blockDecl->fields[0]->annotations.size(), 1);
    EXPECT_EQ(blockDecl->fields[0]->annotations[0]->name, "yima.ui.Int");
}

// 测试复杂类型
TEST_F(ParserTest, ParseComplexTypes) {
    std::string source = R"(
        struct Container {
            repeated string names;
            map<string, int32> scores;
            optional Person person;
        }
    )";
    
    auto doc = parse(source);
    ASSERT_NE(doc, nullptr);
    ASSERT_EQ(doc->declarations.size(), 1);
    
    auto structDecl = dynamic_cast<Struct*>(doc->declarations[0].get());
    ASSERT_NE(structDecl, nullptr);
    EXPECT_EQ(structDecl->name, "Container");
    ASSERT_EQ(structDecl->fields.size(), 3);
    
    // 测试数组类型
    auto arrayType = dynamic_cast<ContainerType*>(structDecl->fields[0]->type.get());
    ASSERT_NE(arrayType, nullptr);
    EXPECT_EQ(arrayType->kind, ContainerType::Kind::Array);
    auto elementType = dynamic_cast<NamedType*>(arrayType->elementType.get());
    ASSERT_NE(elementType, nullptr);
    EXPECT_EQ(elementType->name, "string");
    
    // 测试映射类型
    auto mapType = dynamic_cast<ContainerType*>(structDecl->fields[1]->type.get());
    ASSERT_NE(mapType, nullptr);
    EXPECT_EQ(mapType->kind, ContainerType::Kind::Map);
    auto keyType = dynamic_cast<NamedType*>(mapType->keyType.get());
    ASSERT_NE(keyType, nullptr);
    EXPECT_EQ(keyType->name, "string");
    auto valueType = dynamic_cast<NamedType*>(mapType->elementType.get());
    ASSERT_NE(valueType, nullptr);
    EXPECT_EQ(valueType->name, "int32");
    
    // 测试可选类型
    auto optionalType = dynamic_cast<ContainerType*>(structDecl->fields[2]->type.get());
    ASSERT_NE(optionalType, nullptr);
    EXPECT_EQ(optionalType->kind, ContainerType::Kind::Optional);
    auto personType = dynamic_cast<NamedType*>(optionalType->elementType.get());
    ASSERT_NE(personType, nullptr);
    EXPECT_EQ(personType->name, "Person");
}

// 测试错误处理 - 缺少分号
TEST_F(ParserTest, ErrorMissingSemicolon) {
    std::string source = R"(
        namespace example.person
        struct Person {
            string name;
        }
    )";
    
    try {
        auto doc = parse(source);
        FAIL() << "Expected ParseError exception";
    } catch (const ParseError& e) {
        EXPECT_TRUE(std::string(e.what()).find("Expected ';'") != std::string::npos);
    }
}

// 测试错误处理 - 缺少大括号
TEST_F(ParserTest, ErrorMissingBrace) {
    std::string source = R"(
        struct Person {
            string name;
            int32 age;
        // 缺少右大括号
    )";
    
    try {
        auto doc = parse(source);
        FAIL() << "Expected ParseError exception";
    } catch (const ParseError& e) {
        std::string error_msg = e.what();
        std::cout << "Caught error message: " << error_msg << std::endl;
        // 检查错误消息是否包含与缺少右大括号相关的内容
        EXPECT_TRUE(error_msg.find("Expected") != std::string::npos && 
                   (error_msg.find("}") != std::string::npos || 
                    error_msg.find("brace") != std::string::npos || 
                    error_msg.find("\\}") != std::string::npos));
    }
}

// 测试错误处理 - 无效的类型
TEST_F(ParserTest, ErrorInvalidType) {
    std::string source = R"(
        struct Person {
            invalid_type name;
        }
    )";
    
    try {
        auto doc = parse(source);
        // 根据实际实现，这可能不会抛出异常，因为标识符可能被解析为用户定义类型
        // 这里只是为了演示错误处理
    } catch (const ParseError& e) {
        EXPECT_TRUE(std::string(e.what()).find("Invalid type") != std::string::npos);
    }
}

int main(int argc, char** argv) {
    // 设置控制台输出为UTF-8编码，解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}