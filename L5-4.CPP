#include <stdio.h>
#define MAX 100000
int main()
{
    int i;
    float x,sum,aver;
    sum=0;
    for(i=1;i<=1000;i++)
    {
        scanf("%f",&x);
        sum+=x;
        if (sum>=MAX) break;
    }
    aver=sum/i;
    printf("Num=%d\n",i);
    printf("Average=%10.2f\n",aver);
    return 0;
}
