//
// Created by danie on 4/30/2022.
//

#pragma once
#include "Lexer.h"
#include "AST.h"
#include <cmath>
#include <set>
namespace Parser {

    class Parser {
    private:
        int tok;
        Lexer::Lexer lexer;
        bool isKwd(const std::string&);
        std::map<std::string, Type> varTypes;
        std::set<std::string> varNames;

    public:
        std::shared_ptr<Stack> st; // TODO: make st shared_ptr
        Parser(std::string input);
        ptr<Program> parseProgram();
        ptr<Main> parseMain();
        ptr<ASTNode<void>> parseStatement();
        node parseExpr();
        node parseTerm();
        node parseFactor();
    };

} // Parser
