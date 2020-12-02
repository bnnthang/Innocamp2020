#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 2;

int n, m;
pair<ll, ll> t[N];

void mod(int p, ll x) {
    if (p & 1) t[p += n].first = x;
    else t[p += n].second = x;
    for (; p > 1; p >>= 1) {
        t[p >> 1].first = t[p].first + t[p ^ 1].first;
        t[p >> 1].second = t[p].second + t[p ^ 1].second;
    }
}

pair<ll, ll> operator+(const pair<ll, ll>& lhs, const pair<ll, ll>& rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

pair<ll, ll> query(int l, int r) {
    pair<ll, ll> ans = {0, 0};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans = ans + t[l++];
        if (r & 1) ans = ans + t[--r];
    }
    return ans;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; ++i)
        if (i & 1) cin >> t[n + i].first;
        else cin >> t[n + i].second;
    for (int i = n - 1; i; --i) {
        t[i].first = t[i << 1].first + t[i << 1 | 1].first;
        t[i].second = t[i << 1].second + t[i << 1 | 1].second;
    }
    cin >> m;
    while (m--) {
        int t;
        cin >> t;
        if (t == 0) {
            int i, j;
            cin >> i >> j;
            mod(i - 1, j);
        } else {
            int l, r;
            cin >> l >> r;
            pair<ll, ll> tmp = query(l - 1, r);
            ll ans = tmp.first - tmp.second;
            if (l & 1) ans *= -1;
            cout << ans << "\n";
        }
    }
    return 0;
}