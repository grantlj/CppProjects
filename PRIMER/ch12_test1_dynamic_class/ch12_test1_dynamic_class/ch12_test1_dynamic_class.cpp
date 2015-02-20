// ch12_test1_dynamic_class.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "string1.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int ArSize = 10;
const int MaxLen = 81;

int _tmain(int argc, _TCHAR* argv[])
{
	{
		String name;
		cout << "Hi, what is your name?" << endl;
		cin>>name;

		cout << name << ", please enter up-to " << ArSize
			<< " short saying <empty line to quit>:" << endl;
		String sayings[ArSize];
		char temp[MaxLen];
		
		int i;
		for (i = 0; i < ArSize; i++)
		{
			cout << i + 1 << ": ";
			cin.get(temp, MaxLen);
			while (cin && cin.get() != '\n')
				continue;
			if (!cin || temp[0] == '\0') //empty line.
				break;
			else
				sayings[i] = temp;
		}

		int total = i;
		if (total > 0)
		{
			cout << " Here are your sayings:\n";
			for (i = 0; i < total; i++)
				cout << sayings[i][0] << ":" << sayings[i] << endl;
		}

	}
	system("pause");
	return 0;
}

