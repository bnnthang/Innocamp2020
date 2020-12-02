#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2, K = 18;

int n, depth[N], parent[N][K];
vector<int> adj[N];

void DFS(int u) {
    for (int i = 1; i < K; ++i)
        if (parent[u][i - 1] > 0) {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
            if (parent[u][i] < 1) break;
        }
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
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
    // cerr << "delta = " << delta << endl;
    for (int i = 0; i < K; ++i) if (Bit(delta, i)) {
        // cerr << u << "\n";
        u = parent[u][i];
    }
    // cerr << u << "\n";
    if (u == v) return u;
    for (int i = K - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int main() {
    cin >> n;
    // cout << n << endl;
    for (int i = 2; i <= n; ++i) {
        cin >> parent[i][0];
        adj[parent[i][0]].push_back(i);
    }
    DFS(1);
    int m;
    cin >> m;
    while (m > 0) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << "\n";
        --m;
    }
    return 0;
}