// ch9_test3_default_parameter.cpp : 函数的默认参数。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int MAX_LEN = 50;

char* left(const char* str, int n = 1)  //default parameter n=1
{
	char* ans = new char[n + 1];
	
	//Another is using STATIC, the return value is absolutely static. \0 will be put at 1. STILL WRONG.
	//static char ans[MAX_LEN];

	//can we use: char ans[MAX_LEN] here? The answer is negative, because ans is a array,
	//it WILL BE CLEANED AFTER THIS FUNCTION. However, by using pointer, we can solve it.
	for (int i = 0; i < n; i++)
		ans[i] = str[i];
	ans[n] = '\0';
	return ans;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char sample[MAX_LEN];
	cin >> sample;
	cout << "Origin string:" << sample<<endl;

	char* ans = left(sample, 4);
	char* ans2 = left(sample);   //using default parameter.

	cout<< "With parameter 4:"<< ans << endl;
	cout << "With non-parameter:" << ans2 << endl;
	system("pause");
	return 0;
}

