// ch8_test1_inline.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

inline double square(double x);
double square0(double x);

int _tmain(int argc, _TCHAR* argv[])
{
	int preTime, endTime;
	preTime = clock();

	for (int i = 0; i < 10000000; i++)
	{ 
		square0(i);
	}
	endTime = clock();
	cout << "Using classical function to calculate square:" << (endTime - preTime) << " ms"<<endl;

	preTime = clock();
	for (int i = 0; i < 10000000; i++)
	{
		square(i);
	}
	endTime = clock();

	cout << "Using inline function to calculate square:" << (endTime - preTime) << " ms" << endl;
	system("pause");
	return 0;
}

double square0(double x)
{
	return x;
}

//Using inline, in particular, for SHORT code periods, the performance will greatly enhanced.
inline double square(double x)
{
	return x*x;
}