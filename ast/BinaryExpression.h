//
// Created by nalart11 on 10.10.2026.
//
#pragma once

#include "Expression.h"
#include <memory>
#include <string>

class BinaryExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::string op;
    std::unique_ptr<Expression> right;
    public:
    BinaryExpression(
        std::unique_ptr<Expression> left,
        std::string op,
        std::unique_ptr<Expression> right
    );

    Expression* getLeft() const;
    Expression* getRight() const;
    const std::string &getOperator() const;
};
