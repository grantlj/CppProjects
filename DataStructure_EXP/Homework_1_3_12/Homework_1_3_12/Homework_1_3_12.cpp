// Homework1_3_12.cpp : Homework for Chapter 3 Exercise 3.12
// Description: Link list reversal.
// Author : Jiang Liu (GJ011301, 2013210294)
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


struct Term{
    int num = 0;    //order of each term;
	struct Term* next = NULL;//pointer to next term.
};

//print linklist given headnode.
void print_link_list(Term* headnode)
{
	Term* now_node = headnode->next;
	//cout << "now_node" << now_node->num;
    while (now_node != NULL)
	{
		cout << now_node->num;
		now_node = now_node->next;
	//	system("pause");
	}

	cout << endl;
}

//initiazlize an n-array linklist, return the head node.
Term* initialization(int n)
{

	Term* now_head = new Term;

	Term* last_node = now_head;

	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;

		Term* tmp_node = new Term;
		tmp_node->num = tmp;

		last_node->next = tmp_node;
		last_node = tmp_node;

	}

	cout << endl << "Initializtion finished, your input:" << endl;
	print_link_list(now_head);

	return now_head;
}


 void link_list_reversal(Term*& head)
{
	Term *p1 = head;
	Term *p2 = head->next;
	Term *tmp_node;
	int i = 0;

	while (p2 != NULL)
	{
		i++;
		p1->num = p2->num;
		tmp_node = p2->next;

		p2->next = p1;
		if (i == 1)
			p1->next = NULL;

		p1 = p2;
		p2 = tmp_node;
	}

	head = p1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Input n=" << endl;
	int n;
	cin >> n;

	Term* head;
	head = initialization(n);
	
	link_list_reversal(head);
	
	cout << endl << "After reversal:";
	print_link_list(head);

	system("pause");
	return 0;
}

