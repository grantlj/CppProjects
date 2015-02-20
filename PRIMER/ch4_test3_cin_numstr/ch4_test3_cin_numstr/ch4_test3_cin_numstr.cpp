// ch4_test3_cin_numstr.cpp : multiply input number and character.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int STR_MAX_LEN = 255;
int _tmain(int argc, _TCHAR* argv[])
{
	char address[STR_MAX_LEN];
	int year;
	cout << "Input house built:";
	cin >> year;
 //	cin.get();   //read a new line;
	//cin.clear();
	cin.getline(address, STR_MAX_LEN);
	cout << "Year built:" << year << endl;
	cout << "Address:" << address << endl;
	system("pause");
	return 0;
}

