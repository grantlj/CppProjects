// ch11_test1_operator_reload.cpp : ��������غ���Ԫ�����ⲿ����ڲ�����Ȩ�ޣ�ʹ�ÿ���ֱ��cout<<���ǵĶ���
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

