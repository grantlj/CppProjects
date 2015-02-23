#include <stdio.h>
#include <math.h>
#define PI 3.14
struct Tellipse
{
  struct Tpoint
   {
    int x;
    int y;
   }p1,p2;
   double a;
   double b;
} ellipse;

int main()
{
	scanf("%d,%d",&ellipse.p1.x,&ellipse.p1.y);
	scanf("%d,%d",&ellipse.p2.x,&ellipse.p2.y);
	ellipse.a=fabs(ellipse.p1.y-ellipse.p2.y)/2;
	ellipse.b=fabs(ellipse.p1.x-ellipse.p2.x)/2;
	printf("%5.2f",PI*ellipse.a*ellipse.b);
	return 0;
}
