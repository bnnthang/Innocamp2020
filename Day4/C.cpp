#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;
const int oo = 2e9, threshold = 1e9;

int n, m, s, t, dis[N];
bool used[N];
vector<pair<int, int>> adj[N];
vector<int> topo;

void TopoSort(int u) {
    used[u] = true;
    for (pair<int, int> i : adj[u]) if (!used[i.first]) TopoSort(i.first);
    topo.push_back(u);
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    memset(used, false, sizeof(used));
    for (int i = 1; i <= n; ++i)
        if (!used[i]) TopoSort(i);
    reverse(topo.begin(), topo.end());
    fill(dis + 1, dis + n + 1, oo);
    dis[s] = 0;
    for (int u : topo) {
        for (pair<int, int> it : adj[u]) {
            int v = it.first, w = it.second;
            dis[v] = min(dis[v], dis[u] + w);
        }
    }
    if (dis[t] >= threshold) {
        cout << "Unreachable";
    } else {
        cout << dis[t];
    }
    return 0;
}