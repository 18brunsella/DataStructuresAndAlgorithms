
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "UnweightedGraph.h"                // Edit your code in UnweightedGraph.h and .cpp

using namespace std;


int main(int argc, char * argv[]) {
    
//    if(argc != 2) {
//        cout << "need input file" << endl;
//        return 0;
//    }
    
    UnweightedGraph G("test1.txt");
    G.DisplayInfo();
    cout << "G.IsConnected: " << G.IsConnected() << endl;
    cout << "G.IsEulerian: " <<G.IsEulerian() << endl;
    if(G.IsConnected() && G.IsEulerian()) {
        list<int> cycle = G.FindEulerianCycle();
        std::copy(begin(cycle),end(cycle),std::ostream_iterator<int>(std::cout," "));
        cout << endl;
        cout << "Verify cycle: " << G.VerifyEulerCycle(cycle) << endl;
    }
    
    
    return 0;
}
