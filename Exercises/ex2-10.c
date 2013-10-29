/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-29-19.29

The C Programming Language Exercise 2-10:
Rewrite the lower() function with a conditional expression.
 =============================================================*/
#include <stdio.h>

void lower(char *s)
{
    int i;
    for (i=0;i<strlen(s);i++)
        s[i]=(s[i]>='A' && s[i]<='Z')?(s[i]+32):s[i];
}
int main()
{
    char s[255];
    gets(s);
    lower(s);
    puts(s);
    return 0;
}
