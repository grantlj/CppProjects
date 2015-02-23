#include <stdio.h>
int main()
{
    int a[2][3]={{1,2,3},{4,5,6}};
    int b[3][2]={0};
    int i,j;
    for (i=0;i<=2;i++)
        for (j=0;j<=1;j++)
           b[i][j]=a[j][i];
    for (i=0;i<=2;i++)
    {
        for (j=0;j<=1;j++)
            printf("%d\t",b[i][j]);
        printf("\n");
    }

}
