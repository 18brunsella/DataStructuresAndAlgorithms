#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_
#include <vector>
#include <fstream>

/*
input: a vector of integers.
output: number of comparisons by InsertionSort algorithm.
side-effect: vector 'a' is sorted in non-decreasing order. 
note: to prevent integer overflow, long long is used for counting number of comparisons.
*/

long long InsertionSort(std::vector<int> &a); //do not change this line 

//you can add helper functions here

#endif
