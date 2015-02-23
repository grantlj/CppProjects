/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-23-21.25
 =============================================================*/
#include "stdio.h"
#define MAXLINE 100;
int getline(char s[],int lim)
{
    int c,i;
    for (i=0;i<=lim-1  &&  (c=getchar())!=EOF && c!='\n';i++)
          s[i]=c;
    if (c=='\n')
       {
           s[i++]=c;
       }
    s[i]='\0';
    return i;
}

void copy(char to[],char from[])
{
    int i=0;
    while ((to[i]=from[i])!='\0')
        i++;

}

int main()
{
    int len,ans;
    ans=-1;
    char Cur[100];
    char Lon[100];
    while ((len = getline(Cur,MAXLINE)) >0 )
     {
         if (len>ans){
            ans=len;
            copy(Lon,Cur);
         }
     }
    if (ans>0) printf("%s",Lon);
    return 0;
}
