
#include "stdafx.h"
#include <cstring>
#include "string1.h"

//static define.
int String::num_strings = 0;

int String::HowMany()
{
	return num_strings;
}

//class method.
//Constructor.

String::String(const char* s)
{
	len = std::strlen(s);
	char* str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;
}

String::String()
{
	len = 4;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

String::String(const String& st)
{
	num_strings++;
	len = st.len;
	str = new char[len];
	std::strcpy(str, st.str);
}

String::~String()
{
	num_strings--;
	delete[] str;  //Destructor!! We must destroy as soon as possible.
}

String& String::operator=(const String& st)
{
	if (this == &st)
		return *this;
	delete[] str;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
	return *this;
}

String& String::operator=(const char* s)
{
	delete[] str;
	len = std::strlen(s);
	str = new char[len + 1];
    std::strcpy(str, s);
	return *this;
}

//read write char for none cosnt string.
char& String::operator[](int i)
{
	return str[i];
}

//read only char for const string.
const char& String::operator[](int i) const
{
	return str[i];
}

bool operator<(const String& st1, const String& st2)
{
	return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String& st1, const String& st2)
{
	return st2<st1;
}

bool operator==(const String& st1, const String& st2)
{
	return (std::strcmp(st1.str, st2.str) == 0);
}

ostream& operator<<(ostream& os, const String& st)
{
	os << st.str;
	return os;
}

istream& operator>>(istream& is, String& st)
{
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is)
		st = temp;
	while (is&& is.get() != '\n')
		continue;
	return is;
}