// 邻接表存储无向图：每条无向边存两次
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};

int main() {
    vector<int> adj[N];
    int edges[][2] = {{0, 1}, {1, 2}, {0, 2}, {2, 3}, {3, 4}};
    for (int i = 0; i < 5; i++) {
        int u = edges[i][0], v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);  // undirected: store both ways
    }

    for (int i = 0; i < N; i++) {
        cout << name[i] << ":";
        for (int v : adj[i]) cout << " " << name[v];
        cout << "\n";
    }
    return 0;
}
