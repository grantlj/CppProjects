// ch9_test5_explicit_specialization.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

template <class T>
void myswap(T& a, T& b);


struct job
{
	char name[40];
	double salary;
	int floor;
};

//explicit specilization.
//Grammer template<> function.
template<>  void myswap<job>(job& j1, job& j2);

void show(const job &j);  //define it as const, READ ONLY.

int _tmain(int argc, _TCHAR* argv[])
{
	cout.precision(2);
	cout.setf(ios::fixed, ios::floatfield);

	int i = 10, j = 20;
	cout << "i,j=" << i << ", " << j << ".\n";
	myswap(i, j);       //using default void myswap(T& a, T& b) 
	cout << "Now i, j=" << i << ", " << j << ".\n";

	job sue = { "Susan Yaffee", 73000.60, 7 };
	job sidney = { "Sidney Taffee", 78060.72, 9 };

	cout << "Before job swapping:\n";
	show(sue);
	show(sidney);

	myswap(sue, sidney);

	cout << "After job swapping:\n";
	show(sue);
	show(sidney);

	system("pause");
	return 0;
}



template<class T>          //do not forget this template.
void myswap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}


//Explicit specilization.
template<> void myswap<job>(job& j1, job& j2)
{
	double t1;
	int t2;
	t1 = j1.salary;
	j1.salary = j2.salary;
	j2.salary = t1;

	t2 = j1.floor;
	j1.floor = j2.floor;
	j2.floor = t2;
	
	//cout << "Swapping...." << endl;
	//show(j1);
	//show(j2);
}


void show(const job& j)
{
	cout << j.name << ": $" << j.salary << " on floor " << j.floor << endl;
}

