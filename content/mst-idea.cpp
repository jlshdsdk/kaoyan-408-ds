// Prim 与 Kruskal 同图演示，打印选中边与总权
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};
const int INF = 1e9;

struct Edge {
    int u, v, w;
};

void prim() {
    // 邻接矩阵，无边为 INF
    int g[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) g[i][j] = (i == j ? 0 : INF);
    int ew[][3] = {
        {0, 1, 2}, {0, 2, 6}, {1, 2, 3}, {1, 3, 5},
        {2, 3, 1}, {2, 4, 4}, {3, 4, 2}
    };
    for (int i = 0; i < 7; i++) {
        int u = ew[i][0], v = ew[i][1], w = ew[i][2];
        g[u][v] = g[v][u] = w;
    }

    bool in[N] = {};
    int low[N], pre[N];
    for (int i = 0; i < N; i++) {
        low[i] = INF;
        pre[i] = -1;
    }
    low[0] = 0;
    int total = 0;
    cout << "Prim from A\n";
    for (int k = 0; k < N; k++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!in[i] && (u < 0 || low[i] < low[u])) u = i;
        if (u < 0 || low[u] >= INF) {
            cout << "error\n";
            return;
        }
        in[u] = true;
        if (pre[u] >= 0) {
            cout << "pick " << name[pre[u]] << name[u] << " w=" << low[u] << "\n";
            total += low[u];
        }
        for (int v = 0; v < N; v++) {
            if (!in[v] && g[u][v] < low[v]) {
                low[v] = g[u][v];
                pre[v] = u;
            }
        }
    }
    cout << "Prim total=" << total << "\n";
}

int findp(vector<int>& p, int x) {
    return p[x] == x ? x : p[x] = findp(p, p[x]);
}

void kruskal() {
    vector<Edge> es = {
        {0, 1, 2}, {0, 2, 6}, {1, 2, 3}, {1, 3, 5},
        {2, 3, 1}, {2, 4, 4}, {3, 4, 2}
    };
    sort(es.begin(), es.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    vector<int> p(N);
    for (int i = 0; i < N; i++) p[i] = i;
    int total = 0, cnt = 0;
    cout << "Kruskal\n";
    for (const Edge& e : es) {
        int fu = findp(p, e.u), fv = findp(p, e.v);
        if (fu == fv) {
            cout << "skip " << name[e.u] << name[e.v] << " w=" << e.w << "\n";
            continue;
        }
        p[fu] = fv;
        cout << "pick " << name[e.u] << name[e.v] << " w=" << e.w << "\n";
        total += e.w;
        if (++cnt == N - 1) break;
    }
    cout << "Kruskal total=" << total << "\n";
}

int main() {
    prim();
    kruskal();
    return 0;
}
