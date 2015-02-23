/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-28-13.25
 =============================================================*/
 /*
    全部都是补码！
    正数：补码=源码
    负数：补码=（绝对值）的源码取反后+1
    OPERATIONS           COMMENTS
    =================================
    &: AND               均为1 才为1
    |: OR                有一个位1 就是1
    ^: XOR               不同位真 相同为假
    ~: NOT               全部取反
    <<:LEFT              向左移动N位，乘以2^n
    >>:RIGHT             向右移动N位，除以2^n
*/
#include <stdio.h>
int main()
{
    int x1,x2;
    scanf("%d,%d",&x1,&x2);
    printf("AND:%d\n",x1 & x2);
    printf("OR:%d\n",x1 | x2);
    printf("XOR:%d\n",x1 ^ x2);
    printf("NOT x1:%d\n",~x1);
    printf("LEFT x1:%d\n",x1<<4);
    printf("RIGHT x2:%d\n",x2>>4);
    //printf("%d\n",x);

    return 0;
}

