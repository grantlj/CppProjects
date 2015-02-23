#include "stdafx.h"
#include "RatedPlayer.h"
#include <iostream>
using namespace std;

RatedPlayer::RatedPlayer(unsigned int r, const string& fn, const string& ln, bool ht) :TableTennisPlayer(fn, ln, ht)
//In this constructor, we are not allowed to directly control PRIVATE variables in TTP class.
//In C++ , by using : TableTennisPlayer(fn, ln, ht), we can extent the TTP constructor to give values to those variables.
{
	rating = r;
}

//: TableTennisPlayer and rating are initializing operation.
//If we do not use it, the function will automaticlly calling the default constructor of TableTennisPlayer
RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer& tp) :TableTennisPlayer(tp), rating(r)  
{

}