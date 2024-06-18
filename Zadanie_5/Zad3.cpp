#include <iostream>
#include "CommandHandler.h"
#include "sstream"
#include "CMySmartPointer.h"
#include "CTree.h"

int main() {
	std::string input;
	const std::string intType = "int";
	const std::string doubleType = "double";
	const std::string stringType = "string";
	const std::string boolType = "bool";
	const std::string TypeMessage = "Choose tree type: int, double, string, bool\n";

	CMySmartPointer<int> ptr(new int(5));
	CMySmartPointer<int> ptr2(ptr);
	ptr2.printPointers();

	//while (input != intType && input != doubleType && input != stringType && input!=boolType) {
		//std::cout << TypeMessage;
		//std::getline(std::cin, input);
	//}

	if (input == intType) {
		CommandHandler<int> commandHandler;
		commandHandler.run();
	}
	else if (input == doubleType) {
		CommandHandler<double> commandHandler;
		commandHandler.run();
	}
	else if (input == stringType) {
		CommandHandler<std::string> commandHandler;
		commandHandler.run();
	}
	else if (input == boolType) {
		CommandHandler<bool> commandHandler;
		commandHandler.run();
	}
    return 0;
}
