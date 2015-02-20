// ch4_test9_pointer3.cpp : pointer 3: 2D array.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cin >> n;
	cin.get();
	
	int** arr = new int* [n];  //arr是一个指针，我们在内存中建立了一个int*型数组，数组的大小为n，每个元素是int*，这个数组的
	                          //地址返回给 int** arr，指向int*型数组的指针arr int* [n]叫做行指针。
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[5];  //arr[i]对应的是行指针，量纲是int* 这次给的值是一个int数组的第一个元素的地址。
		for (int j = 0; j < 5; j++)
			arr[i][j] = i*j - 1;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}

	system("pause");
	return 0;
}

