//
// Created by nalart11 on 09.11.2026.
//

#include "IdentifierExpression.h"

#include <utility>

IdentifierExpression::IdentifierExpression(std::string  name) :
    name(std::move(name)) {}

const std::string& IdentifierExpression::getName() const {
    return name;
}