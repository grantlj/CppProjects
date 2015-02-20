// ch4_test8_pointer2.cpp : c++ pointer usage with new.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    int* nums = new int[100];                  //first we dynamically new a ram block. and return its head addr to 
	                                           //a pointer num.
	for (int i = 0; i < 99; i++)
	{ 
		//nums[i] = 2 * i + 1;                  //pointer can be used in this way.
		*(nums + i) = 2 * i + 1;
		cout << nums[i] << endl;
	}
	
	//delete(nums); //this is WRONG.
	
	//we should delete all variables.
	delete[]nums;
	system("pause");
	return 0;
}

