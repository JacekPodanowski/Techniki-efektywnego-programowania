#define _USE_MATH_DEFINES
#include "CTree.h"
#include "VarCon.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

const double DEG_TO_RAD = M_PI / 180.0;

void CTreeNode::read(std::vector<std::string>& formula, int pos, int& endPos, VariableContener* varContener,bool& error) {
    data = formula[pos];
    if (isOperator(data)) {
        left = new CTreeNode();
        if (formula.size() > pos+1) {
            left->read(formula, pos + 1, endPos, varContener,error);
        }
        else {
            left->data = std::to_string(NO_VALUE_DEFAULT);
            error = true;
        }

        if (isSupSum(data)) {
            three = new CTreeNode();
            if (formula.size() > pos + 2) {
                three->read(formula, pos + 2, endPos, varContener, error);
            }
            else {
                three->data = std::to_string(NO_VALUE_DEFAULT);
                error = true;
            }
            four = new CTreeNode();
            if (formula.size() > pos + 3) {
                four->read(formula, pos + 3, endPos, varContener, error);
            }
            else {
                four->data = std::to_string(NO_VALUE_DEFAULT);
                error = true;
            }
        }

        if (isSinCos(data)) {
            right = nullptr;
        }
        else {
            right = new CTreeNode();
            if (formula.size() > endPos + 1 && formula.size()>pos + 1) {
                right->read(formula, endPos + 1, endPos, varContener, error);
            }
            else
            {
                right->data = std::to_string(NO_VALUE_DEFAULT);
                error = true;
            }
        }

    }
    else {
        if(isVariable(data)){
			varContener->addVariable(data, NO_VALUE_DEFAULT);
		}
        else if (isNumber(data)) {
            left = nullptr;
            right = nullptr;
        }
		else {
            error = true;
            data = std::to_string(NO_VALUE_DEFAULT);
		}
    }
    if(pos>endPos){
		endPos = pos;
	}
}

void CTree::createFrom(std::vector<std::string>& formula) {
    int endPos = 0;
    bool error = false;
    root = new CTreeNode();
    root->read(formula, 0,endPos,&variables,error);

   /* if (endPos + 1 < formula.size()) {
        std::cout << "Unused symbols: ";
		for (int i = endPos + 1; i < formula.size(); i++) {
			std::cout << formula[i] << " ";
		}
		std::cout << std::endl;
    }*/
    creationError = error;
    treeCreated= true;
}


void CTree::calculateFormula(std::vector<std::string> valuesVector) {
    int numbercout = 0;
    for (std::string value : valuesVector) {
		if (isNumber(value)) {
			numbercout++;
		}
	}
    if (numbercout != variables.getVariablesCount()) {
        std::cout << "enter " << variables.getVariablesCount() << " legit values" << std::endl;
        return;
    }
    for (int i = 0; i < variables.getVariablesCount(); i++) {
        variables.setVariableByPos(i,std::stoi(valuesVector[i]));
    }
    double result = root->calculateBranch(getVariables());
    std::cout << "Result: " << result << std::endl;
}

double CTreeNode::calculateBranch(VariableContener* varContainer) const {
    if (isOperator(data)) {
        double leftValue = (left != nullptr) ? left->calculateBranch(varContainer) : 1;
        double rightValue = (right != nullptr) ? right->calculateBranch(varContainer) : 1;

        if (data == "+") {
            return leftValue + rightValue;
        }
        else if (data == "-") {
            return leftValue - rightValue;
        }
        else if (data == "*") {
            return leftValue * rightValue;
        }
        else if (data == "/") {
            if (rightValue == 0) {
                return 0;
            }
            return leftValue / rightValue;
        }
        else if (data == "sin") {
            return std::sin(leftValue * DEG_TO_RAD);
        }
        else if (data == "cos") {
            return std::cos(leftValue * DEG_TO_RAD);
        }
        else if (data == "supersum") {
            double value3 = (left != nullptr) ? three->calculateBranch(varContainer) : 1;
            double value4 = (right != nullptr) ? four->calculateBranch(varContainer) : 1;
            return leftValue + rightValue+value3+value4;
        }
    }
    else {
        if (isNumber(data)) {
            return std::stoi(data);
        }
        else {
            int variableValue = varContainer->getVariable(data);
            return variableValue;
        }
    }
}

