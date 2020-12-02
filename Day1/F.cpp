#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2, K = 17;

int n, depth[N], parent[N][K], weight[N][K];
vector<pair<int, int>> edges, adj[N];

void DFS(int u) {
    for (int i = 1; i < K; ++i) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
        weight[u][i] = weight[u][i - 1] + weight[parent[u][i - 1]][i - 1];
        if (parent[u][i] < 1) break;
    }
    for (pair<int, int> i : adj[u]) {
        int v = i.first;
        if (v == parent[u][0]) continue;
        depth[v] = depth[u] + 1;
        parent[v][0] = u;
        weight[v][0] = edges[i.second].first == u; // 1 for down and 0 for up
        DFS(v);
    }
}

bool Bit(int b, int i) {
    return b >> i & 1;
}

// depth[u] >= depth[v]
int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int delta = depth[u] - depth[v];
    for (int i = 0; i < K; ++i) if (Bit(delta, i)) {
        u = parent[u][i];
    }
    if (u == v) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

// parent u to child v
int Sum(int u, int v) {
    int delta = depth[v] - depth[u];
    int ans = 0;
    for (int i = 0; i < K; ++i) if (Bit(delta, i)) {
        ans += weight[v][i];
        v = parent[v][i];
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    DFS(1);
    int m;
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        int w1 = Sum(lca, u), w2 = Sum(lca, v);
        if (w1 == 0 && w2 == depth[v] - depth[lca]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}