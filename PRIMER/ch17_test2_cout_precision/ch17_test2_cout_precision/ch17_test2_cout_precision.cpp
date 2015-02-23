// ch17_test2_cout_precision.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	float price1 = 20.40;
	float price2 = 1.9 + 8.0 / 9.0;
	float price3 = 2;

	//ios_base showpoint, this parameter will make the output fullfill to default bits.(And obliged show 
	//float point.

	//For example, 2.5, is represented with 2.5000(in test1, we know that cout print default bits at 6)
	//Another example: 2 is represented with 2.

	cout.setf(ios_base::showpoint);
	cout << "Default setting, show point:" << endl;
	cout << "	Price 1: " << price1 << endl;
	cout << "	Price 2: " << price2 << endl;
	cout << "	Price 3: " << price3 << endl;

	cout.precision(10);
	cout << "Default setting, show point:" << endl;
	cout << "	Price 1: " << price1 << endl;
	cout << "	Price 2: " << price2 << endl;
	cout << "	Price 3: " << price3 << endl;

	system("pause");
	return 0;
}

