// ch4_test1.cpp : Test on array and string.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;
const int N = 100;

int _tmain(int argc, _TCHAR* argv[])
{
	int number[N] = {};   //all elements are 0.
	int total = 0;
	for (int i = 0; i < N; i++)
	{
		number[i] = i;
		total += number[i];
	}

	cout << "total=" << total<<endl;

	int num_element = sizeof(number) / sizeof(number[0]);  //the trick!
	cout << "The length of the array is:" << num_element<<endl;

	char bird[] = "Bubble";
	char cat[] = "hello" "moto";  //constant string concate.
	cout << bird << endl;
	cout << cat << endl;
	system("pause");
	return 0;
}

