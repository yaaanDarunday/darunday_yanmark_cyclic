#include <iostream>
#include <vector>
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

vector<vector<int>> cycles;
vector<int> state; // 0: unvisited, 1: visiting, 2: visited

void dfs(int u, vector<int>& path) {
    state[u] = 1;
    path.push_back(u);
    
    for (int v = 0; v < adj.size(); v++) {
        if (adj[u][v]) {
            if (state[v] == 1) {
                // Found back edge - extract cycle
                vector<int> cycle;
                bool found = false;
                for (int node : path) {
                    if (node == v) found = true;
                    if (found) cycle.push_back(node);
                }
                
                // Check if this cycle is new
                bool isNew = true;
                for (auto& existingCycle : cycles) {
                    if (cycle.size() == existingCycle.size()) {
                        bool same = true;
                        for (int i = 0; i < cycle.size(); i++) {
                            bool found = false;
                            for (int j = 0; j < existingCycle.size(); j++) {
                                if (cycle[i] == existingCycle[j]) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                same = false;
                                break;
                            }
                        }
                        if (same) {
                            isNew = false;
                            break;
                        }
                    }
                }
                
                if (isNew) cycles.push_back(cycle);
            }
            else if (state[v] == 0) {
                dfs(v, path);
            }
        }
    }
    
    path.pop_back();
    state[u] = 2;
}

int main() {
    int n = adj.size();
    state.assign(n, 0);
    
    cout << "DFS Cycle Detection\n";
    cout << "Graph Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }
    
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            vector<int> path;
            dfs(i, path);
        }
    }
    
    if (!cycles.empty()) {
        cout << "\nCycles detected: " << cycles.size() << "\n";
        for (int i = 0; i < cycles.size(); i++) {
            cout << "Cycle " << i + 1 << ": ";
            for (int v : cycles[i]) {
                cout << char('A' + v) << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "\nNo cycle detected.\n";
    }
    
    return 0;
}