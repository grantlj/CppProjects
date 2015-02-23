/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-22-22.03
 =============================================================*/
#include <stdio.h>
typedef struct
{
   char name[20];
   struct
    {
     int year;
     int moth;
     int day;
    }date;
   struct
     {
      int hour;
      int minute;
     }time;
} TVisitor;

void DoClear(TVisitor* t)
{
  //(t).name="";
  (*t).date.year=0;(*t).date.moth=0;(*t).date.day=0;
  (*t).time.hour=0;(*t).time.minute=0;
}
int main()
{
    TVisitor info[100];
    printf("Enter visitor counts:");
    int n,i;
    FILE* fp;

    fp=fopen("a.txt","w");
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        DoClear(info+i);
        printf("Visitor NO.%d Name   ",i+1);
        scanf("%s",info[i].name);
        printf("YYYY/MM/DD   ");
        scanf("%d/%d/%d",&info[i].date.year,&info[i].date.moth,&info[i].date.day);
        printf("hh:mm   ");
        scanf("%d:%d",&info[i].time.hour,&info[i].time.minute);

        fprintf(fp,"%s\n",info[i].name);
        fprintf(fp,"%d/%d/%d\n",info[i].date.year,info[i].date.moth,info[i].date.day);
        fprintf(fp,"%d:%d\n",info[i].time.hour,info[i].time.minute);
    }
    fclose(fp);


    fp=fopen("a.txt","r");
    TVisitor tmp;

   for (i=0;i<n;i++)
    {
        DoClear(&tmp);
        fscanf(fp,"%s\n",info[i].name);
        fscanf(fp,"%d/%d/%d\n",&info[i].date.year,&info[i].date.moth,&info[i].date.day);
        fscanf(fp,"%d:%d\n",&info[i].time.hour,&info[i].time.minute);
        printf("Name: %s\n",info[i].name);
        printf("Arrived Date: %d/%d/%d\n",info[i].date.year,info[i].date.moth,info[i].date.day);
        printf("Arrived Time: %d:%d\n",info[i].time.hour,info[i].time.minute);
    }
    fclose(fp);
    return 0;
}
