// ch16_test1_string_class.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Windows.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	//Using const string to construct.
	string one("Lottery Winner:"); 
	cout << one << endl;

	//Using 20 $ to construct.
	string two(20, '$');
	cout << two << endl;

	//Copy constructor function.
	string three(one);
	cout << three << endl;

	//overload operator.
	one += "oops!";
	cout << one << endl;

	string four;
	four = two + three;
	cout << four << endl;

	//using char[] to construct.
	char alls[] = "All's well that ends well";
	string five(alls, 20);
	cout << five << endl;

	system("pause");
	return 0;
}

