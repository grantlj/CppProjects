#include <iostream>
using namespace std;
int main()
{
    bool check(int n);
    int n;
    cin>>n;
    for (int i=2;i<=n;i++)
    {
        if (check(i)) cout<<i<<endl;
    }
    return 0;
}
bool check(int n)
{
  bool f;
  f=true;
  for (int i=2;i<=n-1;i++)
     if (n%i==0)
     {
         f=false;
         break;
     }
  return f;
}
