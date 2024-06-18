#pragma once
#include "CTree.h"
#include "VarCon.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#define NO_VALUE_DEFAULT 1

class CTree;

class CTreeNode {
public:
    std::string data;
    CTreeNode* left;
    CTreeNode* right;
    CTreeNode* three;
    CTreeNode* four;

    CTreeNode() {
		left = nullptr;
		right = nullptr;
        three = nullptr;
        four = nullptr;
	}
    CTreeNode(const CTreeNode& other) : data(other.data), left(nullptr), right(nullptr), three(nullptr),four(nullptr) {
        if (other.left) {
            left = new CTreeNode(*other.left);
        }
        if (other.right) {
            right = new CTreeNode(*other.right);
        }
    }
    ~CTreeNode() {
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }


    void read(std::vector<std::string>& formula, int pos,int& endPos, VariableContener* varVector,bool& error);
    bool isOperator(const std::string& str) const;
    bool isSinCos(const std::string& str) const;
    bool isNumber(const std::string& str) const;
    bool isVariable(const std::string& str) const;
    bool isSupSum(const std::string& str) const;
    double calculateBranch(VariableContener* varContainer) const;
};

class CTree {
private:
    CTreeNode* root;
    VariableContener variables;
    bool treeCreated = false;
    bool creationError = false;
    
public:

    CTree() {
        root = nullptr;
    }

    CTree(const CTree& other) : root(nullptr), variables(other.variables), treeCreated(other.treeCreated) {
        if (other.root) {
            root = new CTreeNode(*other.root);
        }
    }
    ~CTree() {
        if (root) {
			delete root;
			root = nullptr;
		}
	}


    CTree& operator=(const CTree& other);
    CTree operator+(const CTree& other) const;

    void createFrom(std::vector<std::string>& formula);
    void printVariables() const;
    void calculateFormula(std::vector<std::string> valuesVector);
    CTreeNode* findLeaf(CTreeNode* node) const;
    bool isNumber(const std::string& str) const;
    bool isOperator(const std::string& str) const;
    bool isSinCos(const std::string& str) const;
    bool isSupSum(const std::string& str) const;
    VariableContener* getVariables() {return &variables;}
    bool isCreated() const { return treeCreated; }
    bool hasCreationError() const { return treeCreated; }
    int getVariablesCount() const { return variables.getVariablesCount();}
    void printTree() const {
        printTreePrefix(root);
        std::cout << std::endl;
    }
    void printTreeGraphically() const { printTreeGraph(root, 0);}
    void clear();
private:
    void printTreePrefix(const CTreeNode* node) const;
    void printTreeGraph(const CTreeNode* node, int level) const;
    void printNodeGraph(const std::string& data, int level) const;
};

