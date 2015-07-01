// Balance_Heap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
using namespace std;

struct TREENODE{
	int height = 1;
	int val;
	TREENODE* left = NULL, *right=NULL;
};

TREENODE* createTreeWithVal(int tmp)
{
	TREENODE* root = new TREENODE;
	root->val = tmp;
	return root;
}

void insertAnNewValue(TREENODE* root, int tmp)
{
	if (root->val > tmp)
	{
		if (root->left == NULL)
		{
			TREENODE* newnode = new TREENODE;
			newnode->val = tmp;
			newnode->height = root->height + 1;
			root->left = newnode;
		}

		else
			insertAnNewValue(root->left, tmp);
	}

	else
	{
		if (root->right == NULL)
		{
			TREENODE* newnode = new TREENODE;
			newnode->val = tmp;
			newnode->height = root->height + 1;
			root->right = newnode;
		}

		else
			insertAnNewValue(root->right, tmp);
	}
}

void mid_ergodic(TREENODE* root)
{
	if (root->left != NULL)
		mid_ergodic(root->left);
	cout << root->val << "("<<root->height<<") ";
	if (root->right != NULL)
		mid_ergodic(root->right);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cin >> n;

	TREENODE* root=NULL;
	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;
		
		if (i==0)
		  root = createTreeWithVal(tmp);

		insertAnNewValue(root, tmp);
	}

	cout << "Mid ergodic:" << endl;
	mid_ergodic(root);
	
	system("pause");
	return 0;
}

