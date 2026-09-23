// Disjoint set: union by rank + path compression.
// Elements 1..6; unions 1-2, 3-4, 2-4, 5-6; then find(1).
#include <iostream>
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n + 1), r(n + 1, 0) {
        for (int i = 0; i <= n; ++i) p[i] = i;
    }

    int find(int x) {
        if (x < 0 || x >= (int)p.size()) {
            cout << "error\n";
            return -1;
        }
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra < 0 || rb < 0) return false;
        if (ra == rb) return false;
        if (r[ra] < r[rb]) {
            p[ra] = rb;
        } else if (r[ra] > r[rb]) {
            p[rb] = ra;
        } else {
            p[rb] = ra;
            r[ra]++;
        }
        return true;
    }
};

int main() {
    DSU d(6);
    int ops[][2] = {{1, 2}, {3, 4}, {2, 4}, {5, 6}};
    for (auto& op : ops) {
        d.unite(op[0], op[1]);
        cout << "union " << op[0] << "-" << op[1] << "\n";
    }

    cout << "parent before find:";
    for (int i = 1; i <= 6; ++i) cout << " " << d.p[i];
    cout << "\n";

    // 4 -> 3 -> 1; find(4) compresses, root of 1's set stays 1
    cout << "find(4)=" << d.find(4) << "\n";
    cout << "find(1)=" << d.find(1) << "\n";

    cout << "parent after find:";
    for (int i = 1; i <= 6; ++i) cout << " " << d.p[i];
    cout << "\n";

    cout << "roots:";
    for (int i = 1; i <= 6; ++i) cout << " " << d.find(i);
    cout << "\n";

    cout << "components:\n";
    vector<bool> seen(7, false);
    for (int i = 1; i <= 6; ++i) {
        int rt = d.find(i);
        if (seen[rt]) continue;
        seen[rt] = true;
        cout << "  {";
        bool first = true;
        for (int j = 1; j <= 6; ++j) {
            if (d.find(j) == rt) {
                if (!first) cout << ",";
                cout << j;
                first = false;
            }
        }
        cout << "}\n";
    }
    return 0;
}
