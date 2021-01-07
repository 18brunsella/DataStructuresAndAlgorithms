 #include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include "InsertionSort.h"	 // Edit your insertion sort code  
#include "QuickSort.h"		 // Edit your quick sort code  
#include "VerifySort.h"		 // Edit your code for verifying sorting result 
#include <fstream>
#include <time.h>
#include <chrono>

using namespace std; 
using namespace std::chrono;


/*
 * DO NOT CHANGE THIS FILE
 */

int main(int argc, char * argv[]) {
	
    if ( argc != 2 ) {
        cout<< "usage: "<< argv[0] <<" <filename>\n";
    	return 0;
    }

    ifstream infile(argv[1]);
	
    // check to see if file can be successfully opened. 
    if ( !infile.is_open() ) {
        cout<<"Could not open file\n";
        return 0;
     }

    vector<int> x,y;

    //read inputs
    int input_t;
    while( infile >> input_t) {
    	x.push_back(input_t);
    	y.push_back(input_t);
    }

    cout << "number of keys: " << x.size() << endl;

    high_resolution_clock::time_point t1,t2;
    long long comparisons;
 
//  quicksort
    t1 =  high_resolution_clock::now(); 
    comparisons = QuickSort(x);
    t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
    
    cout << "QuickSort \nnumber of comparisons: " << comparisons   <<endl;
    cout << "time: " << duration << " ms"<< endl; 
    cout << (VerifySort(x)? "Sorted\n":" Failed\n");

//  insertion sort
    t1 =  high_resolution_clock::now(); 
    comparisons = InsertionSort(y); 
    t2 =  high_resolution_clock::now();
    duration = duration_cast<milliseconds>( t2 - t1 ).count();
  
    cout << "InsertionSort \nnumber of comparisons: " << comparisons  <<endl;
    cout << "time: " << duration << " ms" << endl; 
    cout << (VerifySort(y)? "Sorted \n":"Failed\n");

    //clean up file reader
    infile.close();
    
    return 0;
}
