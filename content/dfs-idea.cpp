// 有向图 DFS：从 A 出发，邻接点按字母序
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};
bool vis[N];
int stamp;
int tin[N], tout[N];

void dfs(int u, vector<int> adj[N]) {
    vis[u] = true;
    tin[u] = ++stamp;
    cout << name[u] << " ";  // visit order
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v, adj);
    }
    tout[u] = ++stamp;
}

int main() {
    vector<int> adj[N];
    // A->B, A->C, B->D, C->D, C->E  (neighbors already alphabetical)
    adj[0] = {1, 2};
    adj[1] = {3};
    adj[2] = {3, 4};
    adj[3] = {};
    adj[4] = {};

    cout << "order:";
    stamp = 0;
    dfs(0, adj);
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << name[i] << " tin=" << tin[i] << " tout=" << tout[i] << "\n";
    }
    return 0;
}
