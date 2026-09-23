// Dijkstra 思想演示：源点 A，逐步确定最短路
#include <iostream>
using namespace std;

const int N = 5;
const int INF = 1e9;

// A->B2 A->C5 B->C1 B->D4 C->D1 C->E3 D->E1
int g[N][N] = {
    {0, 2, 5, INF, INF},
    {INF, 0, 1, 4, INF},
    {INF, INF, 0, 1, 3},
    {INF, INF, INF, 0, 1},
    {INF, INF, INF, INF, 0}
};

char name(int i) { return char('A' + i); }

int main() {
    int dist[N];
    bool done[N] = {false};
    for (int i = 0; i < N; i++) dist[i] = INF;
    dist[0] = 0;

    cout << "why no negative: greed locks a node forever\n";
    cout << "settle order:";
    for (int step = 0; step < N; step++) {
        int u = -1;
        for (int i = 0; i < N; i++) {
            if (!done[i] && (u < 0 || dist[i] < dist[u])) u = i;
        }
        if (u < 0 || dist[u] >= INF) {
            cout << "\nerror\n";
            return 0;
        }
        done[u] = true;
        cout << " " << name(u);
        for (int v = 0; v < N; v++) {
            if (!done[v] && g[u][v] < INF && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
            }
        }
    }
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << name(i) << ":" << dist[i] << "\n";
    }
    return 0;
}
