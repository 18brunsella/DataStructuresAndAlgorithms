#include "WeightedDigraph.hpp"

#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(int argc, char* argv[])
{

//    if(argc != 4) {
//        cerr << "Incorrect number of command line arguments." << endl;
//        cerr << "Usage: " << argv[0] << " <filename> <start vertex> <dest vertex>" << endl;
//        exit(EXIT_FAILURE);
//    }
    
    WeightedDigraph graph("g3.txt");
    cout << "The graph has " << graph.GetOrder() << " vertices and " << graph.GetSize() << " arcs" << endl;
    
    int source = 2;
    int dest = 1;
    
    if (graph.DoesPathExist(source, dest)) {
        cout << "Path from " << source << " to " << dest << ":" << endl;
        list<int> path = graph.FindMinimumWeightedPath(source, dest);
        bool isStart = true;
        for (int v : path) {
            if (!isStart) cout << " -> ";
            cout << v;
            isStart = false;
        }
        cout << endl;

        if (!graph.IsPathValid(path)) {
            cerr << "Error: Path is not valid!" << endl;
        }else {
            cout << "Path weight: " << graph.GetPathWeight(path) << endl;
        }
        
    }else {
      cout << "No path from " << source << " to " << dest << " exists!" << endl;
    }

    
    return 0;
}
