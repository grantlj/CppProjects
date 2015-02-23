/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-29-09.59
 =============================================================*/
 #include <stdio.h>
 struct TPoint
 {
     int val;
     struct TPoint *LChild;
     struct TPoint *RChild;
 };
 struct TPoint* Root;

 void Insert(int x,struct TPoint *p)
 {
     if (x<=p->val)
        if (p->LChild==NULL)
          {
             struct TPoint* now;
             now=(struct TPoint*)malloc(sizeof(struct TPoint));
             now->val=x;now->LChild=NULL;now->RChild=NULL;
             p->LChild=now;
          }
          else
            Insert(x,p->LChild);


    if (x>p->val)
        if (p->RChild==NULL)
          {
             struct TPoint* now;
             now=(struct TPoint*)malloc(sizeof(struct TPoint));
             now->val=x;now->LChild=NULL;now->RChild=NULL;
             p->RChild=now;
          }
          else
            Insert(x,p->RChild);

}

void PrintVals(struct TPoint *p)
{
    if (p->LChild!=NULL) PrintVals(p->LChild);
    printf("%d ",p->val);
    if (p->RChild!=NULL) PrintVals(p->RChild);

}
 int main()
 {
     Root=(struct TPoint*)malloc(sizeof(struct TPoint));
     Root->LChild=NULL;Root->RChild=NULL;
     int n,i;
     scanf("%d",&n);
     for (i=0;i<n;i++)
     {
        int t;
        scanf("%d",&t);
        if (i==0)
            Root->val=t;
        else
            Insert(t,Root);
     }
     PrintVals(Root);
     return 0;
 }

