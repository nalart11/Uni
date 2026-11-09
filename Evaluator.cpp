//
// Created by nalart11 on 05.11.2026.
//

#include "Evaluator.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "ast/BinaryExpression.h"
#include "ast/NumberExpression.h"
#include "ast/PrintStatement.h"

Evaluator::Evaluator() = default;

static void checkDivisor(int num) {
    if (num == 0) {
        throw std::runtime_error("Division by zero");
    }
}

int Evaluator::evaluate(const Expression* expression) {
    const auto* number = dynamic_cast<const NumberExpression*>(expression);
    const auto* binary = dynamic_cast<const BinaryExpression*>(expression);

    if (number != nullptr) {
        return number->getValue();
    }
    if (binary != nullptr) {
        const auto left = evaluate(binary->getLeft());
        const auto right = evaluate(binary->getRight());
        const auto& op = binary->getOperator();

        if (op.length() != 1) throw std::runtime_error("Unexpected operator");

        switch (op[0]) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/':
                checkDivisor(right);
                return left / right;
            case '%':
                checkDivisor(right);
                return left % right;
            default:
                throw std::runtime_error("Unexpected operator");
        }
    }

    throw std::runtime_error("Unexpected expression type");
}

void Evaluator::execute(const Statement* statement) {
    const auto* printStatement = dynamic_cast<const PrintStatement*>(statement);
    if (printStatement == nullptr) {
        throw std::runtime_error("Unexpected statement type");
    }
    auto expression = printStatement->getExpression();
    int result = evaluate(expression);
    std::cout << result << std::endl;
}