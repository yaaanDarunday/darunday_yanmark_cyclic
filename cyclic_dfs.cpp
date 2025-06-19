#include <iostream>
using namespace std;

const int SIZE = 7;
int graph[SIZE][SIZE] = {
    {0, 0, 1, 0, 0, 0, 0}, // A → C
    {0, 0, 1, 0, 0, 0, 0}, // B → C
    {0, 0, 0, 0, 1, 1, 1}, // C → E, F, G
    {1, 0, 0, 0, 1, 0, 0}, // D → A, E
    {1, 0, 0, 0, 0, 0, 0}, // E → A
    {0, 1, 0, 0, 0, 0, 0}, // F → B
    {0, 0, 0, 0, 0, 0, 0}  // G
};

char vertices[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
int color[SIZE], parent[SIZE], cycle[SIZE], cycleLen, cycleCount = 0;

bool dfs(int v) {
    color[v] = 1;
    for(int u = 0; u < SIZE; u++) {
        if(graph[v][u]) {
            if(color[u] == 1) {
                cycleCount++;
                cout << "DFS - Cycle " << cycleCount << ": ";
                cycleLen = 0;
                cycle[cycleLen++] = u;
                int cur = v;
                while(cur != u) {
                    cycle[cycleLen++] = cur;
                    cur = parent[cur];
                }
                cycle[cycleLen++] = u;
                for(int j = cycleLen-1; j >= 0; j--) {
                    cout << vertices[cycle[j]];
                    if(j > 0) cout << " ";
                }
                cout << "\n";
                // Don't return, continue to find more cycles
            }
            if(color[u] == 0) {
                parent[u] = v;
                dfs(u);
            }
        }
    }
    color[v] = 2; 
    return false;
}

void detectCycleDFS() {
    for(int i = 0; i < SIZE; i++) color[i] = 0, parent[i] = -1;
    
    for(int i = 0; i < SIZE; i++) {
        if(color[i] == 0) {
            dfs(i);
        }
    }
    
    if(cycleCount == 0) {
        cout << "DFS - No cycles found\n";
    } else {
        cout << "DFS - Total cycles found: " << cycleCount << "\n";
    }
}

int main() {
    cout << "DFS Cycle Detection\n";
    cout << "==================\n";
    detectCycleDFS();
    return 0;
}