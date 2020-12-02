#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<bool> used, instack;
vector<vector<int>> adj;
vector<int> topo, indeg;

void TopoSort(int u) {
    used[u] = true;
    instack[u] = true;
    for (int v : adj[u]) {
        if (instack[v]) {
            cout << "-1\n";
            exit(0);
        }
        if (!used[v]) TopoSort(v);
    }
    topo.push_back(u);
    instack[u] = false;
}

int main() {
    cin >> n >> m;
    adj.resize(n + 2);
    used.resize(n + 2, false);
    instack.resize(n + 2), false;
    indeg.resize(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ++indeg[v];
    }
    for (int i = 1; i <= n; ++i)
        if (!used[i])
            TopoSort(i);
    if (!topo.size())
        cout << "-1\n";
    else {
        reverse(topo.begin(), topo.end());
        for (int i : topo) cout << i << " ";
    }
    return 0;
}