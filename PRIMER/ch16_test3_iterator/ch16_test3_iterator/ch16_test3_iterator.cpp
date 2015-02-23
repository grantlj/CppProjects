// ch16_test3_iterator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm> //use algorithm to implement sort, for_each, etc.
using namespace std;

struct Review{
	string title;
	int rate;
};

bool FillReview(Review& rr);
void ShowReview(const Review& rr);


int _tmain(int argc, _TCHAR* argv[])
{
	vector<Review> books;
	Review temp;

	while (FillReview(temp))
		//push_back is a function which directly append the elements
		//to the end of the vector. In other words, there is no need to
		//worry about the length of books.

		books.push_back(temp);
		int num = books.size();
		if (num > 0)
		{
			//First, we use the ordinary .size method to iterate the books.
			cout << "Thank you. You enter the following rating books." << endl;
			for (int i = 0; i < num; i++)
				ShowReview(books[i]);

			cout << "Respirsing:" << endl;
			//Second, we use the iterator. ������˵���˾��Ǳ���vector��ָ�롣
			vector<Review>::iterator pr;  //���巽����
			for (pr = books.begin(); pr != books.end(); pr++)
			{
				ShowReview(*pr);
			}

			vector<Review> oldlist(books);
			if (num > 3)
			{
				//remove from...to...
	            //��+1��ʼɾ��ɾ����+2��+3��ɾ����
				books.erase(books.begin() + 1, books.begin() + 3);
				cout << "After erasure:" << endl;
				for (pr = books.begin(); pr != books.end(); pr++)
					ShowReview(*pr);

				//insert 1 item.
				books.insert(books.begin(), oldlist.begin() + 1, oldlist.begin() + 2);

				cout << "After inseration:" << endl;
			    
				//Use for each.(algorithm class)
				for_each(books.begin(), books.end(), ShowReview);

				//for (pr = books.begin(); pr != books.end(); pr++)
					//ShowReview(*pr);

			}
			
			//������������ȫ������
			books.swap(oldlist);
			
			cout << "Swapping oldist with books:" << endl;

			for (pr = books.begin(); pr != books.end(); pr++)
				ShowReview(*pr);

			cout << "After sorting:" << endl;
			//ʹ��algorithm�е�sort�����������, ���Զ���������
			sort(books.begin(), books.end());

			for_each(books.begin(), books.end(), ShowReview);
		}

		else
			cout << "Noting entered, nothing gained" << endl;
	
	system("pause");
	return 0;
}

//����operator<���Ӷ�����sort
bool operator<(const Review& r1, const Review& r2)
{
	if (r1.title < r2.title)
		return true;
	else if (r1.title == r2.title && r1.rate < r2.rate)
		return true;
	else
		return false;
}

bool FillReview(Review& rr)
{
	cout << "Enter book title (quit to quit): ";
	getline(cin, rr.title);
	if (rr.title == "quit")
		return false;
	cout << "Enter book rating: ";
	cin >> rr.rate;
	if (!cin)
		return false;
	while (cin.get() != '\n')
		continue;
	return true;
}

void ShowReview(const Review& rr)
{
	cout << rr.rate << "\t" << rr.title << endl;
}

