#include "VarCon.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>

template <typename T>
bool VariableContener<T>::isElementInVector(std::string element) const {
    for (const std::pair<std::string, T>& i : variables) {
        if (i.first == element) {
            return true;
        }
    }
    return false;
}

template <typename T>
void VariableContener<T>::addVariable(std::string name, T value) {
    if (!isElementInVector(name)) {
        variables.push_back(std::make_pair(name, value));
    }
}

template <typename T>
T VariableContener<T>::getVariable(std::string variable) {
    for (const std::pair<std::string, T>& var : variables) {
        if (var.first == variable) {
            return var.second;
        }
    }
    return T(); // no value deafult
}

template <typename T>
void VariableContener<T>::setVariable(std::string variable, T value) {
    for (std::pair<std::string, T>& var : variables) {
        if (var.first == variable) {
            var.second = value;
        }
    }
}

template <typename T>
void VariableContener<T>::deleteVariable(std::string variable) {
    variables.erase(
        std::remove_if(variables.begin(), variables.end(),
            [variable](const auto& pair) { return pair.first == variable; }),
        variables.end());
}

template <typename T>
void VariableContener<T>::setVariableByPos(int pos, T value) {
    if (pos < variables.size() && pos >= 0) {
        variables[pos].second = value;
    }
}

template <typename T>
std::pair<std::string, T> VariableContener<T>::getVariableByPos(int pos) const {
    return variables[pos];
}

template <typename T>
void VariableContener<T>::printVariables() const {
    std::cout << "Variables: ";
    for (const std::pair<std::string, T>& pair : variables) {
        std::cout << pair.first << " ";
    }
    std::cout << "\n";
}


template class VariableContener<int>;
template class VariableContener<double>; 
template class VariableContener<std::string>; 
template class VariableContener<bool>; 
