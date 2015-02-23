/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-21.44
 =============================================================*/
#include <stdio.h>
int main()
{
    int n,i,a[100];
    scanf("%d",&n);
    for (i=0;i<n;i++)
        scanf("%d",&a[i]);
    int p=0,t;
    for (i=0;i<n;i++)
        if (a[i]<a[p])
              p=i;
    t=a[p];a[p]=a[0];a[0]=t;
    p=n-1;
    for (i=0;i<n;i++)
        if (a[i]>a[n-1])
          p=i;
    t=a[p];a[p]=a[n-1];a[n-1]=t;
    printf("Ans:");
    for (i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}
