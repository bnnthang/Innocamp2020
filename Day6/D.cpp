#include <bits/stdc++.h>

using namespace std;

const int N = 20;

int n, w, c[N], sum[1 << N], rides[1 << N], pre[1 << N];

bool Bit(int b, int i) {
    return b >> i & 1;
}

int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);
    cin >> n >> w;
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int m = 1; m < 1 << n; ++m) {
        for (int i = 0; i < n; ++i)
            if (Bit(m, i)) sum[m] += c[i];
    }
    for (int m = 1; m < 1 << n; ++m) {
        rides[m] = INT_MAX - 2;
        for (int sm = m; sm > 0; (--sm) &= m) {
            if (sum[sm] > w) continue;
            if (rides[m] > rides[sm ^ m]) {
                rides[m] = rides[m ^ sm];
                pre[m] = sm;
            }
        }
        ++rides[m];
    }
    int cur = (1 << n) - 1;
    cout << rides[cur] << "\n";
    while (cur > 0) {
        // cout << cur << "\n";
        cout << __builtin_popcount(pre[cur]) << " ";
        for (int i = 0; i < n; ++i)
            if (Bit(pre[cur], i)) cout << (i + 1) << " ";
        cout << "\n";
        cur = cur ^ pre[cur];
    }
    return 0;
}