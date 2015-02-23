/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-28-14.59
 =============================================================*/
#include <stdio.h>
int a[100];
void sortarr(int n,int a[])
{
    int i,j,t;
    for (i=0;i<=n-2;i++)
        for (j=i+1;j<=n-1;j++)
         if  (a[i]>a[j]) {t=a[i],a[i]=a[j],a[j]=t;}
}

int BSearch(int head,int tail,int x)
{
    int p;
    p=(head+tail)/2;
    if (head=tail && a[p]!=x) return -1;
    if (a[p]==x) return p;
    else if (a[p]>x)
            BSearch(head,p,x);
    else
            BSearch(p,tail,x);
}
int main()
{
    int n,i,x;
    scanf("%d",&n);
    for (i=0;i<=n-1;i++)
        scanf("%d",&a[i]);
    sortarr(n,a);
    printf("Sorted:\n");
    for (i=0;i<=n-1;i++)
        printf("%d\t",a[i]);
    printf("\n");
    scanf("%d",&x);
    printf("Search Result:");
    printf("%d\n",BSearch(0,n,x)+1);

return 0;
}
