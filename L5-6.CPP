#include <stdio.h>
int main()
{
    int i,j,d;
    for (i=1;i<=4;i++)
    {
        d=i;
        for (j=1;j<=5;j++)
            printf("%d\t",i+(j-1)*d);
        printf("\n");
    }
}
