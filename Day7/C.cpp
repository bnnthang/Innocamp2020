#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

int Rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}

struct Node {
    int y, key, childl = -1, childr = -1, children = 1;
    bool reversed = false;
    Node(int _key) : y(Rnd(0, INT_MAX)), key(_key) {}
};

int n, m, root;
vector<Node> treap;

void Tupd(int v) {
    if (v < 0) return;
    treap[v].children = 1;
    if (treap[v].childl >= 0) treap[v].children += treap[treap[v].childl].children;
    if (treap[v].childr >= 0) treap[v].children += treap[treap[v].childr].children;
}

void Tpush(int v) {
    if (v < 0 || !treap[v].reversed) return;
    if (treap[v].childl >= 0) treap[treap[v].childl].reversed ^= 1;
    if (treap[v].childr >= 0) treap[treap[v].childr].reversed ^= 1;
    swap(treap[v].childl, treap[v].childr);
    treap[v].reversed = false;
}

pair<int, int> Tsplit(int v, int x) {
    if (v < 0) return {-1, -1};
    Tpush(v);
    int children_left = treap[v].childl < 0 ? 0 : treap[treap[v].childl].children;
    if (children_left + 1 <= x) {
        pair<int, int> tmp = Tsplit(treap[v].childr, x - children_left - 1);
        treap[v].childr = tmp.first;
        Tupd(v);
        return {v, tmp.second};
    } else {
        pair<int, int> tmp = Tsplit(treap[v].childl, x);
        treap[v].childl = tmp.second;
        Tupd(v);
        return {tmp.first, v};
    }
}

int Tmerge(int vl, int vr) {
    if (vl < 0) return vr;
    if (vr < 0) return vl;
    Tpush(vl);
    Tpush(vr);
    if (treap[vl].y > treap[vr].y) {
        treap[vl].childr = Tmerge(treap[vl].childr, vr);
        Tupd(vl);
        return vl;
    } else {
        treap[vr].childl = Tmerge(vl, treap[vr].childl);
        Tupd(vr);
        return vr;
    }
}

int Tfind(int v, int x) {
    Tpush(v);
    if (treap[v].childl >= 0) {
        if (x <= treap[treap[v].childl].children)
            return Tfind(treap[v].childl, x);
        x -= treap[treap[v].childl].children;
    }
    if (x == 1) return v;
    if (treap[v].childr < 0) return -1;
    return Tfind(treap[v].childr, --x);
}

int main() {
    // freopen("inp.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    treap.push_back(Node(0));
    root = 0;
    for (int i = 1; i < n; ++i) {
        treap.push_back(Node(i));
        root = Tmerge(root, i);
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        pair<int, int> tmp = Tsplit(root, l - 1);
        pair<int, int> tmp1 = Tsplit(tmp.second, r - l + 1);
        if (tmp.first >= 0) treap[tmp.first].reversed ^= 1;
        treap[tmp1.first].reversed ^= 1;
        tmp1.first = Tmerge(tmp.first, tmp1.first);
        treap[tmp1.first].reversed ^= 1;
        root = Tmerge(tmp1.first, tmp1.second);
    }
    for (int i = 1; i <= n; ++i) {
        int cur = Tfind(root, i);
        printf("%d ", treap[cur].key + 1);
    }
    return 0;
}