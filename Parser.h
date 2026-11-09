//
// Created by nalart11 on 10/10/26.
//

#pragma once
#include <cstddef>
#include <vector>
#include <memory>
#include "ast/NumberExpression.h"
#include "Token.h"
#include "ast/PrintStatement.h"
#include "ast/VariableDeclaration.h"

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parsePrimary();
    std::unique_ptr<Expression> parse();
    std::unique_ptr<NumberExpression> parseNumber();
    std::unique_ptr<PrintStatement> parsePrint();
    std::unique_ptr<Statement> parseStatement();
    std::vector<std::unique_ptr<Statement>> parseProgram();
    std::unique_ptr<VariableDeclaration> parseVariableDeclaration();

private:
    const std::vector<Token>& tokens;
    std::size_t pos{};
};
