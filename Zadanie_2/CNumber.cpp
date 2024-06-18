#include "CNumber.h"
#include <iostream>


int CNumber :: GetLengthInBase(int value, int base) {
    if (value < 0 || base <= 1) {
        return 0;
    }

    int length = 1;
    int tempValue = value;

    while (tempValue >= base) {
        tempValue /= base;
        length++;
    }

    return length;
}

std::string CNumber::ToString() const {
    return toString();
}
std::string CNumber::toString() const{
    std::string result = b_isNegative ? "-[" : "[";
    bool isZero = true;

    for (int i = i_length - 1; i >= 0; --i) {
        if (pi_number[i] != 0) {
			isZero = false;
		}
        if (!isZero) {
			result += std::to_string(pi_number[i]);
            if (i > 0) {
				result += " ";
			}
		}
	}  
    result += "]";
    return result;
}

void CNumber::Clear() {
    for (int i = 0; i < i_length; i++) { pi_number[i] = 0; }
	b_isNegative = false;
}


int CNumber::GetDigit(const int pos) const {
    if (pos < 0 || pos >= i_length) {
       return 0;
	}
    return pi_number[pos];
}

void CNumber::SetDigit(const int pos, int value) {
    if (pos >= i_length) {
        int newLen = pos + NUMBER_DEFAULT_LENGTH;
        int* tmp = new int[newLen];
        for (int i = 0; i < i_length; i++)
        {
            tmp[i] = pi_number[i];
        }
        for (int j = i_length; j < newLen; j++)
        {
            tmp[j] = 0;
        }
        delete[] pi_number;
        pi_number = tmp;
        i_length = newLen;
	}
    pi_number[pos] = value;
}


void CNumber::operator=(const int iValue) {
    Clear();
    b_isNegative = iValue < 0;
    int cValue = abs(iValue);
    int len = GetLengthInBase(cValue, numeralSystemBase);
    for (int i = 0; i < len; i++)
    {
        SetDigit(i, cValue % numeralSystemBase);
        cValue /= numeralSystemBase;
    }
}

void CNumber::operator=(const CNumber& other) {
    Clear();
    for (int i = 0; i < other.i_length; ++i) {
        SetDigit(i,other.GetDigit(i));
    }
    b_isNegative = other.b_isNegative;
}

void CNumber::operator=(const CNumber* other) {
    Clear();
	for (int i = 0; i < i_length; ++i) {
		SetDigit(i, other->GetDigit(i));
	}
	b_isNegative = other->b_isNegative;
}



CNumber CNumber::operator+(CNumber& other) {
    if (!b_isNegative&&!other.b_isNegative) {//++
        return Add(other);
    }
    else if (b_isNegative && other.b_isNegative) {//--
		CNumber result = Add(other);
		result.SetNegative(true);
		return result;
	}
    else if (b_isNegative&&!other.b_isNegative) {//-+
		CNumber result = other.Sub(*this);
		//result.SetNegative(true);
		return result;
	}
    else {//+-
		return Sub(other);
	}
}
CNumber CNumber::operator+(int Value) {
    CNumber result;
    CNumber temp = Value;
    result = *this + temp;
    return result;
}

CNumber CNumber::Add(const CNumber& other)
{
    CNumber result;

    int len = std::max(i_length, other.i_length);
    int carry = 0;
    for (int i = 0; i < len; i++)
    {
        int sum = GetDigit(i) + other.GetDigit(i) + carry;
        result.SetDigit(i, sum % numeralSystemBase);
        carry = sum / numeralSystemBase;
    }
    if (carry>0)
        result.SetDigit(len, carry);
    return result;
}

CNumber CNumber::operator-(CNumber& other) {
    if (!b_isNegative && !other.b_isNegative) {//++
        if (IsGreater(other)) {
			return Sub(other);
		}
		CNumber result = other.Sub(*this);
		result.SetNegative(true);
		return result;
        
    }
    else if (b_isNegative && other.b_isNegative) {//--
        CNumber abs = other.Abs();
        if (Abs().IsGreater(abs)) {
            CNumber result = Sub(other);
            result.SetNegative(true);
            return result;
        }
        else {
            CNumber result = other.Sub(*this);
            result.SetNegative(false);
            return result;
        }
    }
    else if (b_isNegative && !other.b_isNegative) {//-+
        CNumber abs=other.Abs();
        if (Abs().IsGreater(abs)) {
            return Sub(other);  
        }
        else {
            CNumber result = other.Sub(*this);
			result.SetNegative(false);
			return result;
        }
    }
    else {//+-
        return Add(other);
    }
}

CNumber CNumber::Sub(const CNumber& other) 
{
    CNumber result;

    int len = std::max(i_length, other.i_length);
    SetDigit(len, 0);
    int carry = 0;
    for (int i = 0; i < len; i++)
    {
        int sum = GetDigit(i) - other.GetDigit(i) - carry;
        if (sum < 0) {
            sum += numeralSystemBase;
            carry = 1;
        }
        else {
            carry = 0;
        }
        result.SetDigit(i, sum % numeralSystemBase);
    }
    return result;
}

bool CNumber::IsZero() const
{
    for (int i = 0; i < i_length; i++)
    {
        if (pi_number[i] != 0) {
            return false;
        }
    }
    return true;
}

