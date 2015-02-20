// ch4_test6_enum.cpp : enum.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

enum spectrum{red, orange, yellow, green, blue, violet, indigo, ultraviolet};

int _tmain(int argc, _TCHAR* argv[])
{
	spectrum band;
	band = green;
	//band++;  invalid can't ++.
	cout << band << endl;
	//convert band to int.
	band = spectrum(5);
	cout << band << endl;
	system("pause");
	return 0;
}

