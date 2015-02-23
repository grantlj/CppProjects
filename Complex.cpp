/*==============================================================
Author : Grant Liu
Contact: 393444163@qq.com
Data   : 2013-10-01-10.43
 =============================================================*/
//Use Class to calcute two complex number.
#include <iostream>
using namespace std;

class TComplex
{
   public:
     int Real,Imag;
     void SetVal(int Real,int Imag);
     void Adder(TComplex A,TComplex B);
     void Minus(TComplex A,TComplex B);
     void Print(void);
     TComplex(int a,int b)
     {
         Real=a;
         Imag=b;
     }

     ~TComplex(void)
     {
         cout<<"Bull shit!"<<endl;
     }
     TComplex operator++()
     {
         this->Real++;
         this->Imag++;
         return *this;
     }

};
void TComplex::SetVal(int Real,int Imag)
{
    this->Real=Real;this->Imag=Imag;
}
void TComplex::Print(void)
{
    cout<<"Real is:"<<this->Real<<endl;
    cout<<"Imag is:"<<this->Imag<<endl;
}

void TComplex::Adder(TComplex A,TComplex B)
{
    this->SetVal(A.Real+B.Real,A.Imag+B.Imag);
}

void TComplex::Minus(TComplex A,TComplex B)
{
    this->SetVal(A.Real-B.Real,A.Imag-B.Imag);
}

int main()
{
    //Creator!!!!
    //The first form.
    TComplex C1(1,2),C3(0,0);
    //The second form.
    TComplex C2=TComplex(3,4);
    int a,b;

   // cin>>a>>b;
   // C1.SetVal(a,b);
   // C1(a,b);
    //cin>>a>>b;
    //C2.SetVal(a,b);
   // C2(a,b);
    ++C2;
    C2.Print();

    cout<<"AddValue:"<<endl;
    C3.Adder(C1,C2);
    C3.Print();

    cout<<"MinusValue:"<<endl;
    C3.Minus(C1,C2);
    C3.Print();
    return 0;
}
