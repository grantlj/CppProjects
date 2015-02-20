#include "stdafx.h"
#include "mytime1.h"
#include <iostream>

Time::Time(int hours, int minutes)
{
	this->hours = hours;
	this->minutes = minutes;
}

Time::Time()
{
	hours = minutes = 0;
}

void Time::AddHr(int hours)
{
	this->hours += hours;
}

void Time::AddMin(int minutes)
{
	this->minutes += minutes;
}

void Time::Reset(int hours, int minutes)
{
	this->hours = hours;
	this->minutes = minutes;
}

Time Time::operator+(const Time& t) const
{
	Time sum;
	sum.minutes = minutes + t.minutes;
	sum.hours = hours + t.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}

void Time::Show() const
{
	using std::cout;
	using std::endl;
	cout << hours << " hours, " << minutes << " minutes." << endl;
}

//friend function.
std::ostream& operator<<(std::ostream& os, const Time& t)
{
	os << t.hours << " hours, " << t.minutes << " minutes." << std::endl;
	return os;
}