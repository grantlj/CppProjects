#include "stdafx.h"
#ifndef STRING1_H_
#define STRING1_H_
#include <iostream>
using std::ostream;
using std::istream;

class String
{
private:
	char* str;          //use pointer to point to a string.
	int len;
	static int num_strings;  //number of objects;
	
public:
	static const int CINLIM = 80; //input limit.
	String(const char* s);
	String();
	String(const String&);
	~String();
	int length() const{ return len; };

	//Operator overload.
	String& operator=(const String&);
	String& operator=(const char*);
	char& operator[](int i);
	const char& operator[](int i) const;

	//overload operator friend.
	friend bool operator<(const String& st, const String& st2);
	friend bool operator>(const String& st1, const String& st2);
	friend bool operator==(const String& st1, const String& st2);
	friend ostream& operator<<(ostream& os, const String& st);
	friend istream& operator>>(istream& is, String& st);

	//static function.
	static int HowMany();

};


#endif