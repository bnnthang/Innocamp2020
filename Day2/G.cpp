#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 2;

int n, q, a[N], app[N], fen[N];
vector<int> val, ans;
vector<pair<int, int>> queries[N];

void mod(int p, int x) {
    for (; p <= n; p += p & -p) {
        fen[p] += x;
    }
}

int psum(int p) {
    int res = 0;
    for (; p; p -= p & -p) {
        res += fen[p];
    }
    return res;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        val.push_back(a[i]);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    }
    cin >> q;
    ans.resize(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        queries[r].emplace_back(l, i);
    }
    for (int i = 1; i <= n; ++i) {
        if (app[a[i]] > 0) {
            mod(app[a[i]], -1);
        }
        app[a[i]] = i;
        mod(app[a[i]], 1);
        for (pair<int, int> j : queries[i]) {
            ans[j.second] = psum(i) - psum(j.first - 1);
        }
    }
    for (int i : ans) cout << i << "\n";
    return 0;
}