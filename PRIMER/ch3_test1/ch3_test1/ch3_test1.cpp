// ch3_test1.cpp : Check variable limits in VC++ 2013 x64.
//

#include "stdafx.h"
#include <iostream>
#include <climits>
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	int n_int = INT_MAX;
	INT n_short = SHRT_MAX;
	long n_long = LONG_MAX;
	long long n_llong = LLONG_MAX;
	cout << "INT:" << INT_MAX << " bytes:" << sizeof(INT_MAX) << endl;
	cout << "SHORT:" << SHRT_MAX << " bytes:" << sizeof(SHRT_MAX) << endl;
	cout << "LONG:" << LONG_MAX << " bytes:" << sizeof(LONG_MAX) << endl;
	cout << "LONG LONG:" << LLONG_MAX <<" bytes:"<<sizeof(LLONG_MAX)<<endl;

	//Conclusion: int is EQUAL to LONG in VC++
	system("pause");

	//A fresh-new method to define a variable.
	int hamburgers{ 27 };
	cout << "hamburger:" << hamburgers << endl;
	return 0;
}

