#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>

template <typename T>
class VariableContener {
private:
    std::vector<std::pair<std::string, T>> variables;

public:
    int getVariablesCount() const { return static_cast<int>(variables.size()); }
    void addVariable(std::string name, T value);
    T getVariable(std::string variable);
    bool isElementInVector(std::string element) const;
    void setVariable(std::string variable, T value);
    void deleteVariable(std::string variable);
    void setVariableByPos(int pos, T value);
    std::pair<std::string, T> getVariableByPos(int pos) const;

    void printVariables() const;
};
