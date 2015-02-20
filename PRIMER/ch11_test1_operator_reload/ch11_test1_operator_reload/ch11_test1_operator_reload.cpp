// ch11_test1_operator_reload.cpp : 运算符重载和友元，从外部获得内部访问权限，使得可以直接cout<<我们的对象。
//

#include "stdafx.h"
#include <iostream>
#include "mytime1.h"
#include <Windows.h>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Time planning;
	Time coding(2, 40);
	Time fixing(5, 55);
	Time total;

	cout << "Planning time=";
	planning.Show();
	
	cout << "Coding time=";
	coding.Show();

	cout << "Fixing time=";
	fixing.Show();

	//operator notation.
	total = coding + fixing;
	cout << " coding+fixing=";
	total.Show();
	
	Time morefixing(3, 28);
	cout << "more fixing time= ";
	morefixing.Show();

	//Another operator notation.
	total = morefixing.operator+(total);
	cout << " more fixing.operator+(total)=";
	cout << total << endl;         //Using friend to print.

	system("pause");
	return 0;
}

