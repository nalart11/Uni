//
// Created by nalart11 on 10/9/26.
//

#include "Lexer.h"

#include <cctype>
#include <vector>
#include <iostream>

Lexer::Lexer(const std::string& source)
    : source(source),
      pos(0) {
}

bool Lexer::isOperator(const char c) {
    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '%' ||
           c == '^';
}

bool Lexer::isKeyword(const std::string& value) {
    return value == "print";
}

bool Lexer::isParen(const char c) {
    return c == ')' || c == '(';
}

bool Lexer::isBrace(const char c) {
    return c == '{' || c == '}';
}

bool Lexer::isBracket(const char c) {
    return c == '[' || c == ']';
}

Token Lexer::readNumber() {
    std::string value;
    while (pos < source.length() && isdigit(source[pos])) {
        value += source[pos];
        pos++;
    }
    return Token{.type = TokenType::Number, .value = value};
}

Token Lexer::readIdentifier() {
    std::string value;
    while (pos < source.length() && (isalpha(source[pos]) || isdigit(source[pos]) || source[pos] == '_')) {
        value += source[pos];
        pos++;
    }
    if (isKeyword(value)) {
        return Token{.type = TokenType::Keyword, .value = value};
    }
    return Token{.type = TokenType::Identifier, .value = value};
}

Token Lexer::readOperator() {
    std::string value;
    value += source[pos];
    pos++;
    return Token{.type = TokenType::Operator, .value = value};
}

Token Lexer::readParen() {
    std::string value;
    TokenType tokenType;
    switch (source[pos]) {
        case '(':
            tokenType = TokenType::LeftParen;
            break;
        case ')':
            tokenType = TokenType::RightParen;
            break;
        default:
            break;
    }
    value += source[pos];
    pos++;
    auto token = Token{.type = tokenType, .value = value};
    return token;
}

Token Lexer::readBrace() {
    std::string value;
    TokenType tokenType;
    switch (source[pos]) {
        case '{':
            tokenType = TokenType::LeftBrace;
            break;
        case '}':
            tokenType = TokenType::RightBrace;
            break;
        default:
            break;
    }
    value += source[pos];
    pos++;
    auto token = Token{.type = tokenType, .value = value};
    return token;
}

Token Lexer::readBracket() {
    std::string value;
    TokenType tokenType;
    switch (source[pos]) {
        case '[':
            tokenType = TokenType::LeftBracket;
            break;
        case ']':
            tokenType = TokenType::RightBracket;
            break;
        default:
            break;
    }
    value += source[pos];
    pos++;
    auto token = Token{.type = tokenType, .value = value};
    return token;
}

std::vector<Token> Lexer::tokenize() {
    while (pos < source.length()) {
        if (isdigit(source[pos])) {
            tokens.push_back(readNumber());
        } else if (isalpha(source[pos]) || source[pos] == '_') {
            tokens.push_back(readIdentifier());
        } else if (isOperator(source[pos])) {
            tokens.push_back(readOperator());
        } else if (isParen(source[pos])) {
            tokens.push_back(readParen());
        } else if (isBrace(source[pos])) {
            tokens.push_back(readBrace());
        } else if (isBracket(source[pos])) {
            tokens.push_back(readBracket());
        } else if (isspace(source[pos])) {
            pos++;
        } else {
            std::cout << "Unexpected character \'" << source[pos] << "\' at pos " << pos + 1 << std::endl;
            pos++;
        }
    }
    return tokens;
}
