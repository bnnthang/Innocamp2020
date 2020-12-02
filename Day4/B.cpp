#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<bool> used;
vector<vector<int>> adj;
vector<int> topo;
set<pair<int, int>> e;

void TopoSort(int u) {
    used[u] = true;
    for (int v : adj[u]) {
        if (!used[v]) TopoSort(v);
    }
    topo.push_back(u);
}

int main() {
    cin >> n >> m;
    adj.resize(n + 2);
    used.resize(n + 2, false);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        e.emplace(u, v);
    }
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            TopoSort(i);
    for (int i = 0; i < topo.size() - 1; ++i)
        if (e.find({topo[i + 1], topo[i]}) == e.end()) {
            cout << "NO\n";
            return 0;
        }
    cout << "YES\n";
    return 0;
}