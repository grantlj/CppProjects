#include "sequential_rec.h"
#include "stdafx.h"

int sequential_search_rec(const int* list, const int n, const int x)
{
	//x is found.
	if (list[0] == x)
		return 0;
	else if (n > 1)
	{
		//x is not found, and there is still remaining list to iterate.
		int t = sequential_search_rec(list + 1, n - 1, x);
		if (t != -1)
			
			// as long as x is eventually found.
			return t + 1;
		else

			//x does NOT exist in the list.
			return -1;
	}
	else
		return -1;
}