//
// Created by nalart11 on 10.10.2026.
//

#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(
    std::unique_ptr<Expression> left,
    std::string op,
    std::unique_ptr<Expression> right
)
    : left(std::move(left)),
      op(std::move(op)),
      right(std::move(right)) {
}

Expression* BinaryExpression::getLeft() const {
    return left.get();
}

Expression* BinaryExpression::getRight() const {
    return right.get();
}

const std::string &BinaryExpression::getOperator() const {
    return op;
}
