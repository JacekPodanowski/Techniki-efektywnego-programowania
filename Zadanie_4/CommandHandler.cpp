#include "CommandHandler.h"
#include "CTree.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

const std::string intTypeTag = "int";
const std::string doubleTypeTag = "double";
const std::string stringTypeTag = "string";
const std::string boolTypeTag = "bool";

template <typename T>
void CommandHandler<T>::run() {
    std::string input;
    CTree<T> tree;

    const std::string exitCommand = "exit";
    const std::string enterCommand = "enter";
    const std::string varsCommand = "vars";
    const std::string printCommand = "print";
    const std::string printgCommand = "printg";
    const std::string compCommand = "comp";
    const std::string joinCommand = "join";

    const std::string commandMessage = "Valid commands: enter <form>, vars, print, printg, comp <v1, v2, ..>, exit.\n";

    std::cout << "Tree type: " << getType() << "\n\n";
    std::cout << commandMessage;

    do {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);
        if (input == "") {
            continue;
        }

        std::vector<std::string> commandVector = splitString(input, ' ');
        std::string command = commandVector[0];
        commandVector.erase(commandVector.begin());

        if (command == exitCommand) {
            break;
        }
        if (command == enterCommand) {
            tree.clear();
            tree.createFrom(commandVector);
            if (tree.hasCreationError()) {
                std::cout << "Inaccuracy in formula, tree was auto-repaired\n";
            }
            std::cout << "Tree created\n";
        }
        if (tree.isCreated()) {
            if (command == varsCommand) {
                tree.printVariables();
            }
            else if (command == printCommand) {
                tree.printTree(); // postac prefiksowa nie graficzna
            }
            else if (command == printgCommand) {
                tree.printTreeGraphically();
            }
            else if (command == compCommand) {
                if (commandVector.size() != tree.getVariablesCount()) {
                    std::cout << "Expected " << tree.getVariablesCount() << " variables\n";
                    continue;
                }
                tree.calculateFormula(commandVector);
            }
            else if (command == joinCommand) {
                if (commandVector.size() == 0) {
                    std::cout << "Expected tree expression\n";
                    continue;
                }
                CTree<T> otherTree;
                otherTree.createFrom(commandVector);
                tree = tree + otherTree;
                std::cout << "Tree joined\n";
            }
        }
        else if (command == printCommand || command == varsCommand) {
            std::cout << "Tree not created yet\n";
        }
        else if (command.find(compCommand) == 0 || command.find(joinCommand) == 0) {
            std::cout << "Tree not created yet\n";
        }
        else {
            std::cout << "Unknown command, " << commandMessage << std::endl;
        }

    } while (true);
}

std::string CommandHandler<int>::getType() {
	return intTypeTag;
}
std::string CommandHandler<double>::getType() {
	return doubleTypeTag;
}
std::string CommandHandler<std::string>::getType() {
	return stringTypeTag;
}
std::string CommandHandler<bool>::getType() {
	return boolTypeTag;
}

template class CommandHandler<int>;
template class CommandHandler<double>;
template class CommandHandler<std::string>;
template class CommandHandler<bool>;
