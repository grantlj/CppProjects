#include <stdio.h>
#include <math.h>
int main()
{
    float a,b,c,p,s;
    scanf("%f,%f,%f",&a,&b,&c);
    p=(a+b+c)/2;
    s=sqrt(p*(p-a)*(p-b)*(p-c));
    printf("a=%f\tb=%f\tc=%f\n",a,b,c);
    printf("Area=%f",s);
    return 0;
}
