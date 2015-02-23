/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-22.00
 =============================================================*/
#include <stdio.h>
#include <windows.h>
int nums[100],n;
void QSort(int a,int b)
{
    int i=a,j=b,x=nums[i],t;
    while (i!=j)
    {
        while ((nums[j]<=x) && (j>i))
            j--;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

       while ((nums[i]>=x) && (j>i))
            i++;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

    }
    nums[i]=x;
    i++;j--;
    if (a<j) QSort(a,j);
    if (i<b) QSort(i,b);

}
int main()
{
    int i;
    scanf("%d",&n);
    for (i=0;i<n;i++)
        scanf("%d",&nums[i]);
    QSort(0,n-1);
    for (i=0;i<n;i++)
        printf("%d ",nums[i]);
    return 0;
}
