#include <stdio.h>
int ans;
int max(int a,int b,int c)
{
    int z=-1000;
    if(a>z)z=a;
    if(b>z)z=b;
    if(c>z)z=c;
    return z;
}
int main()
{
    int a,b,c;
    scanf("%d,%d,%d",&a,&b,&c);
    ans=max(a,b,c);
    printf("Max=%d",ans);
    return 0;

}
