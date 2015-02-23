/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-21-20.17
 =============================================================*/
#include <stdio.h>
#include <math.h>
struct Client
{
    char number[12];
    double cost;
    double balance;
};
typedef struct Client cli;
cli a[10];

void Recharge(char num[12],int addval)
{
    int i;
    for (i=0;i<10;i++)
        if (strcmp(a[i].number,num))
          a[i].balance+=addval;
}

int main()
{

    int i;
    for (i=0;i<10;i++)
        {
          printf("input User %d's number,cost,balance:",i+1);
          scanf("%s %lf %lf",&a[i].number,&a[i].cost,&a[i].balance);
          if (a[i].number[11]==8)
            a[i].balance+=10;
         // printf("%s",a[i].number);
        }
    printf("Recharge....Input User's number & add value:");
    int x,addval;
    char num[12];
    scanf("%d %d",num,addval);
    Recharge(num,addval);
    for (i=0;i<10;i++)
      printf("%s,%d,%d\n",a[i].number,a[i].cost,a[i].balance);
    return 0;
}
