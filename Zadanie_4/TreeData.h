#pragma once
#include <string>
template <typename T>
class TreeData
{
public:
	T data;

	TreeData(T data)
	{
		this->data = data;
	}

	T operator+(const TreeData<T>& other);
	T operator-(const TreeData<T>& other);
	T operator*(const TreeData<T>& other);
	T operator/(const TreeData<T>& other);

	T sin();
	T cos();

	static bool isValue(std::string str);
	T getValue(){ return data;}
	static TreeData<T> fromString(std::string str);
};
