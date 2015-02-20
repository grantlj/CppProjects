// ch15_test1_friend_class.cpp : friend class： 有权限访问本class的私有变量。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "tv.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Tv s42;
	cout << "Initial settings for 42-TV:" << endl;
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "Adjusted settings for 42-TV" << endl;
	s42.settings();

	Remote grey;
	grey.set_chan(s42, 10); grey.volup(s42);
	cout << "After remote:" << endl;
	s42.settings();

	system("pause");
	return 0;
}

