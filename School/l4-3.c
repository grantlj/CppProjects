/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-16-11.59
 =============================================================*/
 #include <stdio.h>
 int a[5][5];

 int GetSum1(int** p,int line)
 {
     int s=0;
     int i;
     for (i=1;i<=line;i++)
     {
         //s=s+(*p);
         //printf("val=%d\n",*p);
         s=s+(*p);
         p+=(line+1);
     }
     return s;
 }
 int main()
 {
     int i,j;
     for (i=0;i<5;i++)
        for (j=0;j<5;j++)
           scanf("%d",&a[i][j]);
     int s1=0,s2=0;
     int** p=&a[0][0];
     s1=GetSum1(p,5);
     printf("%d",s1);
     return 0;
 }
