#ifndef STOCK_H_
#define STOCK_H_

#include <iostream>
#include <string>
using namespace std;
class Stock
{
private:
	string company;
	long shares;
	double share_val;
	double total_val;
	void set_tot();
public:
	Stock();
	Stock(const string& co, long n = 0, double pr = 0.0);  //default argument and reference
	~Stock();                                              //destructor.
	void buy(long num, double price);
	void sell(long num, double price);
	void update(double price);
	void show();
};

#endif