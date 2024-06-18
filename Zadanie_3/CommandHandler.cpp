#include"CommandHandler.h"
#include"CTree.h"
#include"Utils.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>


void CommandHandler::run() {
    CTree tree;
    std::string input;
    const int superSumArgsCount = 4;
    const std::string exitComand = "exit";
    const std::string enterComand = "enter";
    const std::string varsComand = "vars";
    const std::string printComand = "print";
    const std::string printgComand = "printg";
    const std::string compComand = "comp";
    const std::string joinComand = "join";
    const std::string errorMessage = "Valid commands : enter <form>, vars, print, printg, comp <v1, v2, ..>, exit.\n";
    std::cout << errorMessage;

    do {
        std::cout << "Enter command: ";
        std::getline(std::cin, input);
        if (input == "") {
            continue;
        }

        std::vector<std::string> commandVector = splitString(input, ' ');
        std::string command = commandVector[0];
        commandVector.erase(commandVector.begin());


        if(command == exitComand) {
			break;
		}
        if (command == "") {
            std::cout << "Enter something\n";
            continue;
        }
        if (command == enterComand) {
            tree.clear();
            tree.createFrom(commandVector);
            if (tree.hasCreationError()) {
                std::cout << "Inaccuracy in formula, tree was auto-repaired\n";
            }
            std::cout << "Tree created\n";
        }
        if (tree.isCreated()) {
            if (command == varsComand) {
                tree.printVariables();
            }
            else if (command == printComand) {
                tree.printTree();//postac prefiksowa nie graficzna
            }
            else if (command == printgComand) {
                tree.printTreeGraphically();
            }
            else if (command == compComand) {
                if(commandVector.size() != tree.getVariablesCount() ) {
					std::cout << "Expected "<< tree.getVariablesCount()<<" variables\n";
					continue;
				}
                tree.calculateFormula(commandVector);
            }
            else if (command == joinComand) {
                if(commandVector.size()==0) {
					std::cout << "Expected tree expression\n";
					continue;
				}
                CTree otherTree;
                otherTree.createFrom(commandVector);
                tree = tree + otherTree;
                std::cout << "Tree joined\n";
            }
        }
        else if (command == printComand || command == varsComand) {
            std::cout << "Tree not created yet\n";
        }
        else if (command.find(compComand) == 0 || command.find(joinComand) == 0) {
            std::cout << "Tree not created yet\n";
        }
        else {
            std::cout << "Unknown command, valid commands: enter <form>, vars, print, printg, comp <v1,v2,..>, exit." << std::endl;
        }

    } while (true);
}