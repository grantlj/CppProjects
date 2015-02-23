#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    char ch;
    string ans;
    cin>>ch;
    switch(ch)
    {
        case 'A':ans="85-100";break;
        case 'B':ans="70-84";break;
        case 'C':ans="60-69";break;
        case 'D':ans="<60";break;
        default:ans="DATA ERROR!";
    }
    cout<<ans;
    return 0;

}
