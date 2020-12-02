#include <bits/stdc++.h>

using namespace std;

const int N = 102;

int n, q[N], root, f[N][2];
vector<int> adj[N];

void dfs(int u) {
    f[u][0] = 0;
    f[u][1] = q[u];
    for (int v : adj[u]) {
        dfs(v);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p >> q[i];
        if (p == 0) root = i;
        else adj[p].push_back(i);
    }
    dfs(root);
    cout << max(f[root][0], f[root][1]);
    return 0;
}