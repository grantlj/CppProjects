// ch9_test1_include.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
//#include "myswap.h"   //method 1, using include to do.
using namespace std;

extern void myswap(int& a, int& b);   //method 2, directly using extern, extern will be used in the LINKING STAGE.
                                     // 说白了就是引用别的c++代码中的全局变量！！！！不需要include了，引用全局变量！

int _tmain(int argc, _TCHAR* argv[])
{
	int a, b;
	cin >> a >> b;

	myswap(a, b);
	cout << a << "," << b << endl;

	system("pause");
	return 0;

}

