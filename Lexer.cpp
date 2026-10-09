//
// Created by nalart11 on 10/9/26.
//

#include "Lexer.h"

#include <cctype>
#include <vector>
#include <iostream>

Lexer::Lexer(const std::string& source)
    : source(source),
      pos(0) {
}

bool Lexer::isOperator(const char c) {
    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '%' ||
           c == '^';
}

bool Lexer::isKeyword(const std::string& value) {
    return value == "print";
}

std::vector<Token> Lexer::tokenize() {
    while (pos < source.length()) {
        if (isdigit(source[pos])) {
            std::string value;
            while (pos < source.length() && isdigit(source[pos])) {
                value += source[pos];
                pos++;
            }
            Token token{.type = TokenType::Number, .value = value};
            tokens.push_back(token);
        } else if (isalpha(source[pos]) || source[pos] == '_') {
            std::string value;
            while (pos < source.length() && (isalpha(source[pos]) || isdigit(source[pos]) || source[pos] == '_')) {
                value += source[pos];
                pos++;
            }
            Token token;
            if (isKeyword(value)) {
                token = {.type = TokenType::Keyword, .value = value};
            } else {
                token = {.type = TokenType::Identifier, .value = value};
            }
            tokens.push_back(token);
        } else if (isOperator(source[pos])) {
            std::string value;
            value += source[pos];
            pos++;
            Token token{.type = TokenType::Operator, .value = value};
            tokens.push_back(token);
        } else if (isspace(source[pos])) {
            pos++;
        } else {
            std::cout << "Unexpected character \'" << source[pos] << "\' at pos " << pos + 1 << std::endl;
            pos++;
        }
    }
    return tokens;
}
