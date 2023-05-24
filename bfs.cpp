#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

// Structure to represent a graph
struct Graph {
    int numVertices;
    std::vector<std::vector<int>> adjacencyList;
};

// Breadth-First Search
void parallelBFS(const Graph& graph, int startVertex) {
    std::vector<bool> visited(graph.numVertices, false);
    std::queue<int> bfsQueue;
    bfsQueue.push(startVertex);
    visited[startVertex] = true;

    #pragma omp parallel
    {
        while (!bfsQueue.empty()) {
            #pragma omp for
            for (int i = 0; i < bfsQueue.size(); ++i) {
                int currentVertex = bfsQueue.front();
                bfsQueue.pop();
                std::cout << currentVertex << " ";  // Process current vertex
                // Enqueue adjacent unvisited vertices
                for (int neighbor : graph.adjacencyList[currentVertex]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        bfsQueue.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    Graph graph;
    // Initialize the graph and populate the adjacency list

    // Example graph with 6 vertices
    graph.numVertices = 6;
    graph.adjacencyList.resize(graph.numVertices);

    // Add edges to the adjacency list
    graph.adjacencyList[0] = {1, 2};
    graph.adjacencyList[1] = {0, 2, 3, 4};
    graph.adjacencyList[2] = {0, 1, 4};
    graph.adjacencyList[3] = {1, 4, 5};
    graph.adjacencyList[4] = {1, 2, 3, 5};
    graph.adjacencyList[5] = {3, 4};

    // Perform parallel BFS
    parallelBFS(graph, 0);

    return 0;
}

