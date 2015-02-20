// ch7_test2_FuncPointer_Callback.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

double betty(int);
double pam(int);
void estimate(int lines, double(*pf)(int));
/*
  estimate using a kinda callback purpose,to estimate the time on running function;
  *pf is a function, it paramters is int, and return double. Therefore, pf is a pointer, points to 
  such function.
  */


int _tmain(int argc, _TCHAR* argv[])
{
	int lines;
	cin >> lines;
	estimate(lines, betty);   //betty without (), betty is the ADDRESS of function betty/
    estimate(lines, pam);
	system("pause");
	return 0;
}

//betty and pam are functions prepared for estimating.
double betty(int lns)
{
	return 0.05*lns;
}

double pam(int lns)
{
	return 0.03*lns + 0.0004*lns*lns;
}

void estimate(int lines, double(*pf)(int))
{
	cout << lines << " lines will take ";
	cout << (*pf)(lines) << " hours\n";
}