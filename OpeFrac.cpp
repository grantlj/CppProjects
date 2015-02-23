/*==============================================================
Author:Grant Liu
Data:  2013-09-16-22.21
  =============================================================*/
#include <iostream>
using namespace std;
class Swaper
{
    private:
     int tmp;
    public:
     int a,b;
     int GetA(int a,int b)
     {
         a=this->a;b=this->b;
         tmp=a;a=b;b=tmp;
         return a;
     }
     int ReturnShit(void);
} Calcer;

int Swaper::ReturnShit(void)
{
    return 111111;
}

int main()
{
    cin>>Calcer.a>>Calcer.b;
   // cout<<Calcer.tmp;
    cout<<Calcer.GetA(Calcer.a,Calcer.b)<<endl;
    cout<<Calcer.ReturnShit();
    return 0;
}
