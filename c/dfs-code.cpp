// 有向图 DFS 完整递归：打印入栈/出栈与访问序
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};
bool vis[N];

void dfs(int u, vector<int> adj[N]) {
    vis[u] = true;
    cout << "enter " << name[u] << "\n";
    cout << "visit " << name[u] << "\n";
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v, adj);
        } else {
            cout << "skip " << name[v] << "\n";
        }
    }
    cout << "leave " << name[u] << "\n";
}

int main() {
    vector<int> adj[N];
    adj[0] = {1, 2};  // A -> B, C
    adj[1] = {3};     // B -> D
    adj[2] = {3, 4};  // C -> D, E
    adj[3] = {};
    adj[4] = {};

    cout << "DFS from A\n";
    for (int i = 0; i < N; i++) vis[i] = false;
    dfs(0, adj);
    cout << "order: A B D C E\n";
    return 0;
}
