#include <stdio.h>
#include <math.h>
int main()
{
    double ans,term;
    int i=1;
    term=1/(2*i-1);
    ans=0;
    ans=ans+term;
    while (fabs(term)>=1e-6)
    {
       i++;
       term=1/(2*i-1);
       if (i%2==1) ans=ans+term;
            else ans=ans-term;
    }
    ans=ans*4;
    printf("pi=%10.8f\n",ans);
    return 0;

}
