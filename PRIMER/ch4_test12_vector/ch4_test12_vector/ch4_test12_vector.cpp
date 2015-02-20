// ch4_test12_vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <array>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//C++ 99 STL.
	vector<double> a2(4);
	a2[0] = 1.0 / 3.0;
	a2[1] = 1.0 / 5.0;
	a2[2] = 1.0 / 7.0;
	a2[3] = 1.0 / 9.0;
	a2.at(2) = 10;

	//C++ 11 STL: array.
	array<double, 6> a;
	a[1] = 1; a[2] = 2; a[3] = 3; a[4] = 4; a[5] = 5;
	cout << "Vctor:" << a2[2] << endl;
	cout << "Array:"<<a[1] << endl;
	

	//2D vector.
	vector<vector<int>> v2d(5);   //note the length!!!

	for (int i = 0; i < 5; i++)
	{
		v2d[i].resize(5);
		for (int j = 0; j < 5; j++)
			v2d.at(i).at(j) = i + j - 1;

	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << v2d.at(i).at(j) << " ";
		cout << endl;
	}
	system("pause");
	return 0;
}

