// ch17_test4_cin_get_geline.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;

const int Limit = 255;

int _tmain(int argc, _TCHAR* argv[])
{
	char input[Limit];
	cout << "Enter a string for getline() to processing" << endl;
	cin.getline(input, Limit, '#');   //using # as the line-end character
	cout << "Here is your input:" << endl;
	cout << input << "\nDone with phase 1\n";

	//use get to input a single char.
	char ch;
	cin.get(ch);

	cout << "The next input character is " << ch << endl;
	if (ch != '\n')
		cin.ignore(Limit, '\n');      //discard all the rest lines.
	
	cout << "Enter a string for get() processing:\n";
	cin.get(input, Limit, '#');  //using get to input a line, # is the line-end character.
	cout << "Here is your input" << endl;
	cout << input << "\nDone with phase 2\n";

	cin.get(ch);  //will get #, becuaes get will not discard the next character(line-end #) in the stream.
	cout << "The next input characher is " << ch << endl;
	
	system("pause");
	return 0;
}

