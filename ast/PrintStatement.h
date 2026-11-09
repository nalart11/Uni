//
// Created by nalart11 on 05.11.2026.
//

#pragma once
#include <memory>

#include "Expression.h"
#include "Statement.h"


class PrintStatement: public Statement {
    std::unique_ptr<Expression> expression;
    public:
    PrintStatement(std::unique_ptr<Expression> expression);

    const Expression* getExpression() const;
};

