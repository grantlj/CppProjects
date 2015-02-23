/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-10-14.53
 =============================================================*/
#include <stdio.h>
#include <windows.h>
int main()
{
	int i;
	scanf("%d",&i);
	if(i==0)
		printf("off");
	else if(i==1)
		printf("on");
	else printf("Neither 1 and 0");
	system("pause");
	return 0;
}

