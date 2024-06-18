#define _USE_MATH_DEFINES
#include "TreeData.h"
#include "CTree.h"
#include <string>
#include <cmath>
const double DEG_TO_RAD = M_PI / 180.0;

TreeData<std::string> TreeData<std::string>::fromString(std::string str) {
	return TreeData<std::string>(str);
}

TreeData<int> TreeData<int>::fromString(std::string str) {
	return TreeData<int>(std::stoi(str));
}

TreeData<double> TreeData<double>::fromString(std::string str) {
	return TreeData<double>(std::stod(str));
}
TreeData<bool> TreeData<bool>::fromString(std::string str) {
	if (str == "1") {
		return TreeData<bool>(true);
	}
	return TreeData<bool>(false);
}

int TreeData<int>::operator+(const TreeData<int>& other)
{
	return data + other.data;
}
double TreeData<double>::operator+(const TreeData<double>& other)
{
	return data + other.data;
}
std::string TreeData<std::string>::operator+(const TreeData<std::string>& other)
{
	std::string result = data;
	result.erase(result.size() - 1);
	result += other.data.substr(1,other.data.size());
	return result;
}
bool TreeData<bool>::operator+(const TreeData<bool>& other)
{
	if (data == true || other.data == true) {
		return true;
	}
	return false;
}

int TreeData<int>::operator-(const TreeData<int>& other)
{
	return data - other.data;
}
double TreeData<double>::operator-(const TreeData<double>& other)
{
	return data - other.data;
}
std::string TreeData<std::string>::operator-(const TreeData<std::string>& other)
{
	std::string result = data;
	std::string minus = other.data.substr(1, other.data.size() - 2);
	size_t pos = result.rfind(minus);
	if (pos != std::string::npos) {
		result.erase(pos, minus.size());
	}
	return result;
}
bool TreeData<bool>::operator-(const TreeData<bool>& other)
{
	if (data == true && other.data == true) {
		return false;
	}
	return true;
}

int TreeData<int>::operator*(const TreeData<int>& other)
{
	return data * other.data;
}
double TreeData<double>::operator*(const TreeData<double>& other)
{
	return data * other.data;
}
std::string TreeData<std::string>::operator*(const TreeData<std::string>& other)
{
	std::string result = data;
	std::string mul = other.data.substr(1, other.data.size() - 2);
	if (mul!= NO_VALUE_DEFAULT_STRING&&!mul.empty()) {
		size_t firstCharPos = result.find(mul[0]);

		while (firstCharPos != std::string::npos) {
			result.insert(firstCharPos + 1, mul.substr(1));
			firstCharPos = result.find(mul[0], firstCharPos + 1);
		}
	}

	return result;
}
bool TreeData<bool>::operator*(const TreeData<bool>& other)
{
	if (data == true && other.data == true) {
		return true;
	}
	if (data == false && other.data == false) {
		return true;
	}
	return false;
}

int TreeData<int>::operator/(const TreeData<int>& other)
{
	return data / other.data;
}
double TreeData<double>::operator/(const TreeData<double>& other)
{
	return data / other.data;
}
std::string TreeData<std::string>::operator/(const TreeData<std::string>& other)
{
	std::string result = data;
	std::string divisor = other.data.substr(1, other.data.size() - 2);
	if (divisor != NO_VALUE_DEFAULT_STRING && !divisor.empty()) {
		size_t firstCharPos = result.find(divisor[0]);

		while (firstCharPos != std::string::npos) {
			result.erase(firstCharPos+1, divisor.size()-1);
			firstCharPos = result.find(divisor[0], firstCharPos + 1);
		}
	}

	return result;
}
bool TreeData<bool>::operator/(const TreeData<bool>& other)
{
	if (data == true && other.data == true) {
		return true;
	}
	if (data == false && other.data == false) {
		return true;
	}
	return false;
}

int TreeData<int>::sin()
{
	return std::sin(data* DEG_TO_RAD);
}
double TreeData<double>::sin()
{
	return std::sin(data* DEG_TO_RAD);
}
std::string TreeData<std::string>::sin()
{
	return "sin(" +data+")";
}
bool TreeData<bool>::sin()
{
	return false;
}

int TreeData<int>::cos()
{
	return std::cos(data * DEG_TO_RAD);
}

double TreeData<double>::cos()
{
	return std::cos(data * DEG_TO_RAD);
}
std::string TreeData<std::string>::cos()
{
	return "cos(" + data + ")";
}
bool TreeData<bool>::cos()
{
	return false;
}

template <>
bool TreeData<int>::isValue(std::string str) {
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

template <>
bool TreeData<double>::isValue(std::string str) {
	if (str.empty()) {
		return false;
	}
	int dotcount = 0;
	for (int i = 0; i < str.size(); i++) {
		if (!std::isdigit(str[i]) && str[i] != '.') {
			return false;
		}
		if (str[i] == '.') {
			dotcount++;
		}
	}
	if (str[0] == '.') {
		str = "0" + str;
	}
	return dotcount<=1;
}


template <>
bool TreeData<std::string>::isValue(std::string str) {
	if (!str.empty() && str.front() == '"' && str.back() == '"') {
		for (int i = 1; i < str.size() - 1; i++) {
			if (str[i] == '"') {
				return false;
			}
		}
		return true;
	}
	return false;
}

template <>
bool TreeData<bool>::isValue(std::string str) {
	if (str == "1" || str == "0") {
		return true;
	}
	return false;
}
template class TreeData<int>;
template class TreeData<double>;
template class TreeData<std::string>;
template class TreeData<bool>;