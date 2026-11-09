#pragma once

#include <string>
#include <unordered_map>

class Environment {
    std::unordered_map<std::string, int> variables;

public:
    void define(const std::string& name, int value);
    int get(const std::string& name) const;
};