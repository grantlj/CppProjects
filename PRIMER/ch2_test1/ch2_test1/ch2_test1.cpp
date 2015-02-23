// ch2_test1.cpp : basic cin cout experiment.
//

#include "stdafx.h"
#include <iostream>
//using namespace std;   //a lazy usage, it allows all functions in std namespace.
//it can also be:
using std::cout;
using std::cin;
using std::endl;
#include <Windows.h>
int _tmain(int argc, _TCHAR* argv[])
{   
	//using namespace can also be embraced in main() function.
	//using namespace std; 
	int carrots;
	cin >> carrots;

	cout << "hello world!" << carrots<<endl;
	system("pause");

	//cout always contine from the last line;
	cout << "hello";
	cout << " world";
	system("pause");
	return 0;
}

