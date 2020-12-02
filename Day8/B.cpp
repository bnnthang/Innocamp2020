#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 2;

int n, m;
vector<vector<int>> radj;
vector<bool> vis;
vector<int> deg;
vector<string> state;
queue<int> q;

void dfs(int u) {
    vis[u] = true;
    for (int v : radj[u]) if (!vis[v]) {
        if (state[u] == "SECOND") {
            state[v] = "FIRST";
        } else if ((--deg[v]) == 0) {
            state[v] = "SECOND";
        } else continue;
        dfs(v);
    }
}

int main() {
    while (cin >> n >> m) {
        radj.clear(); radj.resize(n + 2);
        deg.clear(); deg.resize(n + 2, 0);
        state.clear(); state.resize(n + 2, "");
        vis.clear(); vis.resize(n + 2, false);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            radj[v].push_back(u);
            ++deg[u];
        }
        for (int i = 1; i <= n; ++i)
            if (deg[i] == 0 && !vis[i]) {
                state[i] = "SECOND";
                dfs(i);
            }
        for (int i = 1; i <= n; ++i)
            if (state[i] == "") {
                cout << "DRAW\n";
            } else {
                cout << state[i] << "\n";
            }
        cout << "\n";
    }
}