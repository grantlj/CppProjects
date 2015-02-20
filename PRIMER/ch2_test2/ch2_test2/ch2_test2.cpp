// ch2_test2.cpp : Tests on cpp function.
//

#include "stdafx.h"
#include<iostream>
#include<cmath>
#include<Windows.h>

double mysqrt(double);

int _tmain(int argc, _TCHAR* argv[])
{
	//if we put using namepace std here, only the main function 
	//can use std::
	using namespace std;
	double area;
	cout << "Enter the floor area:";
	cin >> area;
	
	double side = mysqrt(area);
	cout << "The size of house is:"
		<< side
		<< endl;
	system("pause");
}

double mysqrt(double area)
{
	return sqrt(area);
}
