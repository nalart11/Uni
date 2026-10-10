//
// Created by nalart11 on 10/10/26.
//

#include "Parser.h"

#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Expression> Parser::parseExpression() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected number, but reached end of input");
    }
    if (tokens[pos].type == TokenType::Number) {
        auto exp = std::make_unique<NumberExpression>(std::stoi(tokens[pos].value));
        pos++;
        return exp;
    }
    throw std::runtime_error("Parser error: expected number");
}

NumberExpression Parser::parseNumber() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected number, but reached end of input");
    }
    if (tokens[pos].type != TokenType::Number) {
        throw std::runtime_error("Parser error: expected number");
    }
    auto exp = NumberExpression(std::stoi(tokens[pos].value));
    pos++;
    return exp;
}
