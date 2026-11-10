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
#include "ast/IdentifierExpression.h"
#include "ast/VariableDeclaration.h"

Evaluator::Evaluator() = default;

static void checkDivisor(int num) {
    if (num == 0) {
        throw std::runtime_error("Division by zero");
    }
}

int Evaluator::evaluate(const Expression* expression) {
    const auto* number = dynamic_cast<const NumberExpression*>(expression);
    const auto* binary = dynamic_cast<const BinaryExpression*>(expression);
    const auto* identifier = dynamic_cast<const IdentifierExpression*>(expression);

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
    if (identifier != nullptr) {
        return environment.get(identifier->getName());
    }

    throw std::runtime_error("Unexpected expression type");
}

void Evaluator::execute(const Statement* statement) {
    if (const auto* printStatement = dynamic_cast<const PrintStatement*>(statement); printStatement != nullptr) {
        std::cout << evaluate(printStatement->getExpression()) << '\n';
        return;
    }

    if (const auto* declaration = dynamic_cast<const VariableDeclaration*>(statement); declaration != nullptr) {
        const auto& name = declaration->getName();
        const auto* expression = declaration->getInitializer();

        environment.define(name, evaluate(expression));
        return;
    }

    throw std::runtime_error("Unexpected statement type");
}