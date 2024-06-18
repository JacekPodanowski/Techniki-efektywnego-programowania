#pragma once
#include <string>
#include <vector>
#include <sstream>
std::vector<std::string> splitString(std::string input, char delimiter);
template <typename T>
std::vector<T> castToType(std::vector<std::string> input);

