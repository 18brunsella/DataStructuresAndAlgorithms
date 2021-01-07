#ifndef WeightedDigraph_H
#define WeightedDigraph_H

#include<list>
#include<string>
#include<vector>
#include<utility>

class WeightedDigraph {
public:
    WeightedDigraph(const std::string& filename);
    ~WeightedDigraph();
    
    WeightedDigraph(const WeightedDigraph&) = delete;
    WeightedDigraph& operator=(const WeightedDigraph&) = delete;
    
    int GetOrder() const { return numVertices; };
    int GetSize() const { return numArcs; };
    
    double GetPathWeight(const std::list<int> & path) const;
    bool BFS(int from, int to, bool visit[]) const;
    bool DoesPathExist(int from, int to) const;
    bool IsPathValid(const std::list<int> & path) const;
    std::list<int> FindMinimumWeightedPath(int from, int to) const;
    
private:
    int numVertices;
    int numArcs;
    std::vector<std::vector<std::pair<int, double>>> adj_list;
    
    void InsertArc(int from, int to, double weight);
};

#endif
