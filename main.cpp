#include <iostream>
#include "Runner.h"
#include <fstream>
std::string readFile(const std::string& filename)
{
    std::ifstream source(filename);
    return std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
}
int main() {
    std::string input = readFile("samples/sample2.nn");
    Runner::Runner runner(input, false);
    try {
        runner.run();
    } catch(std::string e) {
        std::cout << e << std::endl;
        return 1;
    }
    return 0;
}
