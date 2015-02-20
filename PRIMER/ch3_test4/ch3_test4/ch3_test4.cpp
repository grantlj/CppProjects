// ch3_test4.cpp : float number and IO.
//

#include "stdafx.h"
#include "iostream"
#include <Windows.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	cout.setf(ios_base::fixed, ios_base::floatfield);
	float tub = 10.0 / 3.0;
	double mint = 10.3 / 3.0;
	const float million = 1e6;
	cout << "tub:" << tub << endl;
	cout << "million=" << million*tub<<endl;
	cout << 10 * million*tub << endl;
	system("pause");
	return 0;
}

