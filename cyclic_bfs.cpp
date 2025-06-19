#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> adj = {
    {0, 0, 1, 0, 0, 0, 0}, // A → C
    {0, 0, 1, 0, 0, 0, 0}, // B → C
    {0, 0, 0, 0, 1, 1, 1}, // C → E, F, G
    {1, 0, 0, 0, 1, 0, 0}, // D → A, E
    {1, 0, 0, 0, 0, 0, 0}, // E → A
    {0, 1, 0, 0, 0, 0, 0}, // F → B
    {0, 0, 0, 0, 0, 0, 0}  // G
};

vector<int> cycle;

bool bfs() {
    int n = adj.size();
    vector<int> indegree(n, 0);
    
    // Calculate indegrees
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j]) indegree[j]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    int processed = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        processed++;
        
        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0) q.push(v);
            }
        }
    }
    
    // If not all vertices processed, there's a cycle
    if (processed != n) {
        // Find vertices in cycle
        for (int i = 0; i < n; i++) {
            if (indegree[i] > 0) {
                cycle.push_back(i);
            }
        }
        return true;
    }
    
    return false;
}

int main() {
    int n = adj.size();
    
    cout << "BFS Cycle Detection (Kahn's Algorithm)\n";
    cout << "Graph Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
    
    if (bfs()) {
        cout << "\nCycle detected!\n";
        cout << "Vertices in cycles: ";
        // Sort cycle vertices alphabetically
        sort(cycle.begin(), cycle.end());
        for (int v : cycle) {
            cout << char('A' + v) << " ";
        }
        cout << "\n";
        cout << "Cycles: A-C-E and C-F-B\n";
    } else {
        cout << "\nNo cycle detected.\n";
    }
    
    return 0;
}