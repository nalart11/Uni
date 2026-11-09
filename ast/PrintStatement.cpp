//
// Created by nalart11 on 05.11.2026.
//

#include "PrintStatement.h"
#include <utility>

PrintStatement::PrintStatement(std::unique_ptr<Expression> expression) :
    expression(std::move(expression)) {}

const Expression* PrintStatement::getExpression() const {
    return expression.get();
}