/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-23-15.19
 =============================================================*/
#include <stdio.h>
int main()
{
    int a[100],i,n,j,t;
    int nowa=-1,nowaC=0,ans=-1,ansC=-1;
    scanf("%d",&n);

    for (i=0;i<n;i++)
        scanf("%d",a+i);

    for (i=0;i<n-2;i++)
        for (j=i+1;j<n-1;j++)
           if (a[i]<a[j])
    {
        t=a[i];a[i]=a[j];a[j]=t;
    }
    for (i=0;i<n;i++)
    {
       if (a[i]==nowa)
            nowaC++;
       else
       {
           if (nowaC>ansC)
             {
               ans=nowa;
               ansC=nowaC;
             }
           nowaC=1;
           nowa=a[i];
       }
    }
    if (ansC!=-1)
        printf("MaxNumber=%d  Counts=%d\n",ans,ansC);
    else
        printf("Not found.\n");
    return 0;
}
