#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 2;

int n;
long long sum[N], paths[N];
vector<int> adj[N];
vector<pair<int, int>> edges;
map<pair<int, int>, long long> ans;

void dfs(int u, int p) {
    sum[u] = 0;
    paths[u] = 1;
    for (int v : adj[u]) if (v != p) {
        dfs(v, u);
        sum[u] += sum[v] + paths[v];
        paths[u] += paths[v];
    }
    // fprintf(stderr, "%d %d %d\n", u, sum[u], paths[u]);
}

void dfs1(int u, int p, long long cursum) {
    for (int v : adj[u]) if (v != p) {
        long long curtmp = cursum + sum[u] - sum[v] - paths[v];
        ans[{u, v}] = curtmp * paths[v] + sum[v] * (n - paths[v]) + paths[v] * (n - paths[v]);
        dfs1(v, u, curtmp + n - paths[v]);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.emplace_back(u, v);
    }
    dfs(1, 0);
    dfs1(1, 0, 0);
    for (pair<int, int> i : edges) {
        if (ans.find(i) == ans.end())
            swap(i.first, i.second);
        cout << ans[i] << "\n";
    }
    return 0;
}