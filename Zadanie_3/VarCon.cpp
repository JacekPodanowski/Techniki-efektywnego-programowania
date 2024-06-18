#include "CTree.h"
#include "VarCon.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>


bool VariableContener::isElementInVector(std::string element) const {
	for (const std::pair<std::string, int>& i : variables) {
		if (i.first == element) {
			return true;
		}
	}
	return false;
}
void VariableContener::addVariable(std::string name, int value) {
	if (!isElementInVector(name)) {
		variables.push_back(std::make_pair(name, value));
	}
}
int VariableContener::getVariable(std::string variable) {
	for (const std::pair<std::string, int>& var : variables) {
		if (var.first == variable) {
			return var.second;
		}
	}
	return NO_VALUE_DEFAULT;
}
void VariableContener::setVariable(std::string variable, int value) {
	for (std::pair<std::string, int>& var : variables) {
		if (var.first == variable) {
			var.second = value;
		}
	}
}
void VariableContener::deleteVariable(std::string variable) {
	for (int i = 0; i < variables.size(); i++) {
		if (variables[i].first == variable) {
			variables.erase(variables.begin() + i);
		}
	}
}

void VariableContener::setVariableByPos(int pos, int value) {
	if (pos < variables.size()&&pos>=0) {
		variables[pos].second = value;
	}
}
std::pair<std::string, int> VariableContener::getVariableByPos(int pos) const {
	return variables[pos];
}

void VariableContener::printVariables() const {
	std::cout << "Variables: ";
	for (const std::pair<std::string, int>& pair : variables) {
		std::cout << pair.first << " ";
	}
	std::cout << "\n";
}