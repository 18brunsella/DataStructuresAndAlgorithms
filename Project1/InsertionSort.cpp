#include "InsertionSort.h"
using namespace std;

long long InsertionSort(vector<int> &a)
{
    long long numofcomp = 0;
    
    for(int loop = 0; loop < a.size(); loop++)
    {
        
        // set equal the amount of loops it has done to the index
        int index = loop;
        
        // if the index is larger than 0 and and if the left data value is larger than the index we are on, it swaps
        while(index > 0 && a[index-1] > a[index])
        {
            // sets a temporary variable
            int tmp = a[index-1];
            //swaps the two index values
            a[index-1] = a[index];
            a[index] = tmp;
            
            // sets the index down one to account if the value has to compare again
            index = index - 1;
            
            // adds to the counter for number of comparisons
            numofcomp += 1;
        }
        
        if(a[index - 1] < a[index])
        {
            numofcomp += 1;
        }
    }
    
    // returns the number of comparisons minus one for accounting the first element that does not compare
    // with anything
    return numofcomp - 1;
}
