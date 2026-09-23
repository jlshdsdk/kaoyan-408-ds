// Floyd 代码：每次 k 打印距离矩阵
#include <iostream>
using namespace std;

const int N = 4;
const int INF = 1e9;

void print_matrix(const int d[N][N], int k) {
    cout << "k=" << k << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j) cout << " ";
            if (d[i][j] >= INF) cout << "INF";
            else cout << d[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int d[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) d[i][j] = (i == j) ? 0 : INF;
    }
    d[0][1] = 3;
    d[0][2] = 8;
    d[1][2] = 2;
    d[1][3] = 5;
    d[2][3] = 1;

    print_matrix(d, -1);
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (d[i][k] < INF && d[k][j] < INF &&
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
        print_matrix(d, k);
    }
    cout << "d[0][3]=" << d[0][3] << "\n";
    return 0;
}
