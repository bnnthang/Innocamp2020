#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<pair<int, int>>> adj, radj;
vector<bool> visited;
vector<int> tout;

void dfs1(int u, int lim) {
    visited[u] = true;
    for (pair<int, int> i : adj[u])
        if (i.second <= lim && !visited[i.first])
            dfs1(i.first, lim);
    tout.push_back(u);
}

int dfs2(int u, int lim) {
    int res = 1;
    // cerr << u << "\n";
    visited[u] = true;
    for (pair<int, int> i : radj[u])
        if (i.second <= lim && !visited[i.first])
            res += dfs2(i.first, lim);
    return res;
}

bool scc(int lim) {
    tout.clear();
    visited.assign(n + 2, false);
    for (int i = 1; i <= n; ++i)
        if (!visited[i]) dfs1(i, lim);
    visited.assign(n + 2, false);
    int comp = dfs2(tout.back(), lim);
    return comp == n;
}

int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    cin >> n;
    adj.resize(n + 2);
    radj.resize(n + 2);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int w;
            cin >> w;
            if (i == j) continue;
            adj[i].emplace_back(j, w);
            radj[j].emplace_back(i, w);
        }
    int l = 0, r = 1e9, ans;
    while (l <= r) {
        int m = (l + r) / 2;
        if (scc(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    // if (ans < 0) return 1;
    cout << ans;
    // cout << scc(10);
    return 0;
}