#include <iostream>
#include <string>
#include <cctype>
#include <vector>

#include "Lexer.h"
#include "Token.h"


int main() {
    const std::string source = "player1+3425-player+-228";
    Lexer lexer(source);

    for (auto tokens = lexer.tokenize(); const auto& token : tokens) {
        std::cout << token.value << std::endl;
    }
}
