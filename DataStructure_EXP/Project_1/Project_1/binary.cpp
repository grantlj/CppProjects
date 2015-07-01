#include "binary.h"
#include "stdafx.h"
//#include <iostream>
int binary_search(const int* list, const int n, const int x)
{
	//std::cout << x;
	int head = 0;
	int tail = n - 1;
	int mid = (head + tail) / 2;
	while (list[mid] != x && head < tail)
	{
		if (list[mid]>x)
			tail = mid - 1;

		if (list[mid] < x)
			head = mid + 1;

		mid = (head + tail) / 2;
	}

	if (head >= tail)
		return -1;
	else
		return mid;
}