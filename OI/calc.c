/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-29-10.33
 =============================================================*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct TPoint
 {
     int isval;
     int val;
     char op;
     struct TPoint *LChild;
     struct TPoint *RChild;
     struct TPoint *Par;
 };


struct TPoint* InitialPoint()
{
    struct TPoint* p;
    p=(struct TPoint*)malloc(sizeof(struct TPoint));
    return p;
}

struct TPoint* SetupBT(char *str,int k,struct TPoint* Par)
{
    if (str[k]=='(') return SetupBT(str,k+1,Par);
    if (str[k]==')') return SetupBT(str,k+2,Par->Par->Par);

    if (str[k]=='+' || str[k]=='-' || str[k]=='*' || str[k]=='/')
    {
        printf("hi!!!! %c\n",str[k]);
        struct TPoint* p=InitialPoint();
        p->isval=0;
        p->op=str[k];
        p->LChild=Par;
        p->Par=NULL;
        p->RChild=SetupBT(str,k+1,p);

    }

    if (str[k]>='0' && str[k]<='9')
    {
        //it is number.
        int t_num=0;
        do
        {
            t_num=t_num*10+(str[k]-'0');
            k++;
        }
        while (str[k]>='0' && str[k]<='9');

        struct TPoint* p0=InitialPoint();
        p0->isval=1;
        p0->val=t_num;
        p0->LChild=NULL;
        p0->RChild=NULL;
        p0->Par=NULL;

        //an operator ALWAYS FOLLOW a number.
        if (str[k]=='+' || str[k]=='-' || str[k]=='*' || str[k]=='/')
          {
             struct TPoint* p=InitialPoint();
             p->isval=0;
             p->op=str[k];
             p->LChild=p0;
             p->Par=Par;
             p->RChild=SetupBT(str,k+1,p);

            //Maybe a ( or another number.
             return p;
          }
        else
             return p0;
    }
};

void PrintVals(struct TPoint *p)
{
    if (p->isval==0 && p->LChild!=NULL) PrintVals(p->LChild);
    if (p->isval==0 && p->RChild!=NULL) PrintVals(p->RChild);
    if (p->isval==1)
       printf("%d ",p->val);
    else
       if (p->op!=')') printf("%c ",p->op);

}

int main()
{
    struct TPoint* Root;
    Root=InitialPoint();
    char str[100];
    gets(str);

    Root=SetupBT(str,0,NULL);
    PrintVals(Root);
    return 0;
}
