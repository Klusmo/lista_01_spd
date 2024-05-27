#include <omp.h>
#include <iostream>
#include <vector>
#include <stack>
#include <mutex>

std::mutex mtx;

void parallelDFS(int v, std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    std::stack<int> stack;
    stack.push(v);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        if (!visited[node]) {
            mtx.lock();
            if (!visited[node]) {
                visited[node] = true;
                std::cout << node << " ";
            }
            mtx.unlock();

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    mtx.lock();
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                    mtx.unlock();
                }
            }
        }
    }
}

int main() {
    int n = 5; // número de nós
    std::vector<std::vector<int>> adj(n);

    // Grafo exemplo
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1};

    std::vector<bool> visited(n, false);

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(0, adj, visited);
        }
    }

    return 0;
}
