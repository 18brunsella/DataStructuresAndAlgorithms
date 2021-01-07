#include "VerifySort.h"
using namespace std;

bool VerifySort(const vector<int> &a)
{
    // for loop for the vector
    for(int index = 0; index < a.size() - 1; index++){
        //if value before the next is greater then it is not sorted
        if(a[index] > a[index+1]){
            return false;
        }
    }
    //if the data successfully does go out the for loop
    return true;
}
