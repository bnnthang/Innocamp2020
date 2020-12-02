#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 2, K = 16;

int n, depth[N], parent[N][K], weight[N][K];
vector<pair<int, int>> adj[N];

void DFS(int u) {
    for (int i = 1; i < K; ++i)
        if (parent[u][i - 1] > 0) {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
            weight[u][i] = min(weight[u][i - 1], weight[parent[u][i - 1]][i - 1]);
            if (parent[u][i] < 1) break;
        }
    for (pair<int, int> i : adj[u]) {
        int v = i.first;
        weight[v][0] = i.second;
        parent[v][0] = u;
        depth[v] = depth[u] + 1;
        DFS(v);
    }
}

bool Bit(int b, int i) {
    return b >> i & 1;
}

// depth[u] >= depth[v]
int LCA(int u, int v) {
    int ans = INT_MAX;
    if (depth[u] < depth[v]) swap(u, v);
    int delta = depth[u] - depth[v];
    for (int i = 0; i < K; ++i) if (Bit(delta, i)) {
        // cerr << "tmp1 = " << weight[u][i] << " i = " << i << "\n";
        ans = min(ans, weight[u][i]);
        u = parent[u][i];
    }
    // cerr << ans << "\n" << "u = " << u << "; v = " << v << "\n";
    if (u == v) return ans;
    for (int i = K - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            ans = min(ans, min(weight[u][i], weight[v][i]));
            // cerr << "tmp2 = " << min(weight[u][i], weight[v][i]) << "\n";
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    ans = min(ans, min(weight[u][0], weight[v][0]));
    return ans;
}

int main() {
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(i, y);
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