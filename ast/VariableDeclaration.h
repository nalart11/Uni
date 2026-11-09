//
// Created by nalart11 on 06.11.2026.
//

#pragma once

#include "Expression.h"
#include "Statement.h"
#include "string"
#include "memory"

class VariableDeclaration: public Statement {
    std::string name;
    std::unique_ptr<Expression> initializer;
    public:
    VariableDeclaration(std::string name, std::unique_ptr<Expression> initializer);
    const std::string& getName() const;
    const Expression* getInitializer() const;
};

