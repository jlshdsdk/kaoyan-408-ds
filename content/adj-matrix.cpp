// 邻接矩阵存储无向图，打印 0/1 矩阵
#include <iostream>
using namespace std;

const int N = 5;
const char* name[N] = {"A", "B", "C", "D", "E"};

int main() {
    int g[N][N] = {};
    // 无向边 AB BC AC CD DE，对称位置都置 1
    int edges[][2] = {{0, 1}, {1, 2}, {0, 2}, {2, 3}, {3, 4}};
    for (int i = 0; i < 5; i++) {
        int u = edges[i][0], v = edges[i][1];
        g[u][v] = g[v][u] = 1;
    }

    cout << "  ";
    for (int j = 0; j < N; j++) cout << name[j] << (j + 1 < N ? " " : "\n");
    for (int i = 0; i < N; i++) {
        cout << name[i] << " ";
        for (int j = 0; j < N; j++) {
            cout << g[i][j] << (j + 1 < N ? " " : "\n");
        }
    }
    return 0;
}
