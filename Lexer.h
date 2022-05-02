//
// Created by danie on 4/30/2022.
//

#pragma once
#include <string>
#include <vector>
#include <map>
enum Token {
    tok_identifier = -1,
    tok_number = -2,
    tok_eof = -3
};
namespace Lexer {

    class Lexer {
    private:
        char c = ' ';
        char nextChar();
    public:
        Lexer(std::string input);
        int line = 1;
        std::string identifierStr = "";
        double numVal = 0;
        std::vector<std::string> keywords =
                {"print", "start", "export", "import", "from", "is", "def", "assign", "to"};
        std::map<std::string, int> kwd_index;
        std::string input;
        int pos = -1;
        int gettok();
    };

} // Lexer

