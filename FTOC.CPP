/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-18-12.08
 =============================================================*/
#include "stdio.h";
int main()
{
    float ft,ct;
    for (int i=0;i<=300;i=i+20)
      {
        ft=i;ct=5*(ft-32)/9;
        printf("%3.0f\t%6.1f\n",ft,ct);
      }
     return 0;
}
