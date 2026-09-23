// 图：定义、术语、性质；统计无向图各顶点的度
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};

// 无向边：AB BC AC CD DE
void build(vector<int> adj[N]) {
    int edges[][2] = {{0, 1}, {1, 2}, {0, 2}, {2, 3}, {3, 4}};
    for (int i = 0; i < 5; i++) {
        int u = edges[i][0], v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int main() {
    vector<int> adj[N];
    build(adj);

    cout << "V={A,B,C,D,E} E={AB,BC,AC,CD,DE}\n";
    cout << "degrees:";
    int sum = 0;
    for (int i = 0; i < N; i++) {
        int d = (int)adj[i].size();
        sum += d;
        cout << " " << name[i] << "=" << d;
    }
    cout << "\n";
    // 握手定理：度数和 = 2|E|
    cout << "sum=" << sum << " = 2*|E|\n";
    cout << "connected=yes sparse=yes\n";
    return 0;
}
