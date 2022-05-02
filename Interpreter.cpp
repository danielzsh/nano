//
// Created by danie on 5/1/2022.
//

#include "Interpreter.h"

namespace Interpreter {
    Interpreter::Interpreter(std::string input) : parser(input) {
        st = std::make_shared<Stack>();
        parser.st = st;
    }

    void Interpreter::interpret() {
        ptr<Program> prgrm = std::move(parser.parseProgram());
        prgrm->visit();
    }
} // Interpreter