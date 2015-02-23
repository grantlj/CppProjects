// ch13_test1_extend_class.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "RatedPlayer.h"
#include "TableTennisPlayer.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	TableTennisPlayer player1("Tara", "Boomdea", false);
	RatedPlayer rplayer1(1140, "Mallory", "Duck", true);

	//protected variable test.
	

	/*
	===============================================
	 C++ base/extend class function using test.
	===============================================
	*/
	//Print test.
	cout << "Print test of base class:";
    player1.printTest();

	cout << endl;
	cout << "Print test of extend class:";
	rplayer1.printTest();

	//Print test of extend class using base function.
	cout << endl;
	cout << "Print test of extend class using base class func:";
	rplayer1.TableTennisPlayer::printTest();   //use TableTennisPlayer's print function.

	/*
	===============================================
	C++ base/extend class function using test.
	==================TEST END=====================
	===============================================
	*/



	/*
	===============================================
	C++ VIRTUAL FUNCTION TEST.
	===============================================
	*/

	//��̬���÷���
	TableTennisPlayer* pt = new TableTennisPlayer(player1);  //���ƹ��캯��;
	TableTennisPlayer* pr = new RatedPlayer(rplayer1);   //��̬�ˣ���������

	cout << endl << endl;
	cout << "First we use NON-VIRTUAL FUNCTION:" << endl;
	cout << "pt:";
	pt->printTest();  //print tabletennis.
	cout << "pr:";
	pr->printTest();  //print tabletennis,  too.

	cout << endl << endl;
	cout << "Second we use VIRTUAL FUNCTION:" << endl;
	cout << "pt:";
	pt->v_printTest();  //print tabletennis.
	cout << "pr:";
	pr->v_printTest();  //print the EXACT class function: ratedplayer.


	/*
	===============================================
	C++ VIRTUAL FUNCTION TEST.
	==================TEST END=====================
	===============================================
	*/
	rplayer1.Name();

	if (rplayer1.HasTable())
	{
		cout << ": has a table" << endl;
	}
	else
		cout << ": has not a table." << endl;

	player1.Name();
	if (player1.HasTable())
	{
		cout << ": has a table" << endl;
    }

	else
		cout << ": has not a table." << endl;
	cout << "Name: ";
	rplayer1.Name();
	cout << "; Rating: " << rplayer1.Rating() << endl;

	RatedPlayer rplayer2(1212, player1);
	cout << " Name: ";
	rplayer2.Name();
	cout << "; Rating: " << rplayer2.Rating() << endl;
	
	

	system("pause");
	return 0;
}

