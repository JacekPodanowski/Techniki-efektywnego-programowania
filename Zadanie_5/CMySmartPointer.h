#pragma once
#include <iostream>
#include <vector>

template <typename T>
class CMySmartPointer
{
public:
    CMySmartPointer(T* pcPointer)
    {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd(pcPointer);
    }

    CMySmartPointer(const CMySmartPointer& pcOther)
    {
        pc_pointer = pcOther.pc_pointer;
        pc_counter = pcOther.pc_counter;
        pc_counter->iAdd(pcOther.pc_pointer);
    }

    ~CMySmartPointer()
    {
        if (pc_counter->iDec(pc_pointer) == 0)
        {
            delete pc_counter;
        }
    }

    CMySmartPointer& operator=(const CMySmartPointer& pcOther)
    {
        if (this != &pcOther)
        {
            if (pc_counter->iDec(pc_pointer) == 0)
            {
                delete pc_counter;
            }

            pc_pointer = pcOther.pc_pointer;
            pc_counter = pcOther.pc_counter;
            pc_counter->iAdd(pcOther.pc_pointer);
        }

        return *this;
    }

    T& operator*() const { return (*pc_pointer); }
    T* operator->() const { return pc_pointer; }

    void printPointers() const
	{
		std::cout << "Pointers: " << pc_counter->iGet() << std::endl;
		for (int i = 0; i < pc_counter->vGetPointers().size(); i++)
		{
			std::cout << pc_counter->vGetPointers()[i] << std::endl;
		}
	}

private:
    class CRefCounter
    {
    public:
        CRefCounter() : i_count(0) {}

        int iAdd(T* pointer)
        {
            v_pointers.push_back(pointer);
            return (++i_count);
        }

        int iDec(T* pointer)
        {
            for (int i = 0; i < v_pointers.size(); i++)
            {
                if (v_pointers[i] == pointer)
                {
                    v_pointers.erase(v_pointers.begin() + i);
                    return (--i_count);
                }
            }
            return (--i_count);
        }

        int iGet() const { return i_count; }
        const std::vector<T*>& vGetPointers() const { return v_pointers; }

    private:
        int i_count;
        std::vector<T*> v_pointers;
    };

    CRefCounter* pc_counter;
    T* pc_pointer;
};
