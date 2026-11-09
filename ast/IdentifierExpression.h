//
// Created by nalart11 on 09.11.2026.
//

#pragma once
#include <string>

#include "Expression.h"

class IdentifierExpression : public Expression {
public:
    explicit IdentifierExpression(std::string  name);
    const std::string& getName() const;
private:
    std::string name;
};
