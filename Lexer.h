//
// Created by nalart11 on 10/9/26.
//
#pragma once
#include <string>
#include <vector>

#include "Token.h"


class Lexer {
    public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

    private:
    std::string source;
    std::size_t pos;
    std::vector<Token> tokens;

    Token readNumber();
    Token readIdentifier();

    static bool isOperator(char c);
    static bool isKeyword(const std::string& value);
};

