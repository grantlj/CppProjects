// ch9_test1_include.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
//#include "myswap.h"   //method 1, using include to do.
using namespace std;

extern void myswap(int& a, int& b);   //method 2, directly using extern, extern will be used in the LINKING STAGE.
                                     // ˵���˾������ñ��c++�����е�ȫ�ֱ���������������Ҫinclude�ˣ�����ȫ�ֱ�����

int _tmain(int argc, _TCHAR* argv[])
{
	int a, b;
	cin >> a >> b;

	myswap(a, b);
	cout << a << "," << b << endl;

	system("pause");
	return 0;

}

