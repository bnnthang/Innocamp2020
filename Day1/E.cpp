#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 2, K = 19;

struct IT {
    struct Node {
        int il, ir;
        long long sum = 0;
    } a[N << 2];

#define nx (i << 1)
#define md ((l + r) >> 1)
    void Build(int l, int r, int i = 1) {
        a[i].il = l;
        a[i].ir = r;
        if (l == r) return;
        Build(l, md, nx);
        Build(md + 1, r, nx + 1);
    }

    void Add(int x, int y, int i = 1) {
        if (a[i].il > x || a[i].ir < x) return;
        a[i].sum += y;
        if (a[i].il == a[i].ir) return;
        Add(x, y, nx);
        Add(x, y, nx + 1);
    }

    long long Sum(int l, int r, int i = 1) {
        if (a[i].il > r || a[i].ir < l) return 0;
        if (l <= a[i].il && a[i].ir <= r) return a[i].sum;
        return Sum(l, r, nx) + Sum(l, r, nx + 1);
    }
#undef nx
#undef md
} it;

int n, m, tin[N], tout[N], timer, parent[N][K];
vector<int> adj[N];

void DFS(int u, int p) {
    tin[u] = ++timer;
    for (int i = 1; i < K; ++i) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
        if (parent[u][i] < 1) break;
    }
    for (int v : adj[u]) if (v != p) {
        parent[v][0] = u;
        DFS(v, u);
    }
    tout[u] = timer;
}

// u is ancestor of v
bool Anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int LCA(int u, int v) {
    if (Anc(u, v)) return u;
    if (Anc(v, u)) return v;
    for (int i = K - 1; i >= 0; --i) {
        if (parent[u][i] < 1 || Anc(parent[u][i], v)) continue;
        u = parent[u][i];
    }
    return parent[u][0];
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1, 0);
    it.Build(1, n);
    int m;
    cin >> m;
    while (m--) {
        char t;
        cin >> t;
        if (t == '+') {
            // cerr << "clgt" << endl;
            int v, u, d;
            cin >> v >> u >> d;
            it.Add(tin[v], d);
            it.Add(tin[u], d);
            int lca = LCA(u, v);
            // printf("lca(%d, %d) = %d\n", u, v, lca);
            it.Add(tin[lca], -d);
            it.Add(tin[parent[lca][0]], -d);
        } else {
            int v;
            cin >> v;
            long long ans = it.Sum(tin[v], tout[v]);
            cout << ans << "\n";
        }
    }
    return 0;
}