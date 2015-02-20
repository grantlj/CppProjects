// ch10_test1_class1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stock.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	cout << " Using constructors to create new objects:" << endl;
	Stock stock1=Stock("NanoSmart", 12, 20.0);   //by constrcutor 2.
	stock1.show();
	
	Stock stock2=Stock("Boffo Objects", 2, 2.0);
	stock2.show();

	cout << "Assigning stock1 to 2:" << endl;
	stock2 = stock1;
	cout << "Listing s1 and s2:" << endl;
	stock1.show();
	stock2.show();

	cout << "Using a constructor ot reset an object.";
	stock1 = Stock("Nifty Foods", 10, 50.0);
	cout << "Revised stock1:" << endl;
	stock1.show();
	
	cout << endl << "Done!" << endl;

	stock1.~Stock();
	stock2.~Stock();

	system("pause");
	return 0;
}

