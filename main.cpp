#include <iostream>
#include "Interpreter.h"
#include <fstream>
std::string readFile(const std::string& filename)
{
    std::ifstream source(filename);
    return std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
}
int main() {
    std::string input = readFile("sample.nn");
    Interpreter::Interpreter interpreter(input);
    try {
        interpreter.interpret();
    } catch(std::string e) {
        std::cout << e << std::endl;
        return 1;
    }
    return 0;
}
