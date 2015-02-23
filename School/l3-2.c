/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-19.15
 =============================================================*/
#include <stdio.h>
int main()
{
    int n,i,a[100];
    scanf("%d",&n);
    for (i=0;i<n;i++)
        scanf("%d",&a[i]);
    for (i=n-1;i>=0;i--)
        printf("%d ",a[i]);
}
