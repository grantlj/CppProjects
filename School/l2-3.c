/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-15-15.13
 =============================================================*/
#include <stdio.h>
#include <math.h>

struct TPoint
{
    int x,y;
};

struct TPoint p1,p2;

double dist(struct TPoint p1,struct TPoint p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
int main()
{
    scanf("%d %d",&p1.x,&p1.y);
    scanf("%d %d",&p2.x,&p2.y);
    printf("%5.2f\n",dist(p1,p2));

    return 0;
}
