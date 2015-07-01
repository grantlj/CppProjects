// Project_1.cpp : The main program for project 1.
// Author : Jiang Liu

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <time.h>
#include "binary.h"
#include "sequential_raw.h"
#include "sequential_rec.h"
#include <vector>
#include <algorithm>
#include <exception>
using namespace std;
//number of evaluation metrics.
const int n_num = 8;

//evaluation parameter: the length of list.
const int eval_n[n_num]={ 100, 500, 1000, 2000, 4000, 6000, 8000, 10000 };

//K_arr is the number of evaluation times for each parameter.
const int k_arr[n_num] = { 20000, 18000, 16000, 14000, 12000, 12000, 11000, 10000 };



//generate an sorted array.
void generate_sorted_array(int*& now_array, const int n)
{
	//using vector to generate random integer.
	vector<int> tmp_arr(n);

	for (int i = 0; i < n; i++)
		tmp_arr[i] = rand();

	//sort the vector.
	sort(tmp_arr.begin(), tmp_arr.end());

	//transfer to int array.
	for (int i = 0; i < n; i++)
		now_array[i] = tmp_arr[i];

}

int _tmain(int argc, _TCHAR* argv[])
{
	
	for (int i = 0; i < n_num; i++)
	{
		int now_n = eval_n[i];
		int *now_array=new int[now_n];
		cout << "================Begin the evaluation on n=" << now_n << "=====================" << endl;
		cout << "Generating raw data array with length:" << now_n << endl;
		
		cout << endl;

		//generate array.
		generate_sorted_array(now_array, now_n);

		int K = k_arr[i];

		//Conduct test on three different algorithms.
		for (int test_index = 0; test_index < 3; test_index++)
		{
			boolean overflow_flag = false;
			clock_t start, stop;
			start = clock();
			for (int exp = 0; exp < K; exp++)
			{
				//randomly select an x to search.
				//int x = now_array[rand() % now_n];

				//select a number larger than the last one, ensure the worst case happening.
				int x = now_array[now_n-1] + 1;
				
				
				switch (test_index)
				{

				case 0:
					seqential_search_iterative(now_array, now_n, x);
					break;
				case 1:

					try
					{

						sequential_search_rec(now_array, now_n, x);
					}
					catch (exception& e)
					{
						//cout << "OVERFLOW " << now_n;
						overflow_flag = true;
					}
					break;
				case 2:
					binary_search(now_array, now_n, x);
					break;

				}

				
		} //end of exp
	    stop = clock();



		//Calculate total_time and average duration.
		double ticks= stop - start;
		double total_time = ticks / CLK_TCK;
		//double total_time = stop - start;
		double duration = total_time / K;


		//Print out the evaluation result.
		switch (test_index)
		{

		case 0:
			cout << "SSI, total=" << total_time << "   dura:" << duration<<"	";
			break;
		case 1:
			if (!overflow_flag)  //catch recursive search's overflow exception.
				cout << "SSC, total=" << total_time << "   dura:" << duration << "	";
			else
				cout << "SSC:OVERFLOW";
			break;
		case 2:
			cout << "BIN, total=" << total_time << "   dura:" << duration << "	";
			break;

		}


		} //end of test_index.
	

		system("pause");
	}
	

	system("pause");
	return 0;
}

