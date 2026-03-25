/* 
5SENG003W Algorithms – Coursework (2025/26)
Checking acyclicity of directed graphs
*/

#include <iostream>
#include <vector>
using namespace std;

// Task 2 - Data structure for representing direct graphs ()
class Graph {
    private:
    int size; // number of nodes
    vector<vector<int>> matrix; // adjacency matrix

    public:
    Graph(int n) {
        size = n;
        matrix.resize(n, vector<int>(n, 0));
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

// Task 4 - Algorithm to check if a graph is acyclic, with checks to show how answer obtained.

// Task 5 - Prints first cycle find in a graph if not acyclic

// Program Start
int main(){
    cout<<endl;
    Graph g(3);
    g.print();
}