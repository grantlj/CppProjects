
#include <string.h>
#include <iostream>
using namespace std;
int main()
{
    int n,i,j;
    char str[100][20];
    char tmp[20];
    cin>>n;
    for (i=0;i<n;i++)
        cin>>str[i];

    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
          if (strcmp(str[i],str[j])>0)
    {
       strcpy(tmp,str[i]);
       strcpy(str[i],str[j]);
       strcpy(str[j],tmp);
    }

    for (i=0;i<n;i++)
        cout<<str[i]<<endl;

    return 0;
}
