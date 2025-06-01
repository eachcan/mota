#include <iostream>
#include "../generated/basic_types.h"

using namespace examples::basic;

int main() {
    BasicTypes basic;
    basic.boolValue = true;
    basic.float32Value = 3.14;
    basic.float64Value = 3.141592653589793;
    basic.int16Value = 32767;
    basic.int32Value = 2147483647;
    basic.int64Value = 9223372036854775807;
    basic.int8Value = -128;
    basic.stringValue = "Hello, Mota!";

    if (!basic.validate().isEmpty()) {
        std::cout << "Validation failed: " << basic.firstErrorMessage() << std::endl;
        return -1;
    }

    basic.save();

    std::cout << "BasicTypes saved to " << basic.toCbor() << std::endl;
}