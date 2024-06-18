#pragma once
#define NUMBER_DEFAULT_LENGTH 10
#include <string>


class CNumber
{
public:
	const int numeralSystemBase = 10;


public:
	CNumber() {
		i_length = NUMBER_DEFAULT_LENGTH;
		pi_number = new int[i_length];
		for (int i = 0; i < i_length; i++) { pi_number[i] = 0;}
		b_isNegative = false;
	}
	CNumber(int iValue) {
		i_length = NUMBER_DEFAULT_LENGTH;
		pi_number = new int[i_length];
		for (int i = 0; i < i_length; i++) { pi_number[i] = 0; }
		*this = iValue;
	}
	CNumber(const CNumber& pcNewVal) {
		i_length = NUMBER_DEFAULT_LENGTH;
		pi_number = new int[i_length];
		for (int i = 0; i < i_length; i++) { pi_number[i] = 0; }
		*this = pcNewVal;
	}

	~CNumber() { delete[] pi_number; }
	void operator=(const int iValue);
	void operator=(const CNumber& other);
	void operator=(const CNumber* other);
	CNumber operator+(CNumber& other);
	CNumber operator+(int Value);
	CNumber operator*(CNumber& other);
	CNumber operator*(int Value);
	CNumber operator-(CNumber& other) ;
	CNumber operator/(CNumber& other);
	bool operator>(CNumber& other);
	bool operator>=(CNumber& other);

	std::string toString() const;
	std::string ToString() const;
	void vSetLength(int iNewLength) { i_length = iNewLength; }
	int iGetLength() const { return i_length; }
	bool IsNegative() const { return b_isNegative; }
	void SetNegative(bool bNewVal) {
		if (!IsZero()) {
			b_isNegative = bNewVal;
		}
	}
	void SetDigit(const int pos, int value);
	int static GetLengthInBase(int value, int base);
	CNumber Abs() const;
	bool Equal(const CNumber& other) const;
	void cDiv(CNumber& other, CNumber** Rest);

private:
	void Clear();
	int GetDigit(const int pos) const;
	
	CNumber Add(const CNumber& other);
	CNumber Sub(const CNumber& other) ;
	int FirstNonZeroDigit() const;
	bool IsGreater(CNumber& other) const;
	bool IsZero() const;
	

private:
	int* pi_number;
	int i_length;
	bool b_isNegative;

};