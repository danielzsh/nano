//
// Created by danie on 5/1/2022.
//

#pragma once
#include "Parser.h"
namespace Interpreter {

    class Interpreter {
    private:
        Parser::Parser parser;
        std::shared_ptr<Stack> st;
    public:
        Interpreter(std::string input);
        void interpret();
    };

} // Interpreter

