// ch8_test2_reference.cpp : 引用（也可以看成是真实变量的别名），用来处理只能传递形参的问题。

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

inline void swapr(int& a, int& b)    //你就把int&看成pascal里面带var的形参（也就是最后会返回新的值）
{
	int t = a;
	a = b;
	b = t;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a, b;
	cin >> a >> b;
	swapr(a, b);                 //调用也一样，没什么区别。
	cout << a << "," << b << endl;
	system("pause");
	return 0;
}

