
#ifndef UnweightedGraph_H
#define UnweightedGraph_H
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
class UnweightedGraph
{
    public:
    UnweightedGraph(const string& t);
    void DisplayInfo() const;
    void BFS(int startingVertex, bool visit[]) const;
    bool IsConnected() const;
    bool IsEulerian() const;
    int FindNeighborVertex(int vertex, vector<list<int>> adj_list_copy) const;
    list<int> FindEulerianCycle() const;
    bool VerifyEulerCycle(const list<int>& cycle) const;
    
    private:
    vector<list<int>> adj_list;
    /// number of vertices in the graph
    int numberOfVertices = 0;
   
};
#endif
