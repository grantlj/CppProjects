/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-21-20.33
 =============================================================*/
#include <stdio.h>
int main()
{
    int i,j;
    for (i=32;i<=99;i++)
    {
        int x=i*i;
        int a[4];
        int t=0;
        do
        {
          a[t++]=x % 10;
          x/=10;
        }
        while (x!=0);
        if (a[0]==a[1] && a[2]==a[3]) printf("%d\n",i*i);
    }
    return 0;
}
