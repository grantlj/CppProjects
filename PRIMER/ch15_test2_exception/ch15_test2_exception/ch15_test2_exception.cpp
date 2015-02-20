// ch15_test2_exception.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Windows.h"
#include <cstdlib>     //for abort function use.
using namespace std;

inline double foo(double& a, double& b);

int _tmain(int argc, _TCHAR* argv[])
{
	cout.precision(3);
	cout.setf(ios::fixed);
	cout << "Input two number a, b:";
	double a, b;
	cin >> a >> b;

	//if (b == 0)
	//	abort();   //call abort to finish the program.
	//else
	
	try
	{
		cout << "a/b=" << foo(a,b) << endl;
	}
	catch (const char* s)   //const char* s is the ERR MESSAGE STRING.
	{
		cout << "Error:" << s << endl;
		cout << "Calling abort()" << endl;
		abort();
	}
	system("pause");
	return 0;
}
 inline double foo(double& a, double& b)
{
	if (b != 0)
		return a / b;
	else
		throw "divided by 0."; //throw out an exception.
}
