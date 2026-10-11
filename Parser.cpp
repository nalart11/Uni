//
// Created by nalart11 on 10/10/26.
//

#include "Parser.h"
#include <stdexcept>

#include "ast/BinaryExpression.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Expression> Parser::parseExpression() {
    auto left = parseNumber();
    if (pos >= tokens.size()) {
        return left;
    }
    if (tokens[pos].type == TokenType::Operator) {
        std::string op = tokens[pos].value;
        pos++;
        auto right = parseNumber();
        return std::make_unique<BinaryExpression>(std::move(left), op, std::move(right));
    }
    throw std::runtime_error("Parser error: expected operator");
}

std::unique_ptr<NumberExpression> Parser::parseNumber() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected number, but reached end of input");
    }
    if (tokens[pos].type != TokenType::Number) {
        throw std::runtime_error("Parser error: expected number");
    }
    auto final = std::make_unique<NumberExpression>(std::stoi(tokens[pos].value));
    pos++;
    return final;
}
