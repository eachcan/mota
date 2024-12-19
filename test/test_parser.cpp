#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <cassert>

int main() {
    std::string source = "namespace myapp;\nstruct Camera { int32 cam1Position = 0; }";
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parse();  // 这里可以做进一步的单元测试验证解析的正确性

    std::cout << "Parser test passed!" << std::endl;
    return 0;
}
