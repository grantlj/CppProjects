// EXP1_link_list.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Node.cpp"
#include <iostream>
using namespace std;

void initialize_list(MYNODE*, int);
void print_list(MYNODE*);
void add_element_at(MYNODE*, int, int);
void delete_element_at(MYNODE*, int);
int find_element(MYNODE*, int);

int _tmain(int argc, _TCHAR* argv[])
{
	MYNODE* p_head = new MYNODE;

	cout << "Input n=";
	int n;
	cin >> n;
	
	initialize_list(p_head, n);
	print_list(p_head);

	cout << "Add an element x at pos n:";
	
	int x, pos;
	cin >> x >> pos;

	add_element_at(p_head,x, pos);
	print_list(p_head);

	cout << "Delete the newly added element:";
	delete_element_at(p_head, pos);
	print_list(p_head);

	cout << "Find an element x:";
	cin >> x;
	cout<<"Element find at first index of:"<<find_element(p_head, x)<<endl;

	system("pause");
	return 0;
}


//initialize node list with n element.
void initialize_list(MYNODE* p_head, int n)
{
	cout << "Initializing list..." << endl;
	MYNODE* last_node = p_head;

	for (int i = 0; i < n; i++)
	{
		cout << "Input No." << i+1<<"-st element:";
		int t;
		cin >> t;
		
		MYNODE* p_now = new MYNODE;
		p_now->x = t;
		p_now->next = NULL;
		last_node->next = p_now;
		last_node = last_node->next;
	}
}

//print list.
void print_list(MYNODE* p_head)
{
	cout << "Print list info..." << endl;
	MYNODE* p_now = p_head;
	int i = 0;
	do
	{
		i++;
		p_now = p_now->next;
		cout <<"No."<<i<<"-st element is:"<< p_now->x<<endl;
	} while (p_now->next != NULL);

	//system("pause");
}


//add element x, at position pos.
void add_element_at(MYNODE* p_head, int x, int pos)
{
	MYNODE* p_now = p_head->next;
	MYNODE* p_last = p_head;
	int i = 1;
	while (i != pos && p_now != NULL)
	{
		i++;
		p_last = p_now;
		p_now = p_now->next;
	}

	MYNODE* p_added = new MYNODE;
	p_added->x = x;
	
	
	p_last->next = p_added;
	p_added->next = p_now;
	


}

//Delete element at pos.
void delete_element_at(MYNODE* p_head, int pos)
{
	MYNODE* p_now = p_head->next;
	MYNODE* p_last = p_head;
	int i = 1;
	while (i != pos && p_now != NULL)
	{
		i++;
		p_last = p_now;
		p_now = p_now->next;
	}

	p_last->next = p_now->next;
	delete(p_now);
}

//find element x;
int find_element(MYNODE* p_head, int x)
{
	MYNODE* p_now = p_head->next;
	
	int i = 1;
	while (p_now->x!=x && p_now != NULL)
	{
		i++;
		//p_last = p_now;
		p_now = p_now->next;
	}

	if (p_now == NULL)
		return -1;
	else
		return i;

}