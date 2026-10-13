//
// Created by nalart11 on 10/10/26.
//

#include "Parser.h"
#include <stdexcept>

#include "ast/BinaryExpression.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Expression> Parser::parseExpression() {
    std::unique_ptr<Expression> left = parseTerm();
    while (pos < tokens.size() && tokens[pos].type == TokenType::Operator && (tokens[pos].value == "+" || tokens[pos].value == "-")) {
        std::string op = tokens[pos].value;
        pos++;
        auto right = parseTerm();
        left = std::make_unique<BinaryExpression>(std::move(left), op, std::move(right));
    }
    return left;
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

std::unique_ptr<Expression> Parser::parseTerm() {
    std::unique_ptr<Expression> left = parseNumber();
    while (pos < tokens.size() && tokens[pos].type == TokenType::Operator && (tokens[pos].value == "*" || tokens[pos].value == "/" || tokens[pos].value == "%")) {
        auto op = tokens[pos].value;
        pos++;
        auto right = parseNumber();

        left = std::make_unique<BinaryExpression>(std::move(left), op, std::move(right));
    }
    return left;
}