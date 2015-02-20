// ch3_test2.cpp : number radix representation and output.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	int chest = 42;     //decimal;
	int waist = 0x42;   //hex;
	int inseam = 042;   //octal


	//default output is in decimal.
	cout << "chest:" << chest << endl;
	cout << "waist:" << waist << endl;
	cout << "inseam" << inseam << endl;
	
	//changing number base to hex(the valid space will maintain until next changing)
	cout << hex;  //it is only a changing....
	cout << "In hex form:" << endl << endl;
	cout << "chest:" << chest << endl;
	cout << "waist:" << waist << endl;
	cout << "inseam" << inseam << endl;

	//changing number base to oct;
	
	cout << oct;
	cout << "In OCT form:" << endl << endl;
	cout << "chest:" << chest << endl;
	cout << "waist:" << waist << endl;
	cout << "inseam" << inseam << endl;

	system("pause");

	cout << "Now input a character:";
	char c;
	cin >> c;
	int i = c;
	cout << endl << "The character you have just input is:" << c << " With ASCII:"<<i<<endl;
	system("pause");
	return 0;
}

