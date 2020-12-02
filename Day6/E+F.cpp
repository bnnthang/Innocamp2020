#include <bits/stdc++.h>

using namespace std;

const long long MOD = (1 << 30) + 1;

int n, m;
// vector<vector<vector<int>>> f;
vector<long long> f1[2];

bool Bit(int b, int i) {
    return b >> i & 1;
}

bool Skip(int x1, int x2, int x3, int x4) {
    return x1 + x2 + x3 + x4 == 0 || x1 + x2 + x3 + x4 == 4;
}

// void Print() {
//     for (int i = 1; i < m; ++i) {
//         for (int j = 0; j < n; ++j) {
//             for (int mk = 0; mk < 1 << (n + 1); ++mk) {
//                 cout << i << " " << j << " " << bitset<4>(mk) << " = " <<  f[i][j][mk] << endl;
//             }
//         }
//     }
// }

int main() {
    cin >> n >> m;
    if (n > m) swap(n, m);
    if (n == 1) {
        long long ans = 1;
        for (int i = 0; i < m; ++i) (ans *= 2) %= MOD;
        cout << ans << "\n";
        return 0;
    }
    // f.resize(m + 1, vector<vector<int>>(n, vector<int>(1 << (n + 1), 0)));
    // f[1][0].assign(1 << (n + 1), 1);
    bool flag = false;
    f1[0].assign(1 << (n + 1), 1);
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            f1[flag ^ 1].assign(1 << (n + 1), 0);
            for (int mk = 0; mk < 1 << (n + 1); ++mk) {
                if (j < n - 1) {
                    int x1 = Bit(mk, n), x2 = Bit(mk, j), x3 = Bit(mk, j + 1);
                    for (int x4 = 0; x4 < 2; ++x4)
                        if (!Skip(x1, x2, x3, x4)) {
                            int new_mk = mk ^ ((x1 ^ x2) << j) ^ ((x1 ^ x4) << n);
                            // (f[i][j + 1][new_mk] += f[i][j][mk]) %= MOD;
                            (f1[flag ^ 1][new_mk] += f1[flag][mk]) %= MOD;
                        }
                } else {
                    int x1 = Bit(mk, n), x2 = Bit(mk, n - 1);
                    for (int x4 = 0; x4 < 2; ++x4) {
                        int new_mk = mk ^ ((x1 ^ x2) << (n - 1)) ^ ((x1 ^ x4) << n);
                        // (f[i + 1][0][new_mk] += f[i][j][mk]) %= MOD;
                        (f1[flag ^ 1][new_mk] += f1[flag][mk]) %= MOD;
                    }
                }
            }
            flag ^= 1;
        }
    }
    // Print();
    // int ans = accumulate(f[m - 1][n - 1].begin(), f[m - 1][n - 1].end(), 0LL) % MOD;
    long long ans = accumulate(f1[flag ^ 1].begin(), f1[flag ^ 1].end(), 0LL) % MOD;
    cout << ans << "\n";
    return 0;
}