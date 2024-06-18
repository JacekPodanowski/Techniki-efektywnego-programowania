#pragma once
#include "VarCon.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#define NO_VALUE_DEFAULT_INT 1
#define NO_VALUE_DEFAULT_DOUBLE 1.0
#define NO_VALUE_DEFAULT_STRING "\"\""
#define NO_VALUE_DEFAULT_BOOL "false"



template <typename T>
class CTreeNode {
public:
    std::string data;
    CTreeNode* left;
    CTreeNode* right;

    CTreeNode() : left(nullptr), right(nullptr) {}
    CTreeNode(const CTreeNode& other) : data(other.data), left(nullptr), right(nullptr) {
        if (other.left) {
            left = new CTreeNode(*other.left);
        }
        if (other.right) {
            right = new CTreeNode(*other.right);
        }
    }
    ~CTreeNode() {
        delete left;
        delete right;
    }

    void read(std::vector<std::string>& formula, int pos, int& endPos, VariableContener<T>* varVector, bool& error);
    bool isOperator(const std::string& str) const;
    bool isSinCos(const std::string& str) const;
    bool isNumber(const std::string& str) const;
    bool isVariable(const std::string& str) const;

    T calculateBranch(VariableContener<T>* varContainer) const;
    std::string getType() const;
    std::string setDefultValue() const;
};

template <typename T>
class CTree {
private:
    CTreeNode<T>* root;
    VariableContener<T> variables;
    bool treeCreated = false;
    bool creationError = false;

public:
    CTree() : root(nullptr) {}

    CTree(const CTree& other) : root(nullptr), variables(other.variables), treeCreated(other.treeCreated) {
        if (other.root) {
            root = new CTreeNode<T>(*other.root);
        }
    }
    ~CTree() {
        delete root;
    }

    CTree& operator=(const CTree& other);
    CTree& operator=(CTree&& other);
    CTree operator+(const CTree& other) const;

    void createFrom(std::vector<std::string>& formula);
    void printVariables() const;
    void calculateFormula(std::vector<std::string> valuesVector);
    CTreeNode<T>* findLeaf(CTreeNode<T>* node) const;
    bool isNumber(const std::string& str) const;
    bool isOperator(const std::string& str) const;
    bool isSinCos(const std::string& str) const;
    VariableContener<T>* getVariables() { return &variables; }
    bool isCreated() const { return treeCreated; }
    bool hasCreationError() const { return creationError; }
    int getVariablesCount() const { return variables.getVariablesCount(); }
    void printTree() const {
        printTreePrefix(root);
        std::cout << std::endl;
    }
    void printTreeGraphically() const { printTreeGraph(root, 0); }
    void clear();
    std::string getType() const;
    std::string setDefultValue() const;

private:
    void printTreePrefix(const CTreeNode<T>* node) const;
    void printTreeGraph(const CTreeNode<T>* node, int level) const;
    void printNodeGraph(const std::string& data, int level) const;
};
