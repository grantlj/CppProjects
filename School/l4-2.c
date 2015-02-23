/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-22.48
 =============================================================*/
#include <stdio.h>
int main()
{
    int n,i,a[100],x;
    scanf("%d",&n);
    for (i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("input x=");
    scanf("%d",&x);

    int flag=0,p;

    for (i=0;i<n;i++)
        if (a[i]==x)
         {
           flag=1;
           p=i;
           break;
         }
   if (flag==0) printf("x not found.\n");
   else
   {
       for (i=p+1;i<n;i++)
        a[i-1]=a[i];
       for (i=0;i<n-1;i++)
        printf("%d ",a[i]);
    }
}
