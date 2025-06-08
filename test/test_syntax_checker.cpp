#include <gtest/gtest.h>
#include "parser.h"
#include "syntax_checker.h"
#include <memory>
#include <string>
#include <iostream>
#include <windows.h>

using namespace mota;

class SyntaxCheckerTest : public ::testing::Test {
protected:
    std::unique_ptr<ast::Document> parse(const std::string& source) {
        lexer::Lexer lexer(source);
        parser::Parser parser(lexer);
        return parser.parse();
    }
};

TEST_F(SyntaxCheckerTest, NoErrorForSimpleStruct) {
    std::string source = R"(
        struct Person {
            string name;
            int32 age;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, FieldTypeNotExist) {
    std::string source = R"(
        struct S {
            NotExistType a;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("NotExistType") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, AnnotationNotExist) {
    std::string source = R"(
        @NotExist
        struct S { int32 a; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("NotExist") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, BlockInheritNotExist) {
    std::string source = R"(
        block B : NotExistBlock {
            int32 a;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("NotExistBlock") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, StructInheritIllegalType) {
    std::string source = R"(
        enum E { A = 0; }
        struct S : E {
            int32 a;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("继承") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, DuplicateDefinition) {
    std::string source = R"(
        struct S { int32 a; }
        struct S { int32 b; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("重复") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, NameConflict) {
    std::string source = R"(
        struct S { int32 a; }
        enum S { A = 0; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_EQ(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("冲突") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, CircularInheritance) {
    std::string source = R"(
        block A : B { int32 x; }
        block B : A { int32 y; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("循环") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, DuplicateEnumValue) {
    std::string source = R"(
        enum E {
            A = 0;
            B = 1;
            A = 2;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("重复") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, DuplicateFieldName) {
    std::string source = R"(
        struct S {
            int32 a;
            string a;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("重复") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, ValidMapType) {
    std::string source = R"(
        struct S {
            map string values;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, NestedContainerType) {
    std::string source = R"(
        struct S {
            repeated optional int32 values;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, FieldAnnotationWithParams) {
    std::string source = R"(
        annotation Range { int32 min; int32 max; }
        struct S {
            @Range(min = 0, max = 100)
            int32 score;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, StructInheritFromBlock) {
    std::string source = R"(
        block Base { int32 id; }
        struct Derived : Base { string name; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, BlockInheritFromBlock) {
    std::string source = R"(
        block Base { int32 id; }
        block Derived : Base { string name; }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, AnnotationFieldTypeNotExist) {
    std::string source = R"(
        annotation Range {
            NotExistType min;
            int32 max;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("NotExistType") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, AnnotationAsFieldType) {
    std::string source = R"(
        annotation Range { int32 min; int32 max; }
        struct S {
            Range range;  // 不允许
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("注解用作字段类型") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, StructAsFieldType) {
    std::string source = R"(
        struct Inner { int32 value; }
        struct Outer {
            Inner inner;  // 不允许
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("struct用作字段类型") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, BlockStructAsAnnotationFieldType) {
    std::string source = R"(
        block B { int32 x; }
        annotation Ann {
            B blockField;  // 不允许
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("注解字段只能使用内置类型或其他注解类型") != std::string::npos);
}

TEST_F(SyntaxCheckerTest, ValidAnnotationFieldTypes) {
    std::string source = R"(
        annotation Range {
            int32 min;
            int32 max;
            string description;
            bool required;
        }
        struct S {
            @Range(min = 0, max = 100, description = "score", required = true)
            int32 score;
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, ValidBlockFieldTypes) {
    std::string source = R"(
        enum Status { Active = 0; Inactive = 1; }
        block Base { int32 id; }
        struct S {
            Status status;    // enum 类型可用
            Base base;        // block 类型可用
            int32 value;      // 内置类型可用
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    EXPECT_TRUE(diagnostics.empty());
}

TEST_F(SyntaxCheckerTest, DuplicateAnnotationFieldName) {
    std::string source = R"(
        annotation Range {
            int32 min;
            int32 max;
            int32 min;  // 重复
        }
    )";
    auto doc = parse(source);
    checker::SyntaxChecker checker;
    auto diagnostics = checker.check(*doc);
    ASSERT_GE(diagnostics.size(), 1);
    EXPECT_EQ(diagnostics[0].level, checker::SyntaxDiagnostic::Level::Error);
    EXPECT_TRUE(diagnostics[0].message.find("注解字段名重复") != std::string::npos);
}

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 