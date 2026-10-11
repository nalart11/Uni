#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Parser.h"
#include "ast/BinaryExpression.h"


int main() {
    const std::string source = "2 + 3";
    Lexer lexer(source);
    const auto tokens = lexer.tokenize();
    Parser parser(tokens);
    const auto expression = parser.parseExpression();
    const auto* binary = dynamic_cast<BinaryExpression*>(expression.get());
    const auto left = dynamic_cast<NumberExpression*>(binary->getLeft());
    const auto right = dynamic_cast<NumberExpression*>(binary->getRight());
    const auto op = binary->getOperator();
    std::cout << left->getValue() << std::endl;
    std::cout << op << std::endl;
    std::cout << right->getValue() << std::endl;
}
