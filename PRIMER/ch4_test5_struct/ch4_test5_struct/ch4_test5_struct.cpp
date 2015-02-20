// ch4_test5_struct.cpp : C++ struct test.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

struct SStudent
{
	string name;
	double weight;

};
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Please input n=" << endl;
	int n;
	cin >> n;
	cin.get();
	SStudent *stu = new SStudent[n];
	for (int i = 0; i < n; i++)
	{
		string tmpstr;
		getline(cin, tmpstr);
		int commapos=tmpstr.find(",", 0);
		stu[i].name = tmpstr.substr(0, commapos);
		stu[i].weight = atof(tmpstr.substr(commapos + 1).data());
		cout << "Student No." << i << " Name:" << stu[i].name << " Weight:" << stu[i].weight << endl;

	}

	stu[1] = stu[2];  //a struct can directly copy between two variables.
	system("pause");
	return 0;
}

