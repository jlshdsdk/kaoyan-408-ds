// Kruskal：边按权排序，并查集跳过成环边
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5;  // A..E
const int M = 7;

struct Edge {
    int u, v, w;
};

int parent[N];

void dsu_init() {
    for (int i = 0; i < N; i++) parent[i] = i;
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return false;
    parent[ra] = rb;
    return true;
}

bool cmp(const Edge& a, const Edge& b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

char name(int i) { return char('A' + i); }

int main() {
    // AB2 AC6 BC3 BD5 CD1 CE4 DE2
    Edge edges[M] = {
        {0, 1, 2}, {0, 2, 6}, {1, 2, 3}, {1, 3, 5},
        {2, 3, 1}, {2, 4, 4}, {3, 4, 2}
    };
    sort(edges, edges + M, cmp);
    dsu_init();

    cout << "sorted:";
    for (int i = 0; i < M; i++) {
        cout << " " << name(edges[i].u) << name(edges[i].v)
             << edges[i].w;
    }
    cout << "\n";

    int taken = 0;
    int total = 0;
    for (int i = 0; i < M; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (unite(u, v)) {
            cout << "accept " << name(u) << "-" << name(v)
                 << " " << w << "\n";
            taken++;
            total += w;
        } else {
            cout << "reject " << name(u) << "-" << name(v)
                 << " " << w << "\n";
        }
    }
    cout << "mst weight=" << total << " edges=" << taken << "\n";
    return 0;
}
