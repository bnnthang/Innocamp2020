#include <bits/stdc++.h>

using namespace std;

const int N = 10002;

int n, m;
vector<pair<int, int>> e;
vector<vector<int>> adj, radj;
vector<int> tout, comp;
vector<bool> visited;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs1(v);
    tout.push_back(u);
}

void dfs2(int u, int x) {
    visited[u] = true;
    comp[u] = x;
    for (int v : radj[u]) if (!visited[v]) dfs2(v, x);
}

int main() {
    cin >> n >> m;
    adj.resize(n + 2);
    radj.resize(n + 2);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        e.emplace_back(u, v);
    }
    visited.resize(n + 2, false);
    for (int i = 1; i <= n; ++i) if (!visited[i]) dfs1(i);
    visited.assign(n + 2, false);
    comp.resize(n + 2);
    reverse(tout.begin(), tout.end());
    int ccomp = 0;
    for (int i : tout)
        if (!visited[i]) {
            // cout << "ok\n";
            dfs2(i, ++ccomp);
            // cout << "\n";
        }
    set<pair<int, int>> ans;
    ans.clear();
    for (pair<int, int> i : e)
        if (comp[i.first] != comp[i.second])
            ans.emplace(comp[i.first], comp[i.second]);
    // for (pair<int, int> i : ans) cout << i.first << " " << i.second << "\n";
    cout << ans.size() << "\n";
    return 0;
}