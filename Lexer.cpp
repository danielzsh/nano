//
// Created by danie on 4/30/2022.
//

#include "Lexer.h"
#include <iostream>
namespace Lexer {
    Lexer::Lexer(std::string input) {
        this->input = input;
        for (int i = 0; i < keywords.size(); i++) {
            kwd_index[keywords[i]] = i;
        }
    }
    char Lexer::nextChar() {
        if (++pos >= input.size()) return EOF;
        return input[pos];
    }
    int Lexer::gettok() {
        while (std::isspace(c)) {
            if (c == '\n') line++;
            c = nextChar();
        }
        if (std::isalpha(c)) {
            identifierStr = c;
            while (std::isalnum(c = nextChar())) {
                identifierStr += c;
            }
            for (int i = 0; i < keywords.size(); i++) {
                if (identifierStr == keywords[i]) return i + 1000; // so we don't conflict with ascii
            }
            return tok_identifier;
        }
        if (std::isdigit(c) || c == '.') {
            std::string numStr;
            do {
                numStr += c;
                c = nextChar();
            } while (std::isdigit(c) || c == '.');
            numVal = strtod(numStr.c_str(), nullptr);
            return tok_number;
        }
        if (c == '#') {
            // comment
            do {
                c = nextChar();
            } while (c != EOF && c != '\n' && c != '\r');
            if (c != EOF) {
                return gettok();
            }
        }
        if (c == EOF) return tok_eof;
        int thisChar = c;
        c = nextChar();
        return thisChar;
    }
} // Lexer