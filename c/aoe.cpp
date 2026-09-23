// AOE 网：事件最早/最迟时间与关键路径
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 6;  // A..F
const int INF = 1e9;

struct Act {
    int u, v, w;
};

char name(int i) { return char('A' + i); }

int main() {
    // activities on edges
    Act acts[] = {
        {0, 1, 3}, {0, 2, 2}, {1, 3, 4}, {2, 3, 1},
        {2, 4, 6}, {3, 4, 2}, {3, 5, 5}, {4, 5, 1}
    };
    const int M = 8;

    vector<int> adj[N];
    int indeg[N] = {0};
    for (int i = 0; i < M; i++) {
        adj[acts[i].u].push_back(i);
        indeg[acts[i].v]++;
    }

    // topological order from source A=0
    int order[N];
    int oc = 0;
    int deg[N];
    for (int i = 0; i < N; i++) deg[i] = indeg[i];
    int q[N], qh = 0, qt = 0;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) q[qt++] = i;
    }
    while (qh < qt) {
        int u = q[qh++];
        order[oc++] = u;
        for (size_t k = 0; k < adj[u].size(); k++) {
            int ei = adj[u][k];
            int v = acts[ei].v;
            if (--deg[v] == 0) q[qt++] = v;
        }
    }
    if (oc != N) {
        cout << "error\n";
        return 0;
    }

    int ve[N], vl[N];
    for (int i = 0; i < N; i++) {
        ve[i] = 0;
        vl[i] = INF;
    }
    // earliest event time
    for (int t = 0; t < N; t++) {
        int u = order[t];
        for (size_t k = 0; k < adj[u].size(); k++) {
            int ei = adj[u][k];
            int v = acts[ei].v;
            int w = acts[ei].w;
            ve[v] = max(ve[v], ve[u] + w);
        }
    }
    vl[N - 1] = ve[N - 1];  // sink F
    for (int t = N - 1; t >= 0; t--) {
        int u = order[t];
        for (size_t k = 0; k < adj[u].size(); k++) {
            int ei = adj[u][k];
            int v = acts[ei].v;
            int w = acts[ei].w;
            vl[u] = min(vl[u], vl[v] - w);
        }
        if (vl[u] >= INF) vl[u] = ve[u];
    }

    cout << "ve:";
    for (int i = 0; i < N; i++) cout << " " << name(i) << "=" << ve[i];
    cout << "\nvl:";
    for (int i = 0; i < N; i++) cout << " " << name(i) << "=" << vl[i];
    cout << "\n";

    cout << "critical edges:";
    int crit_len = ve[N - 1];
    for (int i = 0; i < M; i++) {
        int u = acts[i].u, v = acts[i].v, w = acts[i].w;
        int e = ve[u];
        int l = vl[v] - w;
        if (e == l) {
            cout << " " << name(u) << name(v) << "(" << w << ")";
        }
    }
    cout << "\ncritical path length=" << crit_len << "\n";
    return 0;
}
