// ch3_test3.cpp : Unicode and wchar_t test.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int MAX_MONTH = 12;

int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t bob = L'P';           //we use L to denote wide char.
	wcout << L"tall" << bob << endl;  //use wcout to output/input wide char.


	//Boolean;

	//bool ok;
	//cin >> ok;       //note that here ok must be 0 or 1.
	//if (ok)
	//	cout << !ok << endl;

	cout << MAX_MONTH << endl;
	
	system("pause");
	return 0;

}

