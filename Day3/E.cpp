#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;
using ll = long long;

const ll BASE = 31, MOD = 1677633767;

string s;
vector<ll> hsh, pw;

void Build() {
    hsh.assign(sz(s) + 2, 0);
    pw.assign(sz(s) + 2, 0);
    pw[0] = 1;
    for (int i = 1; i <= sz(s); ++i) {
        hsh[i] = (hsh[i - 1] * BASE + s[i - 1] - 'a' + 1) % MOD;
        pw[i] = pw[i - 1] * BASE % MOD;
    }
}

ll Get(int l, int r) {
    return ((hsh[r] - hsh[l - 1] * pw[r - l + 1]) % MOD + MOD) % MOD;
}

int main() {
    cin >> s;
    Build();
    int m;
    cin >> m;
    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (b - a == d - c && Get(a, b) == Get(c, d)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}