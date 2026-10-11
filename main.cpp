#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Parser.h"
#include "ast/BinaryExpression.h"


int main() {
    const std::string source = "42";
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    std::cout << parser.parseNumber().getValue() << std::endl;

    std::unique_ptr<Expression> left = std::make_unique<NumberExpression>(2);
    std::unique_ptr<Expression> right = std::make_unique<NumberExpression>(3);
    std::unique_ptr<Expression> expression = std::make_unique<BinaryExpression>(
        std::move(left), "*", std::move(right)
        );
    auto* binary = dynamic_cast<BinaryExpression*>(expression.get());
    if (binary == nullptr) {
        std::cout << "Expression is not BinaryExpression";
        return 1;
    }
    const auto* leftNumber = dynamic_cast<const NumberExpression*>(binary->getLeft());
    const auto* rightNumber = dynamic_cast<const NumberExpression*>(binary->getRight());
    const auto& op = binary->getOperator();
    if (leftNumber != nullptr) {
        std::cout << "Left: " << leftNumber->getValue() << '\n';
    }
    std::cout << "Operator: " << op << '\n';
    if (rightNumber != nullptr) {
        std::cout << "Right: " << rightNumber->getValue() << '\n';
    }
}
