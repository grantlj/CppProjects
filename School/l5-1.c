/*==============================================================
Author : Grant Liu(Liu Jiang)
StuID  : 2013210294
Class  : GJ011301
Contact: 393444163@qq.com
Date   : 2013-10-18-12.00
 =============================================================*/

#include <stdio.h>
void SortIt(char str[][255],int n)
{
    int i,j;
    for (i=0;i<n-2;i++)
        for (j=i+1;j<n-1;j++)
          if (strcmp(str[i],str[j])<0)
             {
                char t[255];
                strcpy(t,str[i]);
                strcpy(str[i],str[j]);
                strcpy(str[j],t);
             }
}
int main()
{
    int n,i;
    scanf("%d\n",&n);
    char str[n][255];
    for (i=0;i<n;i++)
         gets(str[i]);
    SortIt(str,n);
    printf("Sorted...\n");
    for (i=0;i<n;i++)
       printf("%s\n",str[i]);

    return 0;
}

