#include <iostream>
#include "CNumber.h"
#include <cmath>
#include "Zad2.h"
using namespace std;


void _assert(bool val)
{
    if (!val)
    {
		cout << "Assertion failed\n";
		exit(1);
	}
    cout<< "Assertion passed\n";
}


void TestAsing()
{
    CNumber test0;
    _assert(test0.toString() == "[]");
    CNumber test1(1);
    _assert(test1.toString() == "[1]");
    CNumber test2(123);
    _assert(test2.toString() == "[1 2 3]");
    CNumber test3(-1);
    _assert(test3.toString() == "-[1]");
}

void TestAdd()
{
    int in1[] = { 1, 2, 3 , 100, 1000, 10000, 12345678,-30,5, -10,18 };
    int in2[] = { 1, 2, 3 , 100, 1000, 10000 ,2,       -30,-4, 15,2 };
    int out[] = { 2, 4, 6,  200, 2000, 20000 ,12345680,-60,1,  5, 20 };

    for (int i = 0; i < sizeof(in1) / sizeof(in1[0]); i++)
    {
        CNumber testA(in1[i]);
        CNumber testB(in2[i]);
        CNumber testC(out[i]);
        CNumber result = testA + testB;
        _assert(result.toString() == testC.toString());
    }
}

void TestGrater(){

    int in1[] = { 1,   -2,    3 ,  -1,     1 };
    int in2[] = { 0,    2,    3 ,    -2 ,   3 };
    int out[] = { true, false, false,true, false };

    for (int i = 0; i < sizeof(in1) / sizeof(in1[0]); i++)
    {
        CNumber testA(in1[i]);
        CNumber testB(in2[i]);

        bool result = testA > testB;
        _assert(result == out[i]);
    }
}

void TestSub()
{
    int in1[] = { 1, 10,15 , 1230, -120 ,-5,0,-5};
    int in2[] = { 1, 2, 20 , 200, -125 ,-2,0,-5};
    int out[] = { 0, 8, -5,  1030, 5 ,  -3,0,0};

    for (int i = 0; i < sizeof(in1) / sizeof(in1[0]); i++)
    {
        CNumber testA(in1[i]);
        CNumber testB(in2[i]);
        CNumber testC(out[i]);
        CNumber result = testA - testB;
        _assert(result.toString() == testC.toString());
    }
}

void TestMul() {
    int in1[] = { 1, 10, 15, 1230, -120, -5, 0, -5 };
    int in2[] = { 1, 2, 20, 200, -125, -2, 0, -5 };
    int out[] = { 1, 20, 300, 246000, 15000, 10, 0, 25 };

    for (int i = 0; i < sizeof(in1) / sizeof(in1[0]); i++) {
        CNumber testA(in1[i]);
        CNumber testB(in2[i]);
        CNumber testC(out[i]);
        CNumber result = testA * testB;
        _assert(result.toString() == testC.toString());
    }
}

void TestDiv() {
    int in1[] = { 520, 20, 100, 1000, -120, -8, 0, -25 };
    int in2[] = { 5, 5, 10, 100, -4, -2, 1, -5 };
    int out[] = { 104, 4, 10, 10, 30, 4, 0, 5 };

    for (int i = 0; i < sizeof(in1) / sizeof(in1[0]); i++) {
        CNumber testA(in1[i]);
        CNumber testB(in2[i]);
        CNumber testC(out[i]);
        CNumber result = testA / testB;
        _assert(result.toString() == testC.toString());
    }
}



int main()
{


    //TestAsing();
    //TestAdd();
    //TestGrater();
    //TestSub();
    //TestMul();
    //TestDiv();

    CNumber test1=1234;
    CNumber test2=4567;
    CNumber test3=1;
    CNumber* test4=&test3;
    CNumber test5 = test1 / test2;
    std::cout << test1.toString()<<"\n";
    std::cout << test2.toString() << "\n";
    std::cout << test5.toString() << "\n";
   // test1.cDiv(test2, &test4);

  //  CNumber answer= *test4;
   // std::cout << answer.toString() << "\n";

}
