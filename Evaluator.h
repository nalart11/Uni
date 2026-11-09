//
// Created by nalart11 on 05.11.2026.
//

#pragma once
#include "Enviroment.h"
#include "ast/Expression.h"
#include "ast/Statement.h"


class Evaluator {
    Environment environment;

    public:
    Evaluator();

    static int evaluate(const Expression* expression);
    static void execute(const Statement* statement);
};

