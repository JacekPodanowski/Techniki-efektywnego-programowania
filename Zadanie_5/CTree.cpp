#define _USE_MATH_DEFINES
#include "CTree.h"
#include "VarCon.h"
#include "Utils.h"
#include "TreeData.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

const std::string intTypeTag = "int";
const std::string doubleTypeTag = "double";
const std::string stringTypeTag = "string";
const std::string boolTypeTag = "bool";

const double DEG_TO_RAD = M_PI / 180.0;
const std::string AddOperator = "+";
const std::string SubOperator = "-";
const std::string MulOperator = "*";
const std::string DivOperator = "/";
const std::string SinOperator = "sin";
const std::string CosOperator = "cos";

template <typename T>
void CTreeNode<T>::read(std::vector<std::string>& formula, int pos, int& endPos, VariableContener<T>* varContener, bool& error) {
    data = formula[pos];
    if (isOperator(data)) {
        left = new CTreeNode();
        if (formula.size() > pos + 1) {
            left->read(formula, pos + 1, endPos, varContener, error);
        }
        else {
            left->data = setDefultValue();
            error = true;
        }
        if (isSinCos(data)) {
            right = nullptr;
        }
        else {
            right = new CTreeNode();
            if (formula.size() > endPos + 1 && formula.size() > pos + 1) {
                right->read(formula, endPos + 1, endPos, varContener, error);
            }
            else {
                right->data = setDefultValue();
                error = true;
            }
        }

    }
    else {
        if (isVariable(data)) {
            varContener->addVariable(data, TreeData<T>::fromString(setDefultValue()).getValue());
        }
        else if (TreeData<T>::isValue(data)) {
            left = nullptr;
            right = nullptr;
        }
        else {
            error = true;
            data = setDefultValue();
        }
    }
    if (pos > endPos) {
        endPos = pos;
    }
}


template <typename T>
T CTreeNode<T>::calculateBranch(VariableContener<T>* varContainer) const {
    if (isOperator(data)) {
        T leftValue = (left != nullptr) ? left->calculateBranch(varContainer) : TreeData<T>::fromString(setDefultValue()).getValue();
        T rightValue = (right != nullptr) ? right->calculateBranch(varContainer) : TreeData<T>::fromString(setDefultValue()).getValue();

        if (data == AddOperator) {
			return TreeData<T>(leftValue) + TreeData<T>(rightValue);
        }
        else if (data == SubOperator) {
            return TreeData<T>(leftValue) - TreeData<T>(rightValue);
        }
		else if (data == MulOperator) {
            return TreeData<T>(leftValue) * TreeData<T>(rightValue);
        }
		else if (data == DivOperator) {
            return TreeData<T>(leftValue) / TreeData<T>(rightValue);
		}
		else if (data == SinOperator) {
			return TreeData<T>(leftValue).sin();
		}
		else if (data == CosOperator) {
            return TreeData<T>(leftValue).cos();
        }
    }
    else {
        if (TreeData<T>::isValue(data)){
            return TreeData<T>::fromString(data).getValue();
        }
        else {
            T variableValue = varContainer->getVariable(data);
            return variableValue;
        }
    }
}

template <typename T>
void CTree<T>::createFrom(std::vector<std::string>& formula) {
    int endPos = 0;
    bool error = false;
    root = new CTreeNode<T>();
    root->read(formula, 0, endPos, &variables, error);

    if (endPos + 1 < formula.size()) {
        error = true;
    }
    creationError = error;
    treeCreated = true;
}

template <typename T>
void CTree<T>::calculateFormula(std::vector<std::string> valuesVector) {
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
        variables.setVariableByPos(i, TreeData<T>::fromString(valuesVector[i]).getValue());
    }
    T result = root->calculateBranch(getVariables());
    std::cout << "Result: " << result << std::endl;
}

template <typename T>
CTree<T>& CTree<T>::operator=(const CTree<T>& other) {
    if (this != &other) {
        delete root;
        if (other.root != nullptr) {
            root = new CTreeNode<T>(*other.root);
        }
        else {
            root = nullptr;
        }
        variables = other.variables;
        treeCreated = other.treeCreated;
    }
    return *this;
}

template <typename T>
CTree<T>& CTree<T>::operator=(CTree<T>&& other){
    if (this != &other) {
        delete root;

        root = other.root;
        variables = std::move(other.variables);
        treeCreated = std::move(other.treeCreated);

        other.root = nullptr;
        other.variables= VariableContener<T>();
        other.treeCreated = false;
    }
    return *this;
}


