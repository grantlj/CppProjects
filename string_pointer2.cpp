#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
void doSort(char** p,int n)   //p is a pointer points to char array. so 2 * , one is to stirng, and one is to pointer to string.
{
    int i,j;
    char *tmp;
    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
          if (strcmp(*(p+i),*(p+j))>0)
    {
        tmp=*(p+j);
        *(p+j)=*(p+i);
        *(p+i)=tmp;
    }
}
int main()
{
  char *ptr[100];   //100 array,element is to char*.
  char s[100][20];
  int i,n;
  scanf("%d\n",&n);
  for (i=0;i<n;i++) //*p[i] is s[i][0]
  {
    cin>>s[i];
    ptr[i]=s[i];
   // cout<<"hi!"<<*ptr[i]<<endl;
  }
  printf("Sorted:\n");
  doSort(ptr,n);
  for (i=0;i<n;i++)
    cout<<ptr[i]<<endl;

}
