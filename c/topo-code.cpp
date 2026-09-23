// Kahn 拓扑排序完整代码：打印入度变化，可发现环
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 16;

char name(int i) { return char('A' + i); }

bool kahn(const vector<int> adj[], int n, bool verbose) {
    int indeg[MAXN] = {0};
    for (int u = 0; u < n; u++) {
        for (size_t i = 0; i < adj[u].size(); i++) indeg[adj[u][i]]++;
    }
    if (verbose) {
        cout << "indeg:";
        for (int i = 0; i < n; i++) cout << " " << name(i) << "=" << indeg[i];
        cout << "\n";
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    int cnt = 0;
    cout << "order:";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << " " << name(u);
        cnt++;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            indeg[v]--;
            if (verbose) {
                cout << "\n  after " << name(u) << "->" << name(v)
                     << " indeg(" << name(v) << ")=" << indeg[v];
            }
            if (indeg[v] == 0) q.push(v);
        }
    }
    cout << "\n";
    if (cnt != n) {
        cout << "cycle detected\n";
        return false;
    }
    cout << "ok acyclic\n";
    return true;
}

int main() {
    // DAG: A->B A->C B->D C->D C->E D->F E->F
    const int n = 6;
    vector<int> dag[MAXN];
    dag[0].push_back(1);
    dag[0].push_back(2);
    dag[1].push_back(3);
    dag[2].push_back(3);
    dag[2].push_back(4);
    dag[3].push_back(5);
    dag[4].push_back(5);

    cout << "=== DAG ===\n";
    kahn(dag, n, true);

    // same nodes plus F->C to make a cycle
    vector<int> cyc[MAXN];
    for (int u = 0; u < n; u++) cyc[u] = dag[u];
    cyc[5].push_back(2);

    cout << "=== with cycle F->C ===\n";
    kahn(cyc, n, false);
    return 0;
}
