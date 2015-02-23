// ch16_test2_string_fileio.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream fin;
	fin.open("D:\\CppProjects\\PRIMER\\ch16_test2_string_fileio\\1.txt");

	if (!fin.is_open())  //distinct whether file exist.
	{
		//CERR is a class specific for print error message.
		cerr << "IO Failure." << endl;
		system("pause");
		exit(EXIT_FAILURE);  //EXIT FAILURE IS DIRECT END PROGRAM WITH A CONST EXIT_FAILURE.
	}

	string item;
	int count = 0;
	
	//getline, read a line, the end separate signal is :.(default is \n)
	getline(fin, item, ':');

	while (fin)
	{
		count++;
		cout << count << ":" << item << endl;
		getline(fin, item,':');
	}
	cout << "Done" << endl;
	fin.close();
	system("pause");
	return 0;
}

