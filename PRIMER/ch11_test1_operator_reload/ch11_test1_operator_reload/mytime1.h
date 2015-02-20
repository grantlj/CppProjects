#ifndef MYTIME1_H_
#define MYTIME1_H_
#include "mytime1.h"
#include <iostream>
class Time{
private:
	int hours;
	int minutes;
public:
	Time();
	Time(int hours, int minutes = 0);
	void AddMin(int minutes);
	void AddHr(int hours);
	void Reset(int hours = 0, int minutes = 0);
	Time operator+(const Time& t) const;          //operator op form, const means this function CAN'T CHANGE internal variables.
	void Show() const;
	friend std::ostream& operator<<(std::ostream& os, const Time& t);
};

#endif