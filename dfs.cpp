#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

void parallel_dfs(vector<vector<int> >& graph, vector<bool>& visited, int start) {
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (!visited[node]) {
            #pragma omp critical
            {
                visited[node] = true;
                cout << "Node " << node << " visited by Thread " << omp_get_thread_num() << endl;
            }

            for (int i = 0; i < graph[node].size(); i++) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }
        }
    }
}

int main() {
    int numNodes, numEdges;

    cout << "Enter the number of nodes in the graph: ";
    cin >> numNodes;

    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    // Create the adjacency list representation of the graph
    vector<vector<int> > graph(numNodes);
    vector<bool> visited(numNodes, false);

    cout << "Enter the edges (node1 node2):\n";
    for (int i = 0; i < numEdges; i++) {
        int node1, node2;
        cin >> node1 >> node2;

        // Add edges to the adjacency list
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    // Perform parallel DFS on the graph
    #pragma omp parallel shared(graph, visited)
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < numNodes; i++) {
            if (!visited[i]) {
                parallel_dfs(graph, visited, i);
            }
        }
    }

    return 0;
}
