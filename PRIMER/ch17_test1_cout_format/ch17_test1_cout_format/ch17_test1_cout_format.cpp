// ch17_test1_cout_format.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	   1. In std::cout default settings, char, string, number is printed as you considered originally.
	   2. However, float is printed with 6 bits. 0 at ENDS are ignored.
	   3. Whether using SCIENTIFIC REPRESENTATION METHOD depends ONLY ON the number itself, no matter 
	      it is double, float, int, long, etc.
	   
	   The rest part of this program shows the default output configurations of cout.
	*/

	cout << "1234567890" << endl;
	char ch = 'K';
	int t = 273;
	cout << ch << ":"<<endl;
	cout << t << ":" << endl;
	cout << -t << endl;

	//Very ordinay print above, nothing serious.

	double f1 = 1.200;
	cout << f1 << endl;  //1.200, no more than 6 bits.
	cout << (f1 + 1.0 / 9.0) << endl;  //1.31111, overall 6 bits.

	double f2 = 1.67E2;
	cout << f2 << endl;   //not 1.67E2, but 167, because E2, is no more than 6.

	f2 += 1.0 / 9.0;     //167.111
	cout << f2 << endl;
	cout << (f2*1.0e4) << endl; //1.671111e+006, expotential is more than 6.

	double f3 = 2.3e-4;  
	cout << f3 << endl;  //0.00023;
	cout << f3 / 10 << endl;  //2.3e-005;


	//Using format manipulator.
	cout << "Enter an integer: ";
	int n;
	cin >> n;
	cout << "n		n*n" << endl;
	cout << n << "		" << n*n << "(decimal)" << endl;
	
	//set to hex.
	cout << hex;
	cout << n << "		" << n*n << "(hexadecimal)" << endl;

	//set to oct.
	cout << oct;
	cout << n << "		" << n*n << "(octal)" << endl;
	
	//alternative way.
	dec(cout);
//	cout << "n		n*n" << endl;
	cout << n << "		" << n*n << "(decimal)" << endl;

	system("pause");
	return 0;
}

