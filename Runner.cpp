//
// Created by danie on 4/30/2022.
//

#include "Runner.h"
namespace Runner {
    bool Runner::isKwd(const std::string& kwd) {
        return (tok - 1000 == lexer.kwd_index[kwd]);
    }
    Runner::Runner(std::string input, bool jit) : lexer(input, jit) {
        tok = lexer.gettok();
        this->jit = jit;
        st = std::make_shared<Stack>();
    }

    void Runner::run() {
        ptr<Program> prgm = parseProgram();
        if (!jit) prgm->visit();
    }
    ptr<Program> Runner::parseProgram() {
        ptr<Program> prgm = std::make_unique<Program>();
        if (isKwd("start")) {
            prgm->main = parseMain();
        }
        else throw std::string("Expected function definition or keyword start.");
        return prgm;
    }
    ptr<Main> Runner::parseMain() {
        ptr<Main> main = std::make_unique<Main>();
        while ((tok = lexer.gettok()) != tok_eof) {
            if (jit) parseStatement()->visit();
            else main->statements.push_back(std::move(parseStatement())); // add statement to body
        }
        return main;
    }
    ptr<ASTNode<void>> Runner::parseStatement() {
        if (isKwd("assign")) {
            tok = lexer.gettok();
            node rhs = std::move(parseExpr());
            if (!isKwd("to")) throw std::string("Expected literal \'to\' after assign on line " + std::to_string(lexer.line));
            tok = lexer.gettok();
            if (tok != tok_identifier) throw std::string("Expected variable name after assign on line " +
                                                         std::to_string(lexer.line));
            std::string name = lexer.identifierStr;
            varTypes[name] = static_cast<Type>(rhs.index());
            varNames.insert(name);
            if (varTypes[name] == Int) {
                return std::make_unique<Assign<int>>(std::make_unique<Var<int>>(name, st), std::move(GETINT(rhs)));
            }
            // TODO: add other types
        }
        if (isKwd("print")) {
            ptr<Print> print = std::make_unique<Print>();
            tok = lexer.gettok();
            if (tok != '(') throw std::string("Expected parentheses after print on line " + std::to_string(lexer.line));
            tok = lexer.gettok();
            while (tok != ')') {
                print->exprs.push_back(std::move(parseExpr()));
                if (tok == ',') tok = lexer.gettok();
                else if (tok != ')') throw std::string("Expected , or () in print statement on line " + std::to_string(lexer.line));

            }
            return print;
        }
        else throw std::string("Unrecognized statement on line " + std::to_string(lexer.line));
    }
    // TODO: operator precedence parsing?
    node Runner::parseExpr() {
        node Node = std::move(parseTerm());
        while (tok == '+' || tok == '-') {
            char op = tok;
            tok = lexer.gettok();
            node rhs = std::move(parseTerm());
            if (Node.index() == Int && rhs.index() == Int) {
                Node = std::make_unique<BinOp<int, int, int>>(std::move(GETINT(Node)), std::move(GETINT(rhs)), op);
            }
            if (Node.index() == String && rhs.index() == Int) {
                Node = std::make_unique<BinOp<std::string, int, std::string>>(std::move(GETSTRING(Node)), std::move(GETINT(rhs)), op);
            }
            if (Node.index() == Int && rhs.index() == String) {
                Node = std::make_unique<BinOp<int, std::string, std::string>>(std::move(GETINT(Node)), std::move(GETSTRING(rhs)), op);
            }
            if (Node.index() == String && rhs.index() == String) {
                Node = std::make_unique<BinOp<std::string, std::string, std::string>>(std::move(GETSTRING(Node)), std::move(GETSTRING(rhs)), op);
            }
            // TODO: add support for other types
        }
        return Node;
    }
    node Runner::parseTerm() {
        node Node = std::move(parseFactor());
        while (tok == '*' || tok == '/') {
            char op = tok;
            tok = lexer.gettok();
            node rhs = std::move(parseFactor());
            if (Node.index() == Int && rhs.index() == Int) {
                Node = std::make_unique<BinOp<int, int, int>>(std::move(GETINT(Node)), std::move(GETINT(rhs)), op);
            }
            if (Node.index() == String && rhs.index() == Int) {
                Node = std::make_unique<BinOp<std::string, int, std::string>>(std::move(GETSTRING(Node)), std::move(GETINT(rhs)), op);
            }
            if (Node.index() == Int && rhs.index() == String) {
                Node = std::make_unique<BinOp<int, std::string, std::string>>(std::move(GETINT(Node)), std::move(GETSTRING(rhs)), op);
            }
            if (Node.index() == String && rhs.index() == String) {
                Node = std::make_unique<BinOp<std::string, std::string, std::string>>(std::move(GETSTRING(Node)), std::move(GETSTRING(rhs)), op);
            }
            // TODO: add support for other types
        }
        return Node;
    }
    node Runner::parseFactor() {
        node Node;
        if (tok == tok_number) {
            double num = lexer.numVal;
            tok = lexer.gettok();
            if (num == std::floor(num)) return std::make_unique<Val<int>>(num);
            return std::make_unique<Val<double>>(num);
        }
        else if (tok == tok_identifier) {
            std::string varName = lexer.identifierStr;
            if (varNames.find(varName) == varNames.end()) {
                throw std::string("Use of a variable that has not been defined: " + varName);
            }
            tok = lexer.gettok();
            if (varTypes[varName] == Int) {
                return std::make_unique<Var<int>>(varName, st);
            }
            // TODO: add support for other types
        }
        else if (tok == tok_string) {
            std::string str = lexer.identifierStr;
            tok = lexer.gettok();
            return std::make_unique<Val<std::string>>(str);
        }
    }
} // Runner