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
	
	int** arr = new int* [n];  //arr��һ��ָ�룬�������ڴ��н�����һ��int*�����飬����Ĵ�СΪn��ÿ��Ԫ����int*����������
	                          //��ַ���ظ� int** arr��ָ��int*�������ָ��arr int* [n]������ָ�롣
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[5];  //arr[i]��Ӧ������ָ�룬������int* ��θ���ֵ��һ��int����ĵ�һ��Ԫ�صĵ�ַ��
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

