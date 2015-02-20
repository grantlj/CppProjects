// ch4_test7_pointer.cpp : Pointer! Pointer!! Pointer!!!
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	int n;
	cin >> n;
	cin.get();
	string *str = new string[n];
	for (int i = 0; i < n; i++)
	{
		getline(cin, str[i]);
		cout << endl << "pos at: " << &str[i] << endl;  //find the position of string.
	}

	*/

	/*
	
	STAR IS AN OPERATOR!!!!!!!!!!!!!
	Always let the star adhere to the variable name.
	It implies that *ptr is a int.

	On the other hand, num1 is a int.
	*/
	int *ptr, num1;
	num1 = 100;
	ptr = &num1;
	cout << *ptr << endl;

	system("pause");
	return 0;
}

