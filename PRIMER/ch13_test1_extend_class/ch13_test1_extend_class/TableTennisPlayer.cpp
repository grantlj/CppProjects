#include "stdafx.h"
#include "TableTennisPlayer.h"


TableTennisPlayer::TableTennisPlayer(const string& fn, const string& ln, bool ht)
{
	firstname = fn;
	lastname = ln;
	hasTable = ht;
}

void TableTennisPlayer::Name() const
{
	cout << lastname << ", " << firstname;
}