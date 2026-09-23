// Prim 算法：从 A 生长，打印 lowcost 变化与选边
#include <iostream>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};
const int INF = 1e9;

void print_low(const int low[], const bool in[]) {
    cout << "lowcost:";
    for (int i = 0; i < N; i++) {
        cout << " " << name[i] << "=";
        if (in[i]) cout << "-";
        else if (low[i] >= INF) cout << "INF";
        else cout << low[i];
    }
    cout << "\n";
}

int main() {
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
    for (int step = 0; step < N; step++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!in[i] && (u < 0 || low[i] < low[u])) u = i;
        if (u < 0 || low[u] >= INF) {
            cout << "error\n";
            return 0;
        }
        in[u] = true;
        if (pre[u] >= 0) {
            cout << "pick " << name[pre[u]] << "-" << name[u]
                 << " w=" << low[u] << "\n";
            total += low[u];
        } else {
            cout << "start " << name[u] << "\n";
        }
        for (int v = 0; v < N; v++) {
            if (!in[v] && g[u][v] < low[v]) {
                low[v] = g[u][v];
                pre[v] = u;
            }
        }
        print_low(low, in);
    }
    cout << "edges AB BC CD DE\n";
    cout << "total=" << total << "\n";
    return 0;
}
