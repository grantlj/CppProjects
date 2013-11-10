/*
Author      :     Grant Liu
Organization:     CQUPT
Student   ID:     2013210294
E-Mail      :     393444163@qq.com

The C Programming Language Exercise 3-2:
Write the escape(s,t) function.
*/
#include <stdio.h>
void escape(char *s,char *t)
{
    int p=0;
    int i=-1;
    do
    {
       switch (*(t+p))
       {
         case '\t':
             s[++i]='\\';
             s[++i]='t';
             break;
         case '\n':
             s[++i]='\\';
             s[++i]='n';
             break;
         default:
            s[++i]=*(t+p);
        }

       p++;
    }
    while (*(t+p)!='\0');
    s[++i]='\0';
}
int main()
{
    char s[255],t[255];
    int p=0;
    char c;
    while ((c=getchar())!=EOF)
       t[p++]=c;
    escape(s,t);
    printf("%s\n",s);
    return 0;
}
