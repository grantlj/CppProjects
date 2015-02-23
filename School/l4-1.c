/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-22.35
 =============================================================*/
#include <stdio.h>
#include <string.h>
int isok(char *ptr)
{
    int flag=1;
    int i,j;
    for (i=0,j=strlen(ptr)-1;i++,j--;i<j)
        if (ptr[i]!=ptr[j]) flag=0;
    return flag;
}
int main()
{
    char str[100];
    gets(str);
    if (isok(str)==1)
        printf("%s is a palindrome\n",str);
    else
        printf("%s is not a palindrome\n",str);
    return 0;
}
