
#include "UnweightedGraph.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <queue>
#include <list>

using namespace std;

UnweightedGraph::UnweightedGraph(const string& t)
{
  //You may add any construction to your private attribute.
        ifstream in(t);
        if(!in.is_open()) {
            cerr << "cannot open file!" << std::endl;
            exit(EXIT_FAILURE);
        }
        string line;
        while(getline(in,line)) {
            istringstream iss(line);
            int v;
            list<int> list_temp;
        int first_item = 0;
            while( iss >> v) {
            first_item++;
            if(first_item==1) continue;
                list_temp.push_back(v);
 
            }
            adj_list.push_back(list_temp);
            numberOfVertices++;
        }
 
 

}

void UnweightedGraph::DisplayInfo() const{
    cout << "Adjacency list of the graph \n";
    int i = 0;
    auto printItem = [&i](const list<int>& alist) {
            cout << i++ << " ";
        copy(begin(alist),end(alist), ostream_iterator<int>(cout, " "));
        cout << endl;

    };
    for_each(begin(adj_list),end(adj_list), printItem);
}

void UnweightedGraph::BFS(int Vertex, bool visit[]) const{
    visit[Vertex] = true;
    // start a queue for BFS
    queue<int> q;
    q.push(Vertex);
    
    //loops until the queue is empty
    while(!q.empty()){
        Vertex = q.front();
        // dequeue
        q.pop();
        // iterating through each adjacent vertices
        for (size_t i = 0; i < adj_list.size(); i++) {
            for (int num : adj_list[i]) {
                if(!visit[num] && i == Vertex){
                    visit[num] = true;
                    q.push(num);
                }
            }
        }
    }
    
}

bool UnweightedGraph::IsConnected() const {
    // initialize all the vertices
    bool visit[numberOfVertices];
    // at this point they are not visited by DFS, so it is false
    for(int i = 0; i < numberOfVertices; i++){
        visit[i] = false;
    }
    // arbitrary vertex for BFS
    BFS(0, visit);
    // checks if each vertex was visited or not
    for(int i = 0; i < numberOfVertices; i++){
        if(visit[i] == false){
            return false;
        }
    }
    return true;
}

bool UnweightedGraph::IsEulerian() const {
    // checks if the graph is connected or not
    if(IsConnected() == false){
        return false;
    }
    // checks each vertex if it is a even or odd degree
    for (size_t i = 0; i < adj_list.size(); i++) {
        // if even you would continue through the iteration
        if(adj_list[i].size() % 2 == 0){
            continue;
        }else{
            // if odd return false
            return false;
        }
    }
    
    return true;
}


int UnweightedGraph::FindNeighborVertex(int vertex, vector<list<int>> adj_list_copy) const{
    for(auto num : adj_list_copy[vertex]){
        return num;
    }
    return vertex;
}

bool contains(std::list<int> & listOfElements, const int & element)
{
    auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
    return it != listOfElements.end();
}

list<int> UnweightedGraph::FindEulerianCycle() const{
    vector<list<int>> adj_list_copy = adj_list;
    list<int> visited_vertices;
    list<int> subgraph_cycle;
    list<int> starting_nodes;
    
    //if not Eulerian, returns empty cycle
    if(IsEulerian() == false){
        return subgraph_cycle;
    }
    
    for(int i = 0; i < numberOfVertices; i++){
        visited_vertices.push_back(i);
    }
    
    
    int starting_vertex = 0;
    int vertex;
    bool visited[numberOfVertices];
    int counter = 0;
    int original_vertex = 0;
    
    
    //To find the first initial complete cycle
    while(true){
        subgraph_cycle.push_back(starting_vertex);
        vertex = FindNeighborVertex(starting_vertex, adj_list_copy);
        visited[starting_vertex] = true;
        visited_vertices.remove(starting_vertex);
        adj_list_copy[starting_vertex].remove(vertex);
        adj_list_copy[vertex].remove(starting_vertex);
        starting_vertex = vertex;
        if(subgraph_cycle.front() == subgraph_cycle.back() && counter != 0){
            break;
        }
        counter++;
    }
    
    //Transition from the first complete to the subgraphs
    list<int> current_cycle(subgraph_cycle);
    subgraph_cycle.clear();
    for(int i = 0; i < numberOfVertices; i++){
        bool result = contains(current_cycle, i);
        if(result && i != original_vertex){
            starting_vertex = i;
            break;
        }
    }
    counter = 0;
    list<int>::iterator it;
    
    
    //Creating sub-cycles until all the edges are visited
    while(!visited_vertices.empty()){
        while(true){
            if(counter == 0){
                original_vertex = starting_vertex;
            }
            subgraph_cycle.push_back(starting_vertex);
            vertex = FindNeighborVertex(starting_vertex, adj_list_copy);
            visited[starting_vertex] = true;
            visited_vertices.remove(starting_vertex);
            adj_list_copy[starting_vertex].remove(vertex);
            adj_list_copy[vertex].remove(starting_vertex);
            starting_vertex = vertex;
            if(subgraph_cycle.front() == subgraph_cycle.back() && counter != 0){
                break;
            }
            if(visited_vertices.empty()){
                break;
            }
            counter++;
        }
        
        subgraph_cycle.pop_back();
        it = find(current_cycle.begin(), current_cycle.end(), original_vertex);
        current_cycle.splice(it, subgraph_cycle);
        subgraph_cycle.clear();
        
        for(int i = 0; i < numberOfVertices; i++){
            if(contains(starting_nodes, i)){
                continue;
            }
            if(i!= original_vertex && visited[i] && current_cycle.front() != i){
                starting_vertex = i;
                starting_nodes.push_back(i);
                break;
            }
        }
        counter = 0;
        
    }

    return current_cycle;
}


bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
    if(cycle.front() == cycle.back()){
        return true;
    }
    
    return false;
}
