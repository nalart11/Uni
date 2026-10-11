cmake_minimum_required(VERSION 4.3)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        TokenType.cpp
        TokenType.h
        Token.cpp
        Token.h
        Lexer.cpp
        Lexer.h
        ast/Expression.cpp
        ast/Expression.h
        ast/NumberExpression.cpp
        ast/NumberExpression.h
        Parser.cpp
        Parser.h
        ast/BinaryExpression.cpp
        ast/BinaryExpression.h)
