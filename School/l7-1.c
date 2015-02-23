/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-22-21.30
 =============================================================*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char c;
    int Counts=0;
    char Buffer[1024]="";
    while ((c=getchar())!='!')
    {
        if (c>='a' && c<='z')
            c=c-'a'+'A';
        Buffer[Counts++]=c;
    }
    FILE *fp;
    fp=fopen("test.dat","w");
    fputs(Buffer,fp);
    fclose(fp);
    return 0;
}
