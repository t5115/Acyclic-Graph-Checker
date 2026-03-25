/* 
Checking acyclicity of directed graphs
*/

#include <iostream>
#include <vector> 
#include <fstream> 
#include <set>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

// Task 2 - Data structure for representing direct graphs (adjacency matrix)
class Graph {
    private:
    int size; // number of nodes
    vector<vector<int>> matrix; // adjacency matrix
    map<int,int> indexToNode; 

    public:
    Graph(int n) {
        size = n;
        matrix.resize(n, vector<int>(n, 0));
    }
    
    // Getters
    int getSize(){
       return size;
    }

    vector<vector<int>> getMatrix() {
        return matrix;
    }

    map<int,int> getIndexToNode() { 
        return indexToNode;
    }

    // Setters
    void addEdge(int from, int to){
        matrix[from][to] = 1;
    }

    void setMapping(map<int,int> m) { 
        indexToNode = m;
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
        exit(1);
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
    map<int, int> indexToNode; // Store original node
    int index = 0;

    for (int node : nodes) {
       nodeIndex[node] = index;
       indexToNode[index] = node; // Store reverse
       index++;
    }

    // Step 3: create graph with correct size
    Graph g(nodes.size());
    g.setMapping(indexToNode);
      
    // Step 4: add edges using mapped indices
    for (auto e : edges) {
        int from = nodeIndex[e.first];
        int to   = nodeIndex[e.second];

        g.addEdge(from, to);
    }

    return g;
};

// Task 4 - Sink Elimination Algorithm to check if a graph is acyclic, shows how answer obtained.
bool CheckAcyclic(Graph g){
    map<int,int> indexToNode = g.getIndexToNode();
    vector<vector<int>> mat = g.getMatrix();
    int n = g.getSize();

    vector<bool> removed(n, false); // track removed nodes
    int remaining = n;

     while (remaining > 0) {
        bool foundSink = false;

        // Try to find a sink
        for (int i = 0; i < n; i++) {
            if (removed[i]) continue;

            bool isSink = true;

            // check row i → outgoing edges
            for (int j = 0; j < n; j++) {
                if (!removed[j] && mat[i][j] == 1) {
                    isSink = false;
                    break;
                }
            }

            if (isSink) {
                //cout << "Sink found: Node " << i  << " (original: " << indexToNode[i] << ")" << endl; 

                // "Remove" node i
                removed[i] = true;
                remaining--;

                cout << "Removing sink found at node " << i  << " (original value: " << indexToNode[i] << ")" << endl;

                foundSink = true;
                break; // restart search
            }
        }

        // If no sink found → cycle exists
        if (!foundSink) {
            cout << "No sink found → Graph has a cycle" << endl;
            return false;
        }
    }

    cout << "All nodes removed → Graph is acyclic" << endl;
    return true;
}

// Task 5 - Prints first cycle find in a graph if cyclic using Depth First Search (If the same node revisited then cycle found)
void FindCycle(Graph g){
    map<int,int> indexToNode = g.getIndexToNode();
    vector<vector<int>> mat = g.getMatrix();
    int n = g.getSize();

    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parent(n, -1);

    int start = -1, end = -1;

    // DFS as a lambda function
    function<bool(int)> dfs = [&](int node) {
        visited[node] = true;
        recStack[node] = true;

        for (int j = 0; j < n; j++) {
            if (mat[node][j] == 1) {

                if (!visited[j]) {
                    parent[j] = node;

                    if (dfs(j))
                        return true;
                }
                else if (recStack[j]) {
                    // cycle found
                    start = j;
                    end = node;
                    return true;
                }
            }
        }

        recStack[node] = false;
        return false;
    };

    // Run DFS from each node
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i)) {

                cout << "Cycle found: ";

                vector<int> cycle;
                cycle.push_back(start);

                for (int v = end; v != start; v = parent[v]) {
                    cycle.push_back(v);
                }
                cycle.push_back(start);

                reverse(cycle.begin(), cycle.end());

                for (int v : cycle)
                    cout << indexToNode[v] << " ";

                cout << endl;
                return;
            }
        }
    }

    cout << "No cycle found" << endl;
}

// Program Start
int main(){
    cout << endl;
    Graph g = InputGraph();
    g.print();

    // If false then print first cycle found (Task 5)
    if (!CheckAcyclic(g)){
        FindCycle(g);
    }
   
};
