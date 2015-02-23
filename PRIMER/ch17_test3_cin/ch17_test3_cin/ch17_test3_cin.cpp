// ch17_test3_cin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Enter numbes: ";
	int sum = 0;
	int input;

	try{
		while (cin >> input)               //when input illegal number, for example 123Z, input will be 123. and cin>>input
			//will return false.
		{
			sum += input;
		}
	}
	catch (ios_base::failure& bf)  //catch what kind of failure.
	{
		cout << bf.what() << endl;
		cout << "Failure happens." << endl;
	}

	cout << "Last value entered = " << input << endl;
	cout << "Sum = " << sum << endl;
	system("pause");
	return 0;
}

