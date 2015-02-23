/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.30
 =============================================================*/
#include <stdio.h>
int countdigit(int num)
{
    int t,s=0;
    do
    {
        t=num%10;
        s+=t*t*t;
        num/=10;
    }
    while (num!=0);
    return s;
}
int main()
{
    int m,n,i;
    scanf("%d,%d",&m,&n);
    for (i=m;i<=n;i++)
      if (i==countdigit(i)) printf("%d ",i);

}
