// ch14_test1_class_template.cpp : 类模板,实现stack。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "stacktp.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Stack<string> st;
	st.push("abc");
	st.push("def");
	cout << st.isempty() << endl;
	string tmp;
	st.ppop(tmp);
	cout << tmp << endl;

	system("pause");
	return 0;
}

