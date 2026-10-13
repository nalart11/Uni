//
// Created by nalart11 on 10/10/26.
//

#pragma once
#include <cstddef>
#include <vector>
#include <memory>
#include "ast/NumberExpression.h"
#include "Token.h"

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    std::unique_ptr<NumberExpression> parseNumber();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseTerm();

private:
    const std::vector<Token>& tokens;
    std::size_t pos{};
};
