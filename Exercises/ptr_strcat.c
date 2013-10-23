/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-23-13.46
 =============================================================*/
#include <stdio.h>

void ptr_strcat(char *s,char *t)
{
    while (*s!='\0')
    {
        s++;
    }
    for (;*t!='\0';s++,t++)
        *s=*t;
    *s='\0';
}

int main()
{
    char s[255];
    char t[255];
    scanf("%s",s);
    scanf("%s",t);
    ptr_strcat(s,t);
    printf("%s",s);
    return 0;
}
