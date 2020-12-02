#include <bits/stdc++.h>

using namespace std;

int n, w[13][13], f[1 << 13][13], pre[1 << 13][13];

bool GetBit(int b, int i) {
    return b >> i & 1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> w[i][j];
    for (int m = 1; m < 1 << n; ++m) {
        if (__builtin_popcount(m) < 2) continue;
        for (int i = 0; i < n; ++i) if (GetBit(m, i)) {
            f[m][i] = INT_MAX;
            for (int j = 0; j < n; ++j) if (GetBit(m, j) && i != j) {
                int tmp = f[m ^ (1 << i)][j] + w[i][j];
                if (f[m][i] > tmp) {
                    f[m][i] = tmp;
                    pre[m][i] = j;
                }
            }
        }
    }
    int cur = (1 << n) - 1, curu = 0;
    for (int i = 1; i < n; ++i)
        if (f[cur][i] < f[cur][curu]) curu = i;
    cout << f[cur][curu] << "\n";
    while (cur > 0) {
        cout << (curu + 1) << " ";
        int tmp = pre[cur][curu];
        cur ^= 1 << curu;
        curu = tmp;
    }
    return 0;
}