template <typename T>
CTree<T> CTree<T>::operator+(const CTree<T>& other) const {
    CTree<T> result(*this);

    if (other.root) {
        CTreeNode<T>* otherCopy = new CTreeNode<T>(*other.root);
        CTreeNode<T>* leaf = findLeaf(result.root);

        if (leaf) {
            if (leaf->isVariable(leaf->data)) {
                result.variables.deleteVariable(leaf->data);
            }
            *leaf = *otherCopy;

            for (int i = 0; i < other.variables.getVariablesCount(); i++) {
                std::pair<std::string, T> variable = other.variables.getVariableByPos(i);
                if (!result.variables.isElementInVector(variable.first)) {
                    result.variables.addVariable(variable.first, TreeData<T>::fromString(setDefultValue()).getValue());
                }
            }
        }
    }
    return std::move(result);
}

template <typename T>
CTreeNode<T>* CTree<T>::findLeaf(CTreeNode<T>* node) const {
    if (!node) {
        return nullptr;
    }

    if (node->left == nullptr && node->right == nullptr) {
        return node;
    }

    CTreeNode<T>* leftLeaf = findLeaf(node->left);
    CTreeNode<T>* rightLeaf = findLeaf(node->right);

    return leftLeaf ? leftLeaf : rightLeaf;
}

template <typename T>
bool CTreeNode<T>::isOperator(const std::string& str) const {
    return (str == "+" || str == "-" || str == "*" || str == "/" || str == "sin" || str == "cos" || str == "supersum");
}

template <typename T>
bool CTreeNode<T>::isSinCos(const std::string& str) const {
    return (str == "sin" || str == "cos");
}

template <typename T>
bool CTreeNode<T>::isNumber(const std::string& str) const {
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

template <typename T>
bool CTreeNode<T>::isVariable(const std::string& str) const {
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
    return alphaCount > 0;
}

template <typename T>
bool CTree<T>::isNumber(const std::string& str) const {
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

template <typename T>
bool CTree<T>::isSinCos(const std::string& str) const {
    return (str == "sin" || str == "cos");
}

template <typename T>
void CTree<T>::printTreePrefix(const CTreeNode<T>* node) const {
    if (node != nullptr) {
        std::cout << node->data << " ";
        printTreePrefix(node->left);
        printTreePrefix(node->right);
    }
}

template <typename T>
void CTree<T>::printVariables() const {
    variables.printVariables();
}

template <typename T>
void CTree<T>::clear() {
    delete root;
    root = nullptr;
    variables = VariableContener<T>();
    treeCreated = false;
}

template <typename T>
void CTree<T>::printNodeGraph(const std::string& data, int level) const {
    const int spaces = level * 4;

    std::cout << std::string(spaces, ' ');
    if (level == 0) {
        std::cout << std::string(spaces * 2, ' ');
    }
    if (level > 0) {
        std::cout << "|-- ";
    }

    std::cout << data << std::endl;
}

template <typename T>
void CTree<T>::printTreeGraph(const CTreeNode<T>* node, int level) const {
    if (node == nullptr) {
        return;
    }
    std::cout << std::string(4, ' ');
    printNodeGraph(node->data, level);

    printTreeGraph(node->left, level + 1);
    printTreeGraph(node->right, level + 1);
}

std::string CTree<int>::getType() const{
    return intTypeTag;
}
std::string CTree<double>::getType() const{
    return doubleTypeTag;
}
std::string CTree<std::string>::getType() const{
    return stringTypeTag;
}
std::string CTree<bool>::getType() const {
	return boolTypeTag;
}

std::string CTreeNode<int>::getType() const{
    return intTypeTag;
}
std::string CTreeNode<double>::getType()const {
	return doubleTypeTag;
}
std::string CTreeNode<std::string>::getType() const{
	return stringTypeTag;
}
std::string CTreeNode<bool>::getType() const {
	return boolTypeTag;
}


std::string CTreeNode<int>::setDefultValue() const{
    return std::to_string(NO_VALUE_DEFAULT_INT);
}
std::string CTreeNode<double>::setDefultValue() const {
	return std::to_string(NO_VALUE_DEFAULT_DOUBLE);
}
std::string CTreeNode<std::string>::setDefultValue() const {
	return NO_VALUE_DEFAULT_STRING;
}
std::string CTreeNode<bool>::setDefultValue() const {
    return NO_VALUE_DEFAULT_BOOL;
}

std::string CTree<int>::setDefultValue() const {
    return std::to_string(NO_VALUE_DEFAULT_INT);
}
std::string CTree<double>::setDefultValue() const {
    return std::to_string(NO_VALUE_DEFAULT_DOUBLE);
}
std::string CTree<std::string>::setDefultValue() const {
    return NO_VALUE_DEFAULT_STRING;
}
std::string CTree<bool>::setDefultValue() const {
    return NO_VALUE_DEFAULT_BOOL;
}
template class CTreeNode<double>;
template class CTree<double>;

template class CTreeNode<int>;
template class CTree<int>;

template class CTreeNode<std::string>;
template class CTree<std::string>;

template class CTreeNode<bool>;
template class CTree<bool>;