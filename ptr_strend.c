/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-23-13.52
 =============================================================*/
#include <stdio.h>
int ptr_strend(char *s,char *t)
{
    int ls=strlen(s)-1;
    int lt=strlen(t)-1;
    int i;

    for (i=lt;(s[ls-(lt-i)]==t[i] && i>=0 && ls-(lt-i)>=0);i--);
    if (i==-1)
       return 1;
    else
       return 0;
}
int main()
{
    char s[255];
    char t[255];
    scanf("%s",s);
    scanf("%s",t);
    printf("%d",ptr_strend(s,t));
    return 0;
}
