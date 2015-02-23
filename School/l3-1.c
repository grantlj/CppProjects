/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-19.11
 =============================================================*/
#include <stdio.h>
int main()
{
    int a[100],n;
    scanf("%d",&n);
    int i;
    float s;
    for (i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        s+=a[i];
    }
    printf("Ave=%4.2f\n",s/n);
    return 0;
}
