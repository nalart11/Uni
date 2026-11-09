//
// Created by nalart11 on 06.11.2026.
//

#include "VariableDeclaration.h"

#include <string>
#include <utility>

VariableDeclaration::VariableDeclaration(std::string name, std::unique_ptr<Expression> initializer) :
    name(std::move(name)), initializer(std::move(initializer)) {}

const std::string &VariableDeclaration::getName() const {
    return name;
}

const Expression* VariableDeclaration::getInitializer() const {
    return initializer.get();
}