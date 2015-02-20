// ch9_test4_template.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using std::cout;
using std::endl;

template<class T>       //using template to implement further swap.

void swap(T& a, T& b)  //What's this? reference!! retunable parameter!
{
	T tmp = a;
	a = b;
	b = tmp;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int i = 10, j = 20;
	swap(i, j);
	cout << i << ',' << j << endl;

	double a = 5.0, b = 5.1;
	swap(a, b);
	cout << a << ',' << b << endl;
	system("pause");
	return 0;
}

