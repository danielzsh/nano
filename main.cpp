#include <iostream>
#include "Runner.h"
#include <fstream>
std::string readFile(const std::string& filename)
{
    std::ifstream source(filename);
    return std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
}
int main() {
    std::string input = readFile("samples/sample.nn");
    Runner::Runner runner(input, true);
    try {
        runner.run();
    } catch(std::string e) {
        std::cout << e << std::endl;
        return 1;
    }
    return 0;
}
