#include "stdafx.h"
#ifndef RATED_PLAYER_H_
#define RATED_PLAYER_H_
#include "TableTennisPlayer.h"

/*
第一:private,public,protected的访问范围:

private: 只能由该类中的函数、其友元函数访问,不能被任何其他访问，该类的对象也不能访问.
protected: 可以被该类中的函数、子类的函数、以及其友元函数访问,但不能被该类的对象访问
public: 可以被该类中的函数、子类的函数、其友元函数访问,也可以由该类的对象访问
注：友元函数包括两种：设为友元的全局函数，设为友元类中的成员函数

第二:类的继承后方法属性变化:

使用private继承,父类的所有方法在子类中变为private;
使用protected继承,父类的protected和public方法在子类中变为protected,private方法不变;
使用public继承,父类中的方法属性不发生改变;
*/
class RatedPlayer :public TableTennisPlayer  //extend!!!!!!! in C++, USING : to represent extend.
{
private:
	unsigned int rating;
public:
	RatedPlayer( unsigned int r = 0, const string& fn = "none", const string& ln = "none", bool ht = false );
	RatedPlayer( unsigned int r, const TableTennisPlayer& tp );
	unsigned int Rating() const
	{
		return rating;
	}

	void ResetRating(unsigned int r)
	{
		rating = r;
	}


	void printTest() const
	{
		cout << "This is print test of extended class." << endl;
	}

	virtual void v_printTest() const  //virtual function.
	{
		cout << "This is VIRTUAL print test of extended class." << endl;
	}
};

#endif