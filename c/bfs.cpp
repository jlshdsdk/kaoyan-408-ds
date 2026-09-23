// 有向图 BFS：队列层序，从 A 出发
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};

int main() {
    vector<int> adj[N];
    adj[0] = {1, 2};  // A -> B, C
    adj[1] = {3};     // B -> D
    adj[2] = {3, 4};  // C -> D, E
    adj[3] = {};
    adj[4] = {};

    bool vis[N] = {};
    queue<int> q;
    q.push(0);
    vis[0] = true;

    cout << "order:";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << " " << name[u];
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
    return 0;
}
