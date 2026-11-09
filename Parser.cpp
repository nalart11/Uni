//
// Created by nalart11 on 10/10/26.
//

#include "Parser.h"
#include <stdexcept>

#include "ast/BinaryExpression.h"
#include "ast/IdentifierExpression.h"
#include "ast/PrintStatement.h"

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
    std::unique_ptr<Expression> left = parsePrimary();
    while (pos < tokens.size() && tokens[pos].type == TokenType::Operator && (tokens[pos].value == "*" || tokens[pos].value == "/" || tokens[pos].value == "%")) {
        auto op = tokens[pos].value;
        pos++;
        auto right = parsePrimary();

        left = std::make_unique<BinaryExpression>(std::move(left), op, std::move(right));
    }
    return left;
}

std::unique_ptr<Expression> Parser::parsePrimary() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected number or expression, but reached end of input");
    }
    if (tokens[pos].type == TokenType::Number) {
        return parseNumber();
    }
    if (tokens[pos].type == TokenType::LeftParen) {
        pos++;
        auto expression = parseExpression();
        if (pos < tokens.size()) {
            if (tokens[pos].type == TokenType::RightParen) {
                pos++;
                return expression;
            } else {
                throw std::runtime_error("Parser error: expected \")\"");
            }
        } else {
            throw std::runtime_error("Parser error: expected \")\"");
        }
    }
    if (tokens[pos].type == TokenType::Identifier) {
        std::string name = tokens[pos].value;
        pos++;
        std::unique_ptr<IdentifierExpression> expression = std::make_unique<IdentifierExpression>(name);
        return expression;
    }
    throw std::runtime_error("Parser error: expected primary expression");
}

std::unique_ptr<Expression> Parser::parse() {
    auto expression = parseExpression();
    if (pos < tokens.size()) {
        throw std::runtime_error("Unexpected token " + tokens[pos].value);
    }
    return expression;
}

std::unique_ptr<PrintStatement> Parser::parsePrint() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected print statement, but reached end of input");
    }
    if (tokens[pos].type != TokenType::Keyword || tokens[pos].value != "print") {
        throw std::runtime_error("Parser error: expected keyword");
    }
    pos++;
    auto result = parseExpression();
    auto statement = std::make_unique<PrintStatement>(std::move(result));
    return statement;
}

std::unique_ptr<Statement> Parser::parseStatement() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected statement, but reached end of input");
    }
    if (tokens[pos].type != TokenType::Keyword) {
        throw std::runtime_error("Parser error: expected keyword");
    }
    if (tokens[pos].value == "print") {
        return parsePrint();
    }

    if (tokens[pos].value == "val") {
        return parseVariableDeclaration();
    }
    throw std::runtime_error("Parser error: unknown statement type");
}

std::vector<std::unique_ptr<Statement>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Statement>> statements;
    while (pos < tokens.size()) {
        if (tokens[pos].type == TokenType::NewLine) {
            pos++;
            continue;
        }
        statements.push_back(parseStatement());
        if (pos < tokens.size() && tokens[pos].type != TokenType::NewLine) {
            throw std::runtime_error("Parser error: expected newline");
        }
        if (pos < tokens.size()) {
            pos++;
        }
    }
    return statements;
}

std::unique_ptr<VariableDeclaration> Parser::parseVariableDeclaration() {
    if (pos >= tokens.size()) {
        throw std::runtime_error("Parser error: expected variable, but reached end of input");
    }
    if (tokens[pos].type == TokenType::Keyword && tokens[pos].value == "val") {
        pos++;
        if (pos >= tokens.size()) {
            throw std::runtime_error("Parser error: expected variable, but reached end of input");
        }
        if (tokens[pos].type != TokenType::Identifier) {
            throw std::runtime_error("Parser error: expected identifier");
        }
        std::string name = tokens[pos].value;
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Operator || tokens[pos].value != "=") {
            throw std::runtime_error("Parser error: expected =");
        }
        pos++;
        if (pos < tokens.size()) {
            std::unique_ptr<Expression> initializer = parseExpression();
            return std::make_unique<VariableDeclaration>(name, std::move(initializer));
        }
    }
    throw std::runtime_error("Parser error: expected variable, but reached end of input");
}