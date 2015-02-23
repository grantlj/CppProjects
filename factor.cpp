#include <iostream>
using namespace std;

bool isok(int n,int i)
{
    bool flag=true;
    for (int j=2;j<=i-1;j++)
    if (i%j==0)
    {
        flag=false;
        break;
    }
    if (flag & (n%i==0))
        return true;
    else
        return false;

}
int main()
{
  int n,fac[100],sum;
  cin>>n;
  sum=0;
  bool flag=true;
  do
  {
    for (int i=2;i<=n;i++)
    {
        if (isok(n,i))
        {
           n=n/i;
           fac[sum]=i;
           sum++;
           break;
        }
    }
  }
  while (n!=1);
  for (int i=0;i<=sum-1;i++)
    cout<<fac[i]<<' ';
  cout<<endl;
  return 0;
}
