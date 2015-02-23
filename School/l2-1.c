/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.06
 =============================================================*/
 #include <stdio.h>
 int sign(int x)
 {
     if (x>0)  return 1;
     if (x==0) return 0;
     if (x<0)  return -1;
 }
 int main()
 {
     int x;
     scanf("%d",&x);
     printf("%d",sign(x));
     return 0;
 }
