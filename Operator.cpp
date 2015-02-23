/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-09-17-08.53
 =============================================================*/
 #include <iostream>
 using namespace std;
 class Adder
 {
  public:
    int a,b;
    int Operator+(int a,b)
    {
        return a-b;
    };
 }
int main()
{
    Adder My1;
    My1.a=100;
    My1.b=200;
    cout<<My1.+(My1.a,My1.b)<<endl;
    return 0;
}


