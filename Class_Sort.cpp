/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-01-10.20
 =============================================================*/
#include <iostream>
using namespace std;

class TSORT
{
  private:
      int n;
      int a[100];

      void SwapVal(int i,int j)
      {
         int t;
         t=this->a[i];this->a[i]=this->a[j];this->a[j]=t;
      }
  public:
      void SetN(int x)
        {
            this->n=x;
            for (int i=0;i<=99;i++)
              a[i]=0;
        }
      void SetVal(int i,int val)
         {
             this->a[i]=val;
         }
      void PrintVal(void)
        {
            for (int i=0;i<=this->n-1;i++)
                cout<<this->a[i]<<' ';
            cout<<endl;
        }
      void Sort()
        {
            for (int i=0;i<=n-2;i++)
                for (int j=i+1;j<=n-1;j++)
                  if (this->a[i]<this->a[j]) SwapVal(i,j);

        }
};

TSORT C1;

int main()
{
    int n,t;
    cin>>n;
    C1.SetN(n);
    for (int i=0;i<=n-1;i++)
    {
        cin>>t;
        C1.SetVal(i,t);
    }
   // C1.PrintVal();
    C1.Sort();
    C1.PrintVal();
    return 0;
}
