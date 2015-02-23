/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-14.53
 =============================================================*/
#include <stdio.h>


int fn(int a,int n)
{
  int i,t=0;
  for (i=1;i<=n;i++)
    t=t*10+a;
  return t;
}
int main()
{
    int a,n;
    scanf("%d,%d",&a,&n);
    int sum=0,i;
    for (i=1;i<=n;i++)
        sum+=fn(a,i);
    printf("%d",sum);
    return 0;
}
