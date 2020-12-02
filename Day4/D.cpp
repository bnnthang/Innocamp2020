#include <bits/stdc++.h>

using namespace std;

const int N = 10002;

int n, m, t[N], f[N], indeg[N];
bool used[N];
vector<int> adj[N], topo;

void TopoSort(int u) {
    used[u] = true;
    for (int v : adj[u]) {
        if (!used[v]) TopoSort(v);
    }
    topo.push_back(u);
}

void Traverse(int u) {
    for (int v : adj[u]) {
        f[v] = max(f[v], f[u] + t[u]);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> t[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ++indeg[v];
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) TopoSort(i);
        if (!indeg[i]) f[i] = 0;
        else f[i] = INT_MIN;
    }
    reverse(topo.begin(), topo.end());
    int ans = INT_MIN;
    for (int u : topo) {
        for (int v : adj[u]) {
            f[v] = max(f[v], f[u] + t[u]);
        }
        if (!adj[u].size()) {
            ans = max(ans, f[u] + t[u]);
        }
    }
    cout << ans << "\n";
    return 0;
}