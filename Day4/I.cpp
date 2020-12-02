#include <bits/stdc++.h>

using namespace std;

const int REACTIONS[5][4] = {
    {2, 1, 0, 2},
    {1, 1, 1, 1},
    {0, 0, 2, 1},
    {0, 3, 0, 0},
    {1, 0, 0, 1}
};
const int N = 31;

bool f[N][N][N][N];

int main() {
    int n[4];
    memset(f, false, sizeof(f));
    for (n[0] = 0; n[0] < N; ++n[0])
        for (n[1] = 0; n[1] < N; ++n[1])
            for (n[2] = 0; n[2] < N; ++n[2])
                for (n[3] = 0; n[3] < N; ++n[3]) {
                    int p[4];
                    for (int i = 0; i < 5; ++i) {
                        bool flag1 = true;
                        for (int j = 0; j < 4; ++j) {
                            if (n[j] >= REACTIONS[i][j])
                                p[j] = n[j] - REACTIONS[i][j];
                            else {
                                flag1 = false;
                                break;
                            }
                        }
                        if (flag1) {
                            f[n[0]][n[1]][n[2]][n[3]] |= f[p[0]][p[1]][p[2]][p[3]] ^ true;
                        }
                    }
                }
    int test;
    cin >> test;
    while (test--) {
        for (int i = 0; i < 4; ++i) cin >> n[i];
        cout << (f[n[0]][n[1]][n[2]][n[3]] ? "First\n" : "Second\n");
    }
    return 0;
}