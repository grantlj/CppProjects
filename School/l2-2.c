/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.09
 =============================================================*/
#include <stdio.h>
int even(int x)
{
    if (x%2==0) return 1;
    if (x%2==1) return 0;
}
int main()
{
    int s=0;
    int x;
    do
    {
        scanf("%d",&x);
        if (even(x)==0) s+=x;
    }
    while (x>0);
    printf("%d",s);
    return 0;
}
