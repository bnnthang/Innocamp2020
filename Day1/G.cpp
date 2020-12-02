#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2, K = 17;

int n, p[N], tin[N], tout[N], timer, depth[N], parent[N][K], ans, root;
vector<int> adj[N], tadj[N];

void DFS(int u) {
  tin[u] = ++timer;
  for (int i = 1; i < K; ++i) {
    parent[u][i] = parent[parent[u][i - 1]][i - 1];
    if (parent[u][i] < 1) break;
  }
  for (int v : adj[u]) {
    parent[v][0] = u;
    depth[v] = depth[u] + 1;
    DFS(v);
  }
  tout[u] = ++timer;
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

void DFS1(int u) {
  for (int v : tadj[u]) {
    ans += depth[v] - depth[u];
    DFS1(v);
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int p;
    cin >> p;
    if (p < 0) {
      root = i;
    } else {
      adj[p].push_back(i);
    }
  }
  DFS(root);
  int g;
  cin >> g;
  while (g--) {
    int k;
    cin >> k;
    vector<int> vg(k);
    for (int& i : vg) cin >> i;
    vg.push_back(root);
    sort(vg.begin(), vg.end());
    vg.erase(unique(vg.begin(), vg.end()), vg.end());
    k = vg.size();
    sort(vg.begin(), vg.end(), [&](int x, int y) {
      return tin[x] < tin[y];
    });
    for (int i = 1; i < k; ++i) {
      int tmp = LCA(vg[i - 1], vg[i]);
      vg.push_back(tmp);
    }
    sort(vg.begin(), vg.end());
    vg.erase(unique(vg.begin(), vg.end()), vg.end());
    k = vg.size();
    sort(vg.begin(), vg.end(), [&](int x, int y) {
      return tin[x] < tin[y];
    });
    stack<int> st;
    for (int i = 0; i < k; ++i) {
      // fprintf(stderr, "ok%d\n", vg[i]);
      while (!st.empty() && tout[st.top()] < tin[vg[i]]) st.pop();
      // fprintf(stderr, "ok%d\n", vg[i]);
      if (!st.empty())
        tadj[st.top()].push_back(vg[i]);
      // fprintf(stderr, "ok%d\n", vg[i]);
      st.push(vg[i]);
      // fprintf(stderr, "ok%d\n", vg[i]);
    }
    ans = 1;
    DFS1(root);
    cout << ans << "\n";
    for (int i = 0; i < k; ++i) tadj[vg[i]].clear();
  }
  return 0;
}