/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-28-13.25
 =============================================================*/
 /*
    ȫ�����ǲ��룡
    ����������=Դ��
    ����������=������ֵ����Դ��ȡ����+1
    OPERATIONS           COMMENTS
    =================================
    &: AND               ��Ϊ1 ��Ϊ1
    |: OR                ��һ��λ1 ����1
    ^: XOR               ��ͬλ�� ��ͬΪ��
    ~: NOT               ȫ��ȡ��
    <<:LEFT              �����ƶ�Nλ������2^n
    >>:RIGHT             �����ƶ�Nλ������2^n
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

