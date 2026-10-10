#include <iostream>
#include <string>
#include <cctype>
#include <vector>

#include "Lexer.h"
#include "Parser.h"
#include "Token.h"


int main() {
    const std::string source = "42";
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    std::cout << parser.parseNumber().getValue() << std::endl;
}
