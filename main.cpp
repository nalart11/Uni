#include <iostream>
#include <string>
#include <vector>

#include "Evaluator.h"
#include "Lexer.h"
#include "Parser.h"
#include "ast/BinaryExpression.h"

/* Saved for future */
static void printExpression(const Expression* expression) {
    const auto* number = dynamic_cast<const NumberExpression*>(expression);
    if (number != nullptr) {
        std::cout << number->getValue();
    } else {
        const auto* binary = dynamic_cast<const BinaryExpression*>(expression);
        if (binary != nullptr) {
            std::cout << "(";
            printExpression(binary->getLeft());
            std::cout << binary->getOperator();
            printExpression(binary->getRight());
            std::cout << ")";
        } else {
            throw std::runtime_error("Unexpected expression type");
        }
    }
}

int main() {
    const std::string source =
    "print 10 + 5\n"
    "\n"
    "print 20 * 3\n"
    "print (100 - 40) / 2";
    Lexer lexer(source);
    const auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto statements = parser.parseProgram();

    for (const auto& statement : statements) {
        Evaluator::execute(statement.get());
    }
}
