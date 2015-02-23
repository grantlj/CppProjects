#include "stdafx.h"
#ifndef TABLE_TENNIS_PLAYER_H_
#define TABLE_TENNIS_PLAYER_H_
#include <string>
#include <iostream>
using namespace std;

class TableTennisPlayer
{

protected:
	static const int PROTECTED_a = 255;     //Protected variable, extended class can operate directly.

private:
	string firstname;
	string lastname;
	bool hasTable;

public:
	TableTennisPlayer(const string& fn = "none", const string& ln = "none", bool ht = false);
	void Name() const;
	bool HasTable() const  //this const means, the function can only READ(BUT NOT MODIFY) those private variables.
	{
		return hasTable;
	}
	
	void printTest() const
	{
		cout << "This is print test of base class." << endl;
	}

	virtual void v_printTest() const
	{
		cout << "This is VIRTUAL print test of base class." << endl;
	}
};

#endif