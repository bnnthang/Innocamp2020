#include <bits/stdc++.h>

using namespace std;

const int N = 3002;

int n, m, lab[N], node[N], deg[N];
bool used[N];
vector<int> adj[N], radj[N];
vector<pair<int, int>> e;
stack<int> topo;

void dfs1(int u) {
    used[u] = true;
    for (int v : adj[u]) if (!used[v]) dfs1(v);
    topo.push(u);
}

void dfs2(int u, int x) {
    lab[u] = x;
    node[x] = u;
    for (int v : radj[u]) if (lab[v] == 0) dfs2(v, x);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        e.emplace_back(u, v);
    }
    for (int i = 1; i <= n; ++i) if (!used[i]) dfs1(i);
    int comp = 0;
    while (!topo.empty()) {
        if (lab[topo.top()] == 0) dfs2(topo.top(), ++comp);
        topo.pop();
    }
    for (pair<int, int> i : e) {
        if (lab[i.first] == lab[i.second]) continue;
        ++deg[lab[i.first]];
    }
    vector<int> stations;
    for (int i = 1; i <= comp; ++i)
        if (deg[i] == 0) {
            stations.push_back(node[i]);
        }
    cout << stations.size() << "\n";
    for (int i : stations) cout << i << " ";
    return 0;
}