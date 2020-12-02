#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

const int N = 1e5 + 2;

int n, m, deg[N][2];
char f[N][2];
vector<int> adj[N], radj[N];
queue<pair<int, int>> q;
set<pair<int, int>> wait;

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        // if (u == v) continue;
        adj[u].push_back(v);
        radj[v].push_back(u);
        ++deg[u][0];
        ++deg[u][1];
    }
    memset(f, '#', sizeof(f));
    for (int i = 1; i <= n; ++i)
        if (deg[i][0] == 0) {
            q.emplace(i, 0);
            q.emplace(i, 1);
            f[i][0] = f[i][1] = 'L';
        }
    while (!q.empty()) {
        int u = q.front().first;
        bool flag = q.front().second;
        q.pop();
        for (int v : radj[u]) {
            if (flag) {
                --deg[v][0];
                if (deg[v][0] == 0) {
                    q.emplace(v, 0);
                    int cntw = 0, cntl = 0;
                    for (int i : adj[v]) {
                        if (f[i][1] == 'W') ++cntw;
                        else if (f[i][1] == 'L') ++cntl;
                    }
                    if (cntw + cntl < sz(adj[v])) {
                        f[v][0] = 'D';
                    } else {
                        if (cntl > 0) f[v][0] = 'W';
                        else f[v][0] = 'L';
                    }
                }
            } else {
                --deg[v][1];
                if (f[u][0] == 'L') {
                    if (f[v][1] != 'W') {
                        f[v][1] = 'W';
                        q.emplace(v, 1);
                        auto tmp = wait.find({v, 1});
                        if (tmp != wait.end()) {
                            wait.erase(tmp);
                        }
                    }
                } else if (f[u][0] == 'W') {
                    if (f[v][1] == '#') {
                        f[v][1] = 'L';
                        wait.emplace(v, 1);
                        if (deg[v][1] == 0) {
                            q.emplace(v, 1);
                            auto tmp = wait.find({v, 1});
                            if (tmp != wait.end()) {
                                wait.erase(tmp);
                            }
                        }
                    }
                }
            }
        }
        if (q.empty() && !wait.empty()) {
            q.push(*wait.begin());
            wait.erase(wait.begin());
        }
    }
    for (int j = 0; j < 2; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (f[i][j] == '#') f[i][j] = 'D';
            cout << f[i][j];
        }
        cout << "\n";
    }
    return 0;
}