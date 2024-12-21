#include "parser.h"
#include "lexer.h"
#include <iostream>
#include <cassert>

int main() {
    std::string input = "int main() {\n"
                        "    return 0;\n"
                        "}\n";

    std::cout << "Input:\n" << input << std::endl;
    return 0;
}
