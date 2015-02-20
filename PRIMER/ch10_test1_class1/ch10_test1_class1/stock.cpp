#include "stdafx.h"
#include "stock.h"

void Stock::set_tot()
{
	total_val = shares * share_val;
}

//Constructor.
Stock::Stock(const string& co, long n, double pr)
{
	cout << "constrcutor 2!!!" << endl;
	company = co;
	if (n < 0)
	{
		cout << "Number of shaers can'tbe negative;"
			<< company << " shares set to 0." << endl;
		shares = 0;
	}
	else
		shares = n;
	share_val = pr;
	set_tot();

}

//Default Constrcutor.
Stock::Stock()
{
	cout << "Default constrctor!!" << endl;
	company = " no name";
	shares = 0;
	share_val = 0.0;
	total_val = 0.0;
}

void Stock::buy(long num, double price)
{
	if (num < 0)
	{
		cout << "Number of shares purchased can't be negative."
			<< " Transaction is aborted." << endl;

	}

	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}

void Stock::sell(long num, double price)
{
	using std::cout;
	if (num < 0)
	{
		cout << "Number of shares sold can't be negative. "
			<< " Transaction is aborted." << endl;
	}
	else if (num>shares)
	{
		cout << "You are not allowed to sell more than you have."
			<< " Transaction is aborted." << endl;
	}

	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void Stock::update(double price)
{
	share_val = price;
	set_tot();
}

void Stock::show()
{
	ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
	streamsize prec = cout.precision(3);
	cout << "Company: " << company
		<< "Shares: " << shares << '\n';
	cout << "Share Price: $" << share_val;

	cout.precision(2);
	cout << " Total Worth: $" << total_val << "\n";

	cout.setf(orig, ios_base::floatfield);
	cout.precision(prec);
}

Stock::~Stock()
{
	cout << "Destructor!" << endl;
}