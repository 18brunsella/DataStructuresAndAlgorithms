#include "QuickSort.h"
using namespace std;

// Function that does the partitioning process
// of the quicksort algorithm: returning the index where the pivot is
int Partition(vector <int> & a, int begin_of_array, int end_of_array)
{
    // constants: secondloop would be the variable that would keep track of the value before pivot
    // pivot would be the first value in the vector
    int secondloop = begin_of_array;
    int pivot = a[secondloop];
    
    // for loop that would go until the initialloop hits the end of the vector
    for(int initialloop = begin_of_array + 1; initialloop <= end_of_array; initialloop++)
    {
        // if the pivot is less than the non-pivot element
        if (pivot < a[initialloop])
        {
            //then for loop continues
            continue;
        }
        else if (pivot > a[initialloop]) // if pivot is greater than non-pivot element
        {
            secondloop = secondloop + 1; // the second loop would go to the next index
            swap(a[secondloop], a[initialloop]); // then they would swap with the second loop element
        }
        
    }
    // after exiting the for loop you would have to insert the pivot where it belongs
    swap(a[secondloop], a[begin_of_array]);
    return secondloop;
}

// function that helps the process of
// the quicksort algorithm: returns the number of comparisons
long long QuickSortHelper(vector<int>& a, int begin_of_array, int end_of_array)
{
    // constant: numofcomp keeps track of the number of comparisons
    long long numofcomp = 0;
    
    // the process stops if the begin is less than the end index
    if(begin_of_array < end_of_array)
    {
        numofcomp += end_of_array - 1;
        int i = Partition(a, begin_of_array, end_of_array);
        QuickSortHelper(a, begin_of_array, i-1);
        QuickSortHelper(a, i+1, end_of_array);
    }
    
    return numofcomp;
}

// function that initially calls for
// the vector and starts the whole algorithm: returns the number of comparisons
long long QuickSort(vector<int> & a)
{
    // if the vector has 1 element or has none: returns 0 comparisons
    long long nocomp = 0;
    if(a.size() == 1 || a.size() == 0){
        return nocomp;
    }
    
    // constants: low is the beginning of the array, high is the end of the array
    int low = 0;
    int high = a.size() - 1;
    
    // calls for the QuickSortHelper
    long long result = QuickSortHelper(a, low, high);
    nocomp = high + result;
    
    return nocomp;
}
