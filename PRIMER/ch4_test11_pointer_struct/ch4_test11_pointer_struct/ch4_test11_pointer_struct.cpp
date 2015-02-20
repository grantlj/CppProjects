// ch4_test11_pointer_struct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

struct inflatable
{
	string name;
	float volume;
	double price;
};


int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cout << "Input n:";
	cin >> n;
	inflatable* ins = new inflatable[n];

	for (int i = 0; i < n; i++)
	{
		(ins+i)->volume = i + 3.14;
		(ins+i)->price = rand()+3.14;
		(ins + i)->name = "aaa";
	}

	for (int i = 0; i < n; i++)
	{
		cout << "Name:"
			<< (ins + i)->name;
		cout << "Volume:"
		<< (ins + i)->volume;
		cout << "Price:"
			<< (ins + i)->price << endl;
	}

	delete[] ins;
	system("pause");
	return 0;
}

