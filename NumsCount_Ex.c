/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-21-12.09
 =============================================================*/
#include <stdio.h>
int main()
{
    int nums[10];
    int other=0,c;
    for (int i=0;i<=9;i++)
      nums[i]=0;
    while ((c=getchar())!=EOF)
    {
        if (c>='0' && c<='9')
            nums[c-'0']++;
        else
            other++;
    }
    for (int i=0;i<=9;i++)
        printf("Num %d shows %d times\n",i,nums[i]);
    printf("Other Characters: %d\n",other);
    return 0;
}
