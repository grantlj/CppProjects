/*==============================================================
Author:Grant Liu
Data:  2013-09-07-22.07
Project:String Operation Exercises!!
  =============================================================*/
#include <iostream>

#include <string>
using namespace std;
int main()
{
   /*
    string str1,str2;

    cout<<"Input Str1:";
    cin>>str1;
    cout<<endl;
    cout<<"Input Str2:";
    cin>>str2;
    cout<<endl;

    //Give Length;
    //string.length()
    cout<<"Str1 Length:"<<str1.length()<<endl;
    cout<<"Str2 Length:"<<str2.length()<<endl;

    //Change Value;
    str1[0]='L';  //If is Li then only change str1[0] with i;
    cout<<"Str1 Value Changed:"<<str1<<endl;

    /*
    //Copy!
    str2=str1.substr(2,3);
    cout<<"Str2 copys from str1's 2 and copy 3 characters!"<<str2<<endl;
    */


    //Find!!!
    //1.Find from start!
    //2.Find from some place!
    //3.Find from end!

    /*
    int where1,where2,where3;
    where1=str1.find(str2);
    where2=str1.find(str2,3);
    where3=str1.rfind(str2);
    cout<<"Str2 in Str1:"<<where1<<endl;
    cout<<"Str2 in Str1 AFTER 3:"<<where2<<endl;
    cout<<"Str2 in Str1 BACKWARD!:"<<where3<<endl;

    //Insert!!!!
    //1.Insert from sp!
    //2.Insert many times!
    str1.insert(3,str2);
    cout<<"Standart Insert str2 into str1:"<<str1<<endl;

    str1.insert(3,5,'a'); //Only can be characters!!!!!!!!!!!!!!!!!
    cout<<"Insert 'a' 5 times from 3:"<<str1<<endl;

    */

    //Replace!
    string str1="String handling C++ style.";
    string str2="STL Power";
    //str1.replace(7, 8, str2);
    //Erase!!!
    str1.erase(0,7);
    cout<<"Erase:"<<str1<<endl;





    return 0;
}