void CTree::printVariables() const {
    variables.printVariables();
}

CTree& CTree::operator=(const CTree& other) {
    if (this != &other) {
        delete root;
        if (other.root != nullptr) {
            root = new CTreeNode(*other.root);
        }
        else {
			root = nullptr;
		}
        variables = other.variables;
        treeCreated = other.treeCreated;
    }
    return *this;
}

CTree CTree::operator+(const CTree& other) const {
    CTree result(*this); 

    if (other.root) {
        CTreeNode* otherCopy = new CTreeNode(*other.root);
        CTreeNode* leaf = findLeaf(result.root);

        if (leaf) {
            if (leaf->isVariable(leaf->data)) {
                result.variables.deleteVariable(leaf->data);
            }
            *leaf = *otherCopy;

            for(int i =0;i<other.variables.getVariablesCount();i++){
                std::pair<std::string, int> variable = other.variables.getVariableByPos(i);
                if (!result.variables.isElementInVector(variable.first)) {
                    result.variables.addVariable(variable.first, NO_VALUE_DEFAULT);
                }
            }
        }
    }
    return result;
}

CTreeNode* CTree::findLeaf(CTreeNode* node) const {
    if (!node) {
        return nullptr;
    }

    if (node->left==nullptr&& node->right == nullptr) {
        return node;
    }

    CTreeNode* leftLeaf = findLeaf(node->left);
    CTreeNode* rightLeaf = findLeaf(node->right);

    return leftLeaf ? leftLeaf : rightLeaf;//jak jest nie null to go da
}

bool CTree::isOperator(const std::string& str) const {
    return (str == "+" || str == "-" || str == "*" || str == "/" || str=="sin" || str == "cos" || str == "supersum");
}
bool CTreeNode::isOperator(const std::string& str) const {
    return (str == "+" || str == "-" || str == "*" || str == "/" || str == "sin" || str == "cos" || str == "supersum");
}

bool CTreeNode::isSinCos(const std::string& str) const {
	return (str == "sin" || str == "cos");
}
bool CTreeNode::isSupSum(const std::string& str) const {
    return (str == "supersum");
}
bool CTree::isSupSum(const std::string& str) const {
    return (str == "supersum");
}

bool CTreeNode::isNumber(const std::string& str) const {
    if (str.empty()) {
        return false;
    }
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool CTreeNode::isVariable(const std::string& str) const {
    if (str.empty()) {
        return false;
    }
    int alphaCount = 0;
    for (char ch : str) {
        if (std::isalpha(ch)) {
            alphaCount++;
        }
        else if (!std::isdigit(ch)) {
			return false;
		}
    }
    return alphaCount>0;
}

bool CTree::isNumber(const std::string& str) const {
    if (str.empty()) {
        return false;
    }
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool CTree::isSinCos(const std::string& str) const {
    return (str == "sin" || str == "cos");
}
void CTree::printTreePrefix(const CTreeNode* node) const {
    if (node != nullptr) {
        std::cout << node->data << " ";
        printTreePrefix(node->left);
        printTreePrefix(node->right);
    }
}

void CTree::clear() {
    delete root;
	root = nullptr;
	variables = VariableContener();
	treeCreated = false;
}
void CTree::printNodeGraph(const std::string& data, int level) const {
    const int spaces = level * 4;

    std::cout << std::string(spaces, ' ');
    if (level == 0) {
        std::cout << std::string(spaces*2, ' ');
    }
    if (level > 0) {
        std::cout << "|-- ";
    }

    std::cout << data << std::endl;
}

void CTree::printTreeGraph(const CTreeNode* node, int level) const {
    if (node == nullptr) {
        return;
    }
    std::cout << std::string(4, ' ');
    printNodeGraph(node->data, level);

    printTreeGraph(node->left, level + 1);
    printTreeGraph(node->right, level + 1);
}
