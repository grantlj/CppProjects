/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-19.18
 =============================================================*/
 #include <stdio.h>
 int main()
 {
     int n,a[100],i,maxnum=-32767,maxp;
     scanf("%d",&n);
     for (i=0;i<n;i++)
       {
           scanf("%d",&a[i]);
           if (a[i]>maxnum)
           {
               maxnum=a[i];
               maxp=i;
           }
       }
     printf("max=%d at %d",maxnum,maxp);
     return 0;
 }
