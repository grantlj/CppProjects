#include "stdafx.h"
#ifndef TV_H_
#define TV_H_


//The TV class. TV's variables can be REMOTED BY REMOTE CLASS.
class Tv
{
private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;

public:
	friend class Remote;  //friend class Remote, can access TV private parts.
	enum{ Off, On };
	enum{MinVal, MaxVal=20};
	enum{Antenna, Cable};
	enum{ TV, DVD };

	Tv(int s = Off, int mc = 125) :state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input{ TV }{};

	void onoff()
	{
		state = (state == On) ? Off : On;
	}

	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode()
	{
		mode = (mode == Antenna )?Cable:Antenna;
	}

	void set_input()
	{
		input = (input == TV) ? DVD : TV;
	}

	void settings() const; //const function, cannot modify any value in the class.

};

class Remote
{
private:
	int mode;
public:
	Remote(int m = Tv::TV) :mode(m){}
	bool volup(Tv& t)   //其实这边用&，也没什么意思，就是为了减少内存开支，用个引用。
	{
		return t.volup();
	}
	
	bool voldown(Tv& t)
	{
		return t.voldown();
	}

	void onoff(Tv& t)
	{
		t.onoff();
	}

	void chanup(Tv& t)
	{
		t.chanup();
	}

	void chandown(Tv& t)
	{
		t.chandown();
	}

	void set_chan(Tv& t, int c)
	{
		t.channel = c;        //看见没，t.channel是private哦，但是因为在Tv类里申明了friend remote,所以在remote里面可以用他！
	}

	void set_mode(Tv& t)
	{
		t.set_mode();
	}

	void set_input(Tv& t)
	{
		t.set_input();
	}
};

#endif