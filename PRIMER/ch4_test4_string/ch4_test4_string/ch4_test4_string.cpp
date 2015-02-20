// ch4_test4_string.cpp : C++ string class.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	(cin >> n).get();
   string* strs=new string[n];  //In C++, define a array CAN'T with a variable length. string str[n] is wrong.
	for (int i = 0; i < n; i++)
		cin >> strs[i];
	
	for (int i = 0; i < n; i++)
		cout << strs[i]<<',' ;

	for (int i = 0; i < n - 1;i++)
	for (int j = i + 1; j < n; j++)
	{
		if (strs[i]>strs[j])
		{
			string tmp;
			tmp = strs[i];
			strs[i] = strs[j];
			strs[j] = tmp;
		}
	}
	cout << endl;
	cout << "After sort:";
	for (int i = 0; i < n; i++)
	{
		cout << strs[i];
		if (i != n - 1)
			cout << ',';


	}
	system("pause");
	return 0;
}

