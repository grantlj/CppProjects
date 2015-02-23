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
char t[255];
char* lower(char s[])
{
    int i;
    for (i=0;i<strlen(s);i++)
        t[i]=(s[i]>='A' && s[i]<='Z')?(s[i]+32):s[i];
    return t;
}
int main()
{
    char s[255];
    char *t;
    gets(s);
    t=lower(s);
    printf("%s\n",t);
    return 0;
}
