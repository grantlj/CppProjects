#include <iostream>
using namespace std;
int main()
{
    int year;
    bool ans;
    ans=true;
    cin>>year;
    if (year%4!=0) ans=false;
    else
        if (year%100==0 && year%400!=0) ans=false;
    cout<<"Year "<<year<<" is "<<ans<<endl;
    return 0;
}
