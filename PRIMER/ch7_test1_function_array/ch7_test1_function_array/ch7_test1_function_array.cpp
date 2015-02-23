// ch7_test1_function_array.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

int do_sum(int** a,int n, int m);

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Input n,m:";
	int n, m;
	cin >> n >> m;
	
	int** a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];

	for (int i = 0; i < n;i++)
	for (int j = 0; j < m; j++)
		a[i][j] = i*j;

	int total = do_sum(a,n,m);
	cout << total << endl;
	system("pause");
	return 0;
}

int do_sum(int** a,int n, int m)
{
	int total = 0;
	for (int i = 0; i < n;i++)
	for (int j = 0; j < m; j++)
		total = total + a[i][j];
	return total;
}

