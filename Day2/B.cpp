#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 2;

int n, t[N];

void mod(int p, int x) {
    for (t[p += n] = x; p > 1; p >>= 1)
        t[p >> 1] = min(t[p], t[p ^ 1]);
}

int query(int l, int r) {
    int res = INT_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, t[l++]);
        if (r & 1) res = min(res, t[--r]);
    }
    return res;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    fill(t, t + N, INT_MAX);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> t[n + i];
    for (int i = n - 1; i > 0; --i)
        t[i] = min(t[i << 1], t[i << 1 | 1]);
    string cmd;
    while (cin >> cmd) {
        if (cmd == "min") {
            int l, r;
            cin >> l >> r;
            int res = query(l - 1, r);
            cout << res << "\n";
        } else {
            int p, x;
            cin >> p >> x;
            mod(p - 1, x);
        }
    }
    return 0;
}