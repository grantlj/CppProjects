/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-29-19.10

The C Programming Language Exercise 2-2:
Rewrite the getline() function without && or ||.
 =============================================================*/
#define lim 255
#include <stdio.h>
int counts=0;

int valid(char c)
{
    if (c=='\n') return 0;
        else if (c==EOF) return 0;
    else
    if (counts<lim)
        return 1;
}

int main()
{
    char s[lim]="";
    char c;
    c=getchar();

    while (valid(c)==1)
    {
      s[counts++]=c;
      c=getchar();
    }
    printf("%s",s);
    return 0;
}
