// ch6_test1_fileio.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>       //fstream, file io.
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <Windows.h>
using namespace std;

struct SPerson
{
	string name;
	int age;
};

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream fin;
	
	fin.open("input.txt");
	ofstream fout;
	fout.open("output.txt");
	//fout.open("output.txt",ios_base::out|ios_base::app)  //this is the append mode.
	
	//fout.open("output.txt",ios_base::in|ios_base::binary) //binary mode. c++mode | ios_base::binary

	//For more details, please refer to C++ primer plus page 775, Table17.8.

    int n;
	fin >> n;
	fin.get(); //>> only reads the first integer. will not automatically return.
    
	vector<SPerson> persons(n);

	for (int i = 0; i < n; i++)
	{
		getline(fin, persons[i].name);
		fin >> persons[i].age;
		fin.get();
		fout << persons[i].name << ", with age:" << persons[i].age << endl;
	}

	fin.close();
	fout.clear();
	fout.close();

	//===============================================================================================
	//Revised.
	//Using binary mode, we no longer need to write tedious fout<<XXX<<XXX<<endl, just fout.write()

	fout.open("output_bin.dat", ios_base::out | ios_base::binary);
	if (!fout.is_open())
	{
		cerr << "Can't open binary file..." << endl;
		exit(EXIT_FAILURE);
	}

	fout.write((char*) &persons, sizeof(persons)*persons.size());
	fout.clear();
	fout.close();
	//==============================================================================================
	//Using fin to read binary file.

	fin.open("output_bin.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		cerr << "Can't open binary file..." << endl;
		exit(EXIT_FAILURE);
	}

	fin.read((char*)&persons, sizeof(persons)*persons.size());
	fin.clear();
	fin.close();

	for (int i = 0; i < n; i++)
	{
		cout << persons[i].name << ", with age:" << persons[i].age << endl;
	}
	system("pause");
	return 0;
}

