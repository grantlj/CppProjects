// Ex1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char str[100][255];
	char(*p)[255];
	p = str;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", *p);
		p++;
	}
    
	for (p = str; p < str + n; p++)
	{
		system("pause");
		printf("%s", *p);
	}
	return 0;
}

