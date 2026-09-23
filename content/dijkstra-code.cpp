// Dijkstra 完整代码：打印 dist 与前驱
#include <iostream>
using namespace std;

const int N = 5;
const int INF = 1e9;

int g[N][N] = {
    {0, 2, 5, INF, INF},
    {INF, 0, 1, 4, INF},
    {INF, INF, 0, 1, 3},
    {INF, INF, INF, 0, 1},
    {INF, INF, INF, INF, 0}
};

char name(int i) { return char('A' + i); }

void print_dist(const int dist[]) {
    cout << "dist:";
    for (int i = 0; i < N; i++) {
        cout << " " << name(i) << "=";
        if (dist[i] >= INF) cout << "INF";
        else cout << dist[i];
    }
    cout << "\n";
}

void print_prev(const int prev[]) {
    cout << "prev:";
    for (int i = 0; i < N; i++) {
        cout << " " << name(i) << "<-";
        if (prev[i] < 0) cout << "-";
        else cout << name(prev[i]);
    }
    cout << "\n";
}

int main() {
    int dist[N], prev[N];
    bool done[N] = {false};
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[0] = 0;

    print_dist(dist);
    for (int step = 0; step < N; step++) {
        int u = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && (u < 0 || dist[i] < dist[u])) u = i;
        }
        if (u < 0 || dist[u] >= INF) {
            cout << "error\n";
            return 0;
        }
        done[u] = true;
        cout << "settle " << name(u) << "\n";
        for (int v = 0; v < N; v++) {
            if (!done[v] && g[u][v] < INF && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
                prev[v] = u;
                cout << "relax " << name(v) << "=" << dist[v]
                     << " via " << name(u) << "\n";
            }
        }
        print_dist(dist);
    }
    print_prev(prev);
    return 0;
}
