//
// Created by nalart11 on 10/10/26.
//

#pragma once
#include "Expression.h"

class NumberExpression : public Expression {
public:
    explicit NumberExpression(int value);
    int getValue() const;
private:
    int value;
};
