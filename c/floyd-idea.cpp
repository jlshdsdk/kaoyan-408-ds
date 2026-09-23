// Floyd 思想：三重循环 k,i,j 松弛
#include <iostream>
using namespace std;

const int N = 4;
const int INF = 1e9;

int main() {
    // edges 0->1:3 0->2:8 1->2:2 1->3:5 2->3:1
    int d[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) d[i][j] = (i == j) ? 0 : INF;
    }
    d[0][1] = 3;
    d[0][2] = 8;
    d[1][2] = 2;
    d[1][3] = 5;
    d[2][3] = 1;

    cout << "init d[0][3]=";
    if (d[0][3] >= INF) cout << "INF\n";
    else cout << d[0][3] << "\n";

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (d[i][k] < INF && d[k][j] < INF &&
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
        cout << "after k=" << k << " d[0][3]=" << d[0][3] << "\n";
    }
    cout << "path 0-1-2-3 = 3+2+1 = " << d[0][3] << "\n";
    return 0;
}
