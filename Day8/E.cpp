#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n;
int m;
vector<ll> a;
map<ll, pair<bool, bool>> f;

void DFS(ll u) {
    f[u] = {false, false};
    for (ll i : a) if (u % i == 0) {
        ll v = u / i;
        if (f.find(v) == f.end()) {
            DFS(v);
        }
        f[u].second = true;
        if (f[v].second) {
            f[u].first |= (f[v].first ^ 1) == (i & 1);
        } else {
            f[u].first = true;
        }
    }
}

int main() {
    cin >> n >> m;
    a.resize(m);
    for (ll& i : a) cin >> i;
    DFS(n);
    cout << (f[n].first ? "First" : "Second");
    return 0;
}