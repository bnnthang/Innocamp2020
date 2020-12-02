#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

int n, m;
vector<int> grundy, deg;
vector<vector<int>> adj, radj;
queue<int> q;

int main() {
    cin >> n >> m;
    adj.resize(n);
    radj.resize(n);
    deg.resize(n, 0);
    grundy.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
        radj[v].push_back(u);
        ++deg[u];
    }
    for (int i = 0; i < n; ++i) if (sz(adj[i]) < 1) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        sort(adj[u].begin(), adj[u].end(), [&](int x, int y) { return grundy[x] < grundy[y]; });
        for (int v : adj[u]) if (grundy[u] == grundy[v]) ++grundy[u];
        for (int v : radj[u]) if ((--deg[v]) == 0) q.push(v);
    }
    for (int i : grundy) cout << i << " ";
    return 0;
}