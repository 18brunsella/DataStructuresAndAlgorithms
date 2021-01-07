#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_
#include <vector>
#include <fstream>


/*
input: a vector of integers.
output: number of comparisons by QuickSort algorithm.
side-effect: vector 'a' is sorted in non-decreasing order. 
note: to prevent integer overflow, long long is used for counting number of comparisons.
*/
long long QuickSort(std::vector<int> & a); //do not change this line 

long long QuickSortHelper(std::vector<int> & a, int beginofarray, int endofarray);

int Partition(std::vector<int> & a, int beginofarray, int endofarray);

#endif

