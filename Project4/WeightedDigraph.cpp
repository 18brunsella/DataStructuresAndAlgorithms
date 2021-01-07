#include "WeightedDigraph.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <queue>
#include <set>
#include <limits>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename) : numVertices(0), numArcs(0) {
    ifstream in(filename);
    if(!in.is_open()) {
        cerr << "cannot open file!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    string line;
    getline(in, line);
    istringstream vertexStream(line);
    vertexStream >> numVertices;

    for(size_t i = 0; i < numVertices; i++){
        adj_list.resize(numVertices);
    }
    
    while(getline(in,line)) {
        istringstream iss(line);
        int u, v;
        float weight;
        iss >> u >> v >> weight;
        numArcs++;
        InsertArc(u, v, weight);
    }
    
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
    
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight) {
    // the index of first vector would be the from value, the to value would be the first in the pair, the second would be the weight
    adj_list[from].push_back(make_pair(to, weight));
    
}
 
/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
    //for iteration purposes
    int count = 0;
    //variable for the sum weight of the path 
    double sum = 0;
    
    //copies the path into another list
    list<int> copyPath(path);
    
    //iterates through the path until empty
    while(!copyPath.empty()){
        int variable = copyPath.front();
        copyPath.pop_front();
        //retrieves the weight between the edge
        for(auto vector : adj_list){
            if(variable == count){
                for(auto pair : vector){
                    if(pair.first == copyPath.front()){
                        sum += pair.second;
                        count = 0;
                    }
                }
                break;
            }else{
                count++;
                continue;
            }
        }
    }
    return sum;
}

bool WeightedDigraph::BFS(int from, int to, bool visit[]) const{
    visit[from] = true;
    int count = 0;
    // int loop = 0;
    // start a queue for BFS
    queue<int> q;
    q.push(from);
    
    //loops until the queue is empty
    while(!q.empty()){
        from = q.front();
        // dequeue
        q.pop();
        // iterating through each adjacent vertices
        for(auto vector : adj_list){
            if(count == from){
                for(auto pair : vector){
                    if(!visit[pair.first]){
                        visit[pair.first] = true;
                        q.push(pair.first);
                        count = 0;
                    }
                }
            }else{
                count++;
            }
        }
    }
    
    if(!visit[to]){
        return false;
    }
    
    return true;
    
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
    
    //variable for boolean of each node in graph
    bool visit[numVertices];
    
    //set all the nodes in the graph to false
    for(auto vector : adj_list){
        for(auto pair : vector){
            visit[pair.first] = false;
        }
    }
    
    // arbitrary vertex for BFS
    bool result = BFS(from, to, visit);
    
    // returns from the BFS search result
    return result;
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
    int count = 0;
    int found = 0;
    list<int> copyPath(path);
    while(copyPath.size() != 1){ // exits when the path only contains 1 node
        
        int variable = copyPath.front(); // takes first node
        copyPath.pop_front();
        
        for(auto vector : adj_list){ //iterates through adjancency list
            if(variable == count){ // if the node matches with the first value
                for(auto pair : vector){ //it searches for the other end of the path
                    if(pair.first == copyPath.front()){ //if found adds to found variable
                        found++;
                        count = 0;
                    }else{ // continues to search until the end
                        continue;
                    }
                }
                
                if(found != 0){ //if found it breaks out of for loop
                    found = 0;
                    break;
                }else if(found == 0){ //if nothing is found, then it returns false
                    return false;
                }
                
            }else{
                count++;
                continue;
            }
        }
    }
    // if it exits out of while loop, it means that the path is valid
    return true;
}

/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
    //final path
    list<int> result;
    //the distance from until that vertex
    double distance[numVertices];
    //checks if the vertex has been visited
    bool visited[numVertices];
    //for iteration
    int loop = 0;
    //keeps track of the previous node/parent node
    vector<int> previous;
    previous.resize(numVertices);
    
    // Dijkstra's Algroithm priority queue
    set<pair<double, int>> q;
    
    //set all the nodes in the graph to false and inserts the distance (infinity) to the priority queue
    for(auto vector : adj_list){
        for(auto pair : vector){
            visited[pair.first] = false;
            if(pair.first == from){
                distance[from] = 0;
                q.insert(make_pair(distance[from], from));
            }else{
                distance[pair.first] = std::numeric_limits<double>::infinity();
                q.insert(make_pair(distance[pair.first], pair.first));
            }
        }
    }
    
    //runs loop until the pq is empty
    while(!q.empty()){
        int start = q.begin()->second;
        q.erase(q.begin());
        visited[start] = true;
        for(auto vector : adj_list){
            if(loop == start){
                for(auto pair : vector){
                    if((distance[start] + pair.second) < distance[pair.first] && !visited[pair.first]){
                        distance[pair.first] = distance[start] + pair.second;
                        previous[pair.first] = start;
                        q.insert(make_pair(distance[pair.first], pair.first));
                    }
                }
            }
            loop++;
        }
        loop = 0;
        if(visited[to]){
            break;
        }
    }
    
    //adds the path into the list by accessing the previous vector
    result.push_front(to);
    while(result.front() != from){
        result.push_front(previous[to]);
        to = previous[to];
    }
    
    
    return result;
}
