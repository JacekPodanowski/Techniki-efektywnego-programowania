#pragma once
#include "CTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>

class VariableContener {
private:
	std::vector<std::pair<std::string, int>> variables;
	
public:
	int getVariablesCount() const { return (int)variables.size(); }
	void addVariable(std::string name, int value);
	int getVariable(std::string variable);
	bool isElementInVector(std::string element) const;
	void setVariable(std::string variable, int value);
	void deleteVariable(std::string variable);
	void setVariableByPos(int pos, int value);
	std::pair<std::string, int> getVariableByPos(int pos) const;

	void printVariables() const;
};