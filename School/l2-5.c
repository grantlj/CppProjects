/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.25
 =============================================================*/
#include <stdio.h>
int countdigit(int num,int dig)
{
    int t,s=0;
    do
    {
        t=num%10;
        if (t==dig) s++;
        num/=10;
    }
    while (num!=0);
    return s;
}
int main()
{
    int x;
    scanf("%d",&x);
    printf("%d\n",countdigit(x,2));
}
