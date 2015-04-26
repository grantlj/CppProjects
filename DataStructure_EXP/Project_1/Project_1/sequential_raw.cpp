#include "stdafx.h"
#include "sequential_raw.h"
//iterative sequential search for an integer x in list, with length n.
int seqential_search_iterative(const int* list, const int n, const int x)
{
	for (int i = 0; i < n; i++)
	{
		if (list[i] == x)
			return i;
	}

	return -1;
}