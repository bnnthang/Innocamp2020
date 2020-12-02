#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 2;

int n;
ll t[N];

void mod(int p, ll x) {
    for (t[p += n] = x; p > 1; p >>= 1)
        t[p >> 1] = t[p] + t[p ^ 1];
}

ll sum(int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t[l++];
        if (r & 1) res += t[--r];
    }
    return res;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> t[i + n];
    for (int i = n - 1; i; --i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    string cmd;
    while (cin >> cmd) {
        if (cmd == "set") {
            int p;
            ll x;
            cin >> p >> x;
            mod(p - 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sum(l - 1, r) << "\n";
        }
    }
    return 0;
}