CNumber CNumber::operator*(CNumber& other) {
    int len1 = i_length;
    int len2 = other.i_length;
    int resultLen = len1 + len2;

    CNumber result;
    if(b_isNegative&&other.b_isNegative)
		result.SetNegative(false);
	else if (b_isNegative || other.b_isNegative)
        result.SetNegative(true);
    for (int i = 0; i < resultLen; i++) {
        result.SetDigit(i, 0);
    }

    for (int i = 0; i < len1; i++) {
        int carry = 0;
        for (int j = 0; j < len2; j++) {
            int product = GetDigit(i) * other.GetDigit(j) + result.GetDigit(i + j) + carry;
            carry = product / numeralSystemBase;
            result.SetDigit(i + j, product % numeralSystemBase);
        }

        int k = i + len2;
        while (carry > 0) {
            int sum = result.GetDigit(k) + carry;
            carry = sum / numeralSystemBase;
            result.SetDigit(k, sum % numeralSystemBase);
            k++;
        }
       
    }
    return result;
}
CNumber CNumber::operator*(int Value) {
    CNumber result;
    CNumber temp = Value;
    result = *this * temp;
    return result;
}
bool CNumber::operator>(CNumber& other) {
    	return IsGreater(other);
}
bool CNumber::operator>=(CNumber& other) {
    return IsGreater(other)||Equal(other);
}

/*CNumber CNumber::operator/(CNumber& other) {
    CNumber result;
    if (b_isNegative && other.b_isNegative)
        result.SetNegative(false);
    else if (b_isNegative || other.b_isNegative)
        result.SetNegative(true);

	CNumber dividend = Abs();
	CNumber divisor = other.Abs();

    if (divisor.IsZero()) {
		return result;
	}

    if (dividend.IsZero()) {
		return result;
	}
    int counter = 0;
    while (dividend.IsGreater(divisor)||dividend.Equal(divisor) ){
		dividend = dividend - divisor;
		counter++;
	}
    result = counter;
	return result;
}  */ 

CNumber CNumber::operator/(CNumber& other) {
    CNumber result;
    if (other.IsZero()) {
        return result;
    }
    if (IsZero()) {
        return result;
    }
    if (Equal(other)) {
        if(b_isNegative&&other.b_isNegative)
			result = 1;
		else if (b_isNegative || other.b_isNegative)
			result = -1;
		else
			result = 1;
        return result;
    }

    if (b_isNegative && other.b_isNegative)
        result.SetNegative(false);
    else if (b_isNegative || other.b_isNegative)
        result.SetNegative(true);

    int firstNonZeroDigit = FirstNonZeroDigit();
    CNumber dividend = pi_number[firstNonZeroDigit];
    CNumber divisor = other.Abs();

    while (firstNonZeroDigit >= 0){
        if (dividend >= divisor) {
            int counter = 0;
            while (dividend.IsGreater(divisor) || dividend.Equal(divisor)) {
                dividend = dividend - divisor;
                counter++;
            }
            result.SetDigit(firstNonZeroDigit, counter);
        }
        else {
            dividend = dividend * numeralSystemBase + pi_number[--firstNonZeroDigit];

        }
    }
    return result;
}

bool CNumber::IsGreater(CNumber& other) const{
    if (b_isNegative && !other.b_isNegative) {
		return false;
	}
    else if (!b_isNegative && other.b_isNegative) {
		return true;
	}
    int firstNonZeroDigit = FirstNonZeroDigit();
    int otherFirstNonZeroDigit = other.FirstNonZeroDigit();

    if (firstNonZeroDigit > otherFirstNonZeroDigit) {
        if (b_isNegative && other.b_isNegative) {
            			return false;
        }
        return true;
    }
    if (firstNonZeroDigit < otherFirstNonZeroDigit) {
        if (b_isNegative && other.b_isNegative) {
            return true;
        }
        return false;
    }

    for (int i = firstNonZeroDigit; i >= 0; i--) {
        if (GetDigit(i) > other.GetDigit(i)) {
            if (b_isNegative && other.b_isNegative) {
                return false;
            }
			return true;
		}
        if (GetDigit(i) < other.GetDigit(i)) {
            if (b_isNegative && other.b_isNegative) {
				return true;
			}
			return false;
		}
	}
	return false;
}
bool CNumber::Equal(const CNumber& other) const {
    if (b_isNegative != other.b_isNegative) {
		return false;
	}
	int firstNonZeroDigit = FirstNonZeroDigit();
	int otherFirstNonZeroDigit = other.FirstNonZeroDigit();

    if (firstNonZeroDigit != otherFirstNonZeroDigit) {
		return false;
	}

    for (int i = firstNonZeroDigit; i >= 0; i--) {
        if (GetDigit(i) != other.GetDigit(i)) {
			return false;
		}
	}
	return true;
}
CNumber CNumber::Abs() const {
	CNumber result = *this;
	result.SetNegative(false);
	return result;
}

void CNumber::cDiv(CNumber& other, CNumber** Rest) {
    CNumber numberOfDivisions;
    numberOfDivisions = *this / other;

    if (numberOfDivisions.IsZero()) {
        *Rest = &other;
    }

    CNumber number = numberOfDivisions * other;
    CNumber result;
    result = *this - number;
    if (result.IsZero()) {
        Rest = nullptr;
    }
    **Rest = result;

}

int CNumber::FirstNonZeroDigit()const {
	int i = i_length - 1;
    while (i >= 0 && GetDigit(i) == 0) {
		i--;
	}
	return i;
}

