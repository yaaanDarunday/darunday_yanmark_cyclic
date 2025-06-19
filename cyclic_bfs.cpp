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

bool detectCycleBFS() {
    int inDegree[SIZE] = {0}, queue[SIZE], front = 0, rear = 0, processed = 0;
    
    // Calculate in-degrees
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(graph[i][j]) inDegree[j]++;
    
    // Add vertices with in-degree 0
    for(int i = 0; i < SIZE; i++)
        if(inDegree[i] == 0) queue[rear++] = i;
    
    // Process queue
    while(front < rear) {
        int v = queue[front++];
        processed++;
        for(int u = 0; u < SIZE; u++) {
            if(graph[v][u] && --inDegree[u] == 0)
                queue[rear++] = u;
        }
    }
    
    if(processed != SIZE) {
        cout << "BFS - Cycle detected\n";
        cout << "Vertices in cycle: ";
        bool first = true;
        for(int i = 0; i < SIZE; i++) {
            bool found = false;
            for(int j = 0; j < rear; j++) {
                if(queue[j] == i) { found = true; break; }
            }
            if(!found) {
                if(!first) cout << ", ";
                cout << vertices[i];
                first = false;
            }
        }
        cout << "\n";
        return true;
    }
    
    cout << "BFS - No cycle found\n";
    return false;
}

int main() {
    cout << "BFS Cycle Detection (Kahn's Algorithm)\n";
    cout << "=====================================\n";
    detectCycleBFS();
    return 0;
}