#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <map>

class Graph {
public:
    void addEdge(int, int);
    void breadthFirstSearch(int);
    void depthFirstSearch(int);
private:                                        // map data structure, uses a number as a key
    std::map<int, std::vector<int>> vertices;   // allows vertices to be stored out of order                                       
};                                              
// add edge to graph class, sets v2 to v1's adjacency list and vice versa
void Graph::addEdge(int vertex1, int vertex2){
    vertices[vertex1].push_back(vertex2);
    vertices[vertex2].push_back(vertex1);
}
// traverse the graph and add each element encountered to a queue
// if the first element in the queue has not been encoutered before
// output it
void Graph::breadthFirstSearch(int start){
    std::map<int, bool> visited;                // map of vertices, uses bool to mark visited vertices
    std::queue<int> nextVertex;                 // queue data structure, allows fifo on vertices

    nextVertex.push(start);
    visited[start] = true;

    // loop while queue is not empty
    while (nextVertex.empty() == false){        
        int vertex = nextVertex.front();
        nextVertex.pop();

        std::cout << vertex << " ";

        // loop through all adjacent vertices
        for (int adjVertex : vertices[vertex]){ 
            if (visited[adjVertex] == false){
                nextVertex.push(adjVertex);
                visited[adjVertex] = true;
            }
        }
    }
    std::cout << std::endl;
}
// traverse the graph and add each element encoutnered to a stack
// if the first element in the stack has not been encountered before 
// output it
void Graph::depthFirstSearch(int start) {
    std::map<int, bool> visited;                // map of vertices, uses bool to mark visited vertices
    std::stack<int> nextVertex;                 // stack data structure, allows lifo on vertices
        
    nextVertex.push(start);
    visited[start] = true;

    // loop while stack is not empty
    while (nextVertex.empty() == false) {
        int vertex = nextVertex.top();
        nextVertex.pop();

        std::cout << vertex << " ";

        // loop through all adjancent vertices
        for (int adjVertex : vertices[vertex]) {
            if (visited[adjVertex] == false) {
                nextVertex.push(adjVertex);
                visited[adjVertex] = true;
            }
        }
    }
    std::cout << std::endl;
}
int main(){
    Graph Graph;
    std::ifstream inFile;
    std::string file;
    int vertex = 0;
    int adjVertex = 0;
    int max = 0;

    std::cout << "Enter file with list: ";      // grab list of vertices          
    std::cin >> file;
    inFile.open(file);

    // error checking file open
    while (inFile.is_open() == false) {                 
        std::cout << "Invalid file, please re-enter: ";
        std::cin >> file;
        inFile.open(file);
    }
    // add vertices from file to Graph class
    while (inFile.eof() == false) {                     
        inFile >> vertex;
        inFile >> adjVertex;

        Graph.addEdge(vertex, adjVertex);

        if (vertex > max)                       // find last vertex, used to output
            max = vertex;
        else if (adjVertex > max)
            max = adjVertex;
    }
    // output every possible starting vertex from 1 to max
    for (int vertex = 1; vertex <= max; vertex++) {     
        std::cout << std::endl << "Starting vertex " << vertex << std::endl;

        std::cout << "Breadth-First Search: ";
        Graph.breadthFirstSearch(vertex);               
            
        std::cout << "Depth-First Search: ";
        Graph.depthFirstSearch(vertex);
    }
}

