//
// Created by nalart11 on 09.11.2026.
//

#include "Enviroment.h"

#include <iostream>

void Environment::define(const std::string& name, int value) {
    if (const auto it = variables.find(name); it != variables.end()) {
        throw std::runtime_error("Variable '" + name + "' is already defined");
    }

    variables.emplace(name, value);
}

int Environment::get(const std::string& name) const {
    const auto it = variables.find(name);

    if (it == variables.end()) {
        throw std::runtime_error("Undefined variable '" + name + "'");
    }

    return it->second;
}
