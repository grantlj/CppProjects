// ch4_test2_cin.cpp : cin输入多个字符串的特性.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int MAX_CHAR_LEN = 100;

int _tmain(int argc, _TCHAR* argv[])
{
	char name[MAX_CHAR_LEN];
	char birth_place[MAX_CHAR_LEN];
	/*
	The following code is wrong. As a stream, cin split strings with space.
	If we input Grant Liu as name, then Grant will be the name; liu will be 
	birth place.

	cout << "Name:" << endl;
	cin >> name;
	cout << "Birth place:" << endl;
	cin >> birth_place;
	cout << "User: " << name << "  Birth at:" << birth_place << endl;
	*/


	//The usage of getline. getline will ABANDON the enter.
	//getline is equal to readln in java, where get is equal to read.
	/*
	cout << "Name:" << endl;
	cin.getline(name, MAX_CHAR_LEN);
	cout << "Birth place:" << endl;
	cin.getline(birth_place, MAX_CHAR_LEN);
	cout << "User: " << name << "  Birth at:" << birth_place << endl;
    */

	//The usage of get.
//	cin.get(name, MAX_CHAR_LEN);
	
	cout << "Name:" << endl;
	cin.get(name, MAX_CHAR_LEN);
	cin.get();                    //it is a MUST.
	cout << "Birth place:" << endl;
	cin.get(birth_place, MAX_CHAR_LEN);
	cout << "User: " << name << "  Birth at:" << birth_place << endl;

	system("pause");
	return 0;
	
}

