#include <iostream>
#include "Runner.h"
#include <fstream>
std::string readFile(const std::string& filename)
{
    std::ifstream source(filename);
    return std::string((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
}
int main(int argc, char** argv) {
    bool jit = false;
    std::string input;
    if (argc > 1) input = readFile(argv[1]);
    else jit = true;
    Runner::Runner runner(input, jit);
    try {
        runner.run();
    } catch(std::string e) {
        std::cout << e << std::endl;
        return 1;
    }
    return 0;
}
