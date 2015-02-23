/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.19
 =============================================================*/
#include <stdio.h>
int prime(int x)
{
    int i;
    int flag=1;
    if (x==1) return 0;
    for (i=2;i<=sqrt(x);i++)
        if (x%i==0)
        {
            flag=0;
            break;
        }
    return flag;
}
int main()
{
    int m,n;
    scanf("%d,%d",&m,&n);
    int i,s=0,total=0;
    for (i=m;i<=n;i++)
    {
      if (prime(i)==1)
        {
          //printf("%d ",i);
          total++;
          s+=i;
        }

    }
     printf("total=%d\n",total);
     printf("sum=%d\n",s);
}
