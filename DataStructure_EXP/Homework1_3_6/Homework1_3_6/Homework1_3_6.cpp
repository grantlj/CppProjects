// Homework1_3_6.cpp : Homework for Chapter 3 Exercise 3.6
// Description: Polynomial addition with link list.
// Author : Jiang Liu (GJ011301, 2013210294)

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <cassert>
using namespace std;


struct Term{
	double coeff=0;   //coefficent of each term;
	int order = 0;    //order of each term;
	struct Term* next=NULL;//pointer to next term.
};


//print poly given link list.
void print_poly(Term* headnode)
{
	Term* now_node = headnode->next;

	int order = 0;
	while (now_node != NULL)
	{
		cout << now_node->coeff << "X^" << order << "	";
		order++;
		now_node = now_node->next;
	}

	cout << endl;
}


//initiazlize an n-order poly, return the head node.
Term* initialization(int n)
{
	cout << endl << "Please input the coeff(from constant term to highest order) for the " << n << "-th order poly:" << endl;
	
	Term* now_head = new Term;
	now_head->order = -1;     //the null node for head use. use order -1 as a flag.

	Term* last_node = now_head;

	for (int i = 0; i <= n; i++)
	{
		double tmp_coeff;
		cin >> tmp_coeff;

		Term* tmp_node = new Term;
		tmp_node->order = i;
		tmp_node->coeff = tmp_coeff;

		last_node->next = tmp_node;
		last_node = tmp_node;

	}

	cout << endl << "Initializtion finished, your input:" << endl;
	print_poly(now_head);

	return now_head;
}


//poly adder, store answer in poly_1 list.
void do_poly_adder(Term *head_1, Term *head_2)
{
	head_1 = head_1->next;
	head_2 = head_2->next;
	while (head_2 != NULL)
	{
		assert(head_1->order == head_2->order);        //Assertion: the order must be equal.
		head_1->coeff = head_1->coeff + head_2->coeff;

		head_1 = head_1->next;
		head_2 = head_2->next;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int m, n;
	Term *poly_1_head, *poly_2_head;   //the head of the link list for poly 1 and 2.

	cout << "Input the order of poly 1, m=";
	cin >> m;
	poly_1_head = initialization(m);         //generate link list for poly 1.


    cout << "Input the order of poly 2, n=";
	cin >> n;
	poly_2_head = initialization(n);        //generate link list for poly 2.


	//swap the order, we want to store the answer in poly_1's list, which should 
	//always with higher order.
	if (m < n)
	{
		int t = m; m = n; n = t;
		Term* t_node = poly_1_head; poly_1_head = poly_2_head; poly_2_head = t_node;
	}

	do_poly_adder(poly_1_head, poly_2_head);
	
	
	cout <<endl<< "The poly additioin answer is:"<<endl;
	print_poly(poly_1_head);
	system("pause");
	return 0;
}

