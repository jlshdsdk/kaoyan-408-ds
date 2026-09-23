// 拓扑排序思想：入度 + 队列（Kahn）
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int N = 6;  // A..F

char name(int i) { return char('A' + i); }

int main() {
    // A->B A->C B->D C->D C->E D->F E->F
    vector<int> adj[N];
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(5);

    int indeg[N] = {0};
    for (int u = 0; u < N; u++) {
        for (size_t i = 0; i < adj[u].size(); i++) indeg[adj[u][i]]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    cout << "order:";
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << " " << name(u);
        cnt++;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    cout << "\n";
    if (cnt != N) cout << "error cycle\n";
    return 0;
}
