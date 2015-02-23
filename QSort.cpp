/*==============================================================
Author:Grant Liu
Data:  2013-09-07-21.36
Project Name: QSort;
STEPS:
     1.set value i,j(i is head;j is end)
     2.set key=nums[0];
     3.from j to head find a[j]<Key,swap;
     4.from i to end find a[i]>key,swap;
     repeat setp 3,4,5; until i=j?
  =============================================================*/
#include <iostream>
using namespace std;
int nums[100];

void QSort(int a,int b)
{
    int i=a,j=b,x=nums[i],t;
    while (i!=j)
    {
        while ((nums[j]>=x) && (j>i))
            j--;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

       while ((nums[i]<=x) && (j>i))
            i++;
        if (j>i)
        {
            t=nums[i];
            nums[i]=nums[j];
            nums[j]=t;
        }

    }
    nums[i]=x;
    i++;j--;
    if (a<j) QSort(a,j);
    if (i<b) QSort(i,b);

}
int main()
{
    int n;
    cin>>n;
    for (int i=0;i<=n-1;i++)
      cin>>nums[i];
    QSort(0,n-1);
    cout<<"Result:"<<endl;
    for (int i=0;i<=n-1;i++)
        cout<<nums[i]<<endl;
    return 0;
}
