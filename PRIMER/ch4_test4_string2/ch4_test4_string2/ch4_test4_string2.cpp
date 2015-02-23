// ch4_test4_string2.cpp : c++ string test 2, string operations.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string str1="hello world";
	string str2=str1;           //this equal is absolutely copy!!!!! 
	str1[1] = 'X';
	cout << "Str1:"<< str1 << endl;
	cout << "Str2:"<< str2 << endl;

	str1 = str1 + str2;
	cout << "Added:" << str1 << endl;
	cout << "Length of str1:" << str1.length() << endl;
	system("pause");
	return 0;
}

