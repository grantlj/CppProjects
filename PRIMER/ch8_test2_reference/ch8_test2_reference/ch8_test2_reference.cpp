// ch8_test2_reference.cpp : ���ã�Ҳ���Կ�������ʵ�����ı���������������ֻ�ܴ����βε����⡣

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

inline void swapr(int& a, int& b)    //��Ͱ�int&����pascal�����var���βΣ�Ҳ�������᷵���µ�ֵ��
{
	int t = a;
	a = b;
	b = t;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a, b;
	cin >> a >> b;
	swapr(a, b);                 //����Ҳһ����ûʲô����
	cout << a << "," << b << endl;
	system("pause");
	return 0;
}

