//
// Created by danie on 4/30/2022.
//

#pragma once
#include "Lexer.h"
#include "AST.h"
#include <cmath>
#include <set>
namespace Runner {

    class Runner {
    private:
        int tok;
        Lexer::Lexer lexer;
        bool isKwd(const std::string&);
        std::map<std::string, Type> varTypes;
        std::set<std::string> varNames;
        bool jit = false;
        std::shared_ptr<Stack> st;

    public:
        Runner(std::string input, bool jit = false);
        ptr<Program> parseProgram();
        ptr<Main> parseMain();
        ptr<ASTNode<void>> parseStatement();
        node parseExpr();
        node parseTerm();
        node parseFactor();
        void run();
    };

} // Runner
