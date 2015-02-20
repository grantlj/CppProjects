// ch4_test10_pointer_str.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstring>   //C-style string.
#include <Windows.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	char animal[20] = "bear";              //animal is the first addr of "bear"(the pointer points to b)
	const char* bird = "wren";            // bird is a pointer points to w.
	char* ps;
	cout << animal << " and";
	cout << bird << "\n";

	cout << "Enter a kind of animal: ";
	cin >> animal;                       //ok, if input < 20 chars.

	ps = animal;
	cout << ps << "!\n";
	cout << "Before using strcpy():\n";
	cout << animal << " at " << (int*)animal << endl;   //OBLIGED TRANSFORM, although animal is an addr, however it points to a string. cout will print string.

	ps = new char[strlen(animal) + 1];
	strcpy(ps, animal);
	cout << "After using strcpy():\n";
	cout << animal << " at " << (int*)animal << endl;
	delete[] ps;
	
	system("pause");
	return 0;
}

