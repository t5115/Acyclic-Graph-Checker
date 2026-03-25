/* 
5SENG003W Algorithms – Coursework (2025/26)
Checking acyclicity of directed graphs
*/

#include <iostream>
#include <vector> 
#include <fstream> 
#include <set>
#include <map>

using namespace std;

// Task 2 - Data structure for representing direct graphs (adjacency matrix)
class Graph {
    private:
    int size; // number of nodes
    vector<vector<int>> matrix; // adjacency matrix

    public:
    Graph(int n) {
        size = n;
        matrix.resize(n, vector<int>(n, 0));
    }
    
    void addEdge(int from, int to){
        matrix[from][to] = 1;
    }

    void print(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                cout<<matrix[i][j]<<" ";
            };
            cout<<endl;
        };
    };

};

// Task 3 - Parser that takes an input to generate a graph
Graph InputGraph(){
    ifstream file("input.txt");  

    if (!file){
        cout<<"Error opening file\n";
    }

    vector<pair<int,int>> edges; // Stores all edges like (1,2),(3,1)
    set<int> nodes;  // stores unique nodes only

    int a, b;

    // Step 1: read edges + collect unique nodes
    while (file >> a >> b) {
        edges.push_back({a, b});
        nodes.insert(a);
        nodes.insert(b);
    }

    file.close();

    // Step 2: map each node → index
    map<int, int> nodeIndex;
    int index = 0;

    for (int node : nodes) {
        nodeIndex[node] = index++;
    }

    // Step 3: create graph with correct size
    Graph g(nodes.size());

    // Step 4: add edges using mapped indices
    for (auto e : edges) {
        int from = nodeIndex[e.first];
        int to   = nodeIndex[e.second];

        g.addEdge(from, to);
    }

    return g;
};

// Task 4 - Algorithm to check if a graph is acyclic, with checks to show how answer obtained.

// Task 5 - Prints first cycle find in a graph if not acyclic

// Program Start
int main(){
    Graph g = InputGraph();
    g.print();
};