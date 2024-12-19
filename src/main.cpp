#include "lexer.h"
#include <iostream>

int main() {
    std::string input = R"(
        @[ 
            file = "${app_path}/camera.cbor",
            level = global,
            format = cbor 
        ]
        struct Camera {
            int32 cam1Position;
        }
    )";

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Token: " << static_cast<int>(token.type) 
                  << " Value: " << token.value 
                  << " Line: " << token.line 
                  << " Column: " << token.column << std::endl;
    }

    return 0;
}
