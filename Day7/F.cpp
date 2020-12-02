#include <bits/stdc++.h>
 
#define oo INT_MAX
#define sz(a) (int)a.size()
 
using namespace std;
 
random_device dev;
mt19937 gen(dev());
 
int rd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}
 
struct Node {
    int val, key, tail, y, childl = -1, childr = -1, pkey = 0;
    pair<int, int> ptail = {0, oo};
 
    Node(int _val, int _key, int _tail) : val(_val), key(_key), tail(_tail), y(rd(0, oo)) {}
};
 
int root = -1;
vector<Node> treap;
 
void Push(int v) {
    if (v < 0) return;
    treap[v].key += treap[v].pkey;
    if (treap[v].childl >= 0) treap[treap[v].childl].pkey += treap[v].pkey;
    if (treap[v].childr >= 0) treap[treap[v].childr].pkey += treap[v].pkey;
    treap[v].pkey = 0;
    if (treap[v].ptail == pair<int, int>(0, oo)) return;
    if (treap[v].ptail.second == oo) {
        treap[v].tail += treap[v].ptail.first;
        if (treap[v].childl >= 0) {
            if (treap[treap[v].childl].ptail.second == oo)
                treap[treap[v].childl].ptail.first += treap[v].ptail.first;
            else
                treap[treap[v].childl].ptail.second += treap[v].ptail.first;
        }
        if (treap[v].childr >= 0) {
            if (treap[treap[v].childr].ptail.second == oo)
                treap[treap[v].childr].ptail.first += treap[v].ptail.first;
            else
                treap[treap[v].childr].ptail.second += treap[v].ptail.first;
        }
    } else {
        treap[v].tail = treap[v].ptail.second;
        if (treap[v].childl >= 0) {
            treap[treap[v].childl].ptail = treap[v].ptail;
        }
        if (treap[v].childr >= 0) {
            treap[treap[v].childr].ptail = treap[v].ptail;
        }
    }
    treap[v].ptail = {0, oo};
}
 
pair<int, int> Split_by_key(int v, int key) {
    if (v < 0) return {-1, -1};
    Push(v);
    if (treap[v].key < key) {
        pair<int, int> tmp = Split_by_key(treap[v].childr, key);
        treap[v].childr = tmp.first;
        return {v, tmp.second};
    } else {
        pair<int, int> tmp = Split_by_key(treap[v].childl, key);
        treap[v].childl = tmp.second;
        return {tmp.first, v};
    }
}
 
pair<int, int> Split_by_tail(int v, int tail) {
    if (v < 0) return {-1, -1};
    Push(v);
    if (treap[v].tail < tail) {
        pair<int, int> tmp = Split_by_tail(treap[v].childr, tail);
        treap[v].childr = tmp.first;
        return {v, tmp.second};
    } else {
        pair<int, int> tmp = Split_by_tail(treap[v].childl, tail);
        treap[v].childl = tmp.second;
        return {tmp.first, v};
    }
}
 
int Merge(int vl, int vr) {
    if (vl < 0) return vr;
    if (vr < 0) return vl;
    Push(vl);
    Push(vr);
    if (treap[vl].y > treap[vr].y) {
        treap[vl].childr = Merge(treap[vl].childr, vr);
        return vl;
    } else {
        treap[vr].childl = Merge(vl, treap[vr].childl);
        return vr;
    }
}
 
int Leftmost(int v) {
    if (v < 0) return -1;
    Push(v);
    if (treap[v].childl >= 0) return Leftmost(treap[v].childl);
    return v;
}
 
int Find(int v, int x) {
    if (v < 0) return -1;
    Push(v);
    if (treap[v].key == x) return v;
    if (treap[v].key > x) return Find(treap[v].childl, x);
    return Find(treap[v].childr, x);
}
 
int Rightmost(int v) {
    if (v < 0) return -1;
    Push(v);
    if (treap[v].childr >= 0) return Rightmost(treap[v].childr);
    return v;
}
 
void Insert(int L, int K) {
    if (root < 0) {
        root = 0;
        treap.emplace_back(K, L, L);
        return;
    }
    int v = Find(root, L);
    if (v >= 0) {
        pair<int, int> tmp = Split_by_key(root, L);
        pair<int, int> tmp1 = Split_by_key(tmp.second, treap[v].tail + 1);
        pair<int, int> tmp2 = Split_by_tail(tmp.first, treap[v].tail);
        ++treap[tmp1.first].pkey;
        ++treap[tmp1.first].ptail.first;
        Push(tmp1.first);
        int v_next = Leftmost(tmp1.second);
        if (v_next >= 0 && treap[v_next].key == treap[tmp1.first].tail + 1) {
            treap[tmp1.first].ptail.second = treap[v_next].tail;
            Push(tmp1.first);
        }
        if (tmp2.second >= 0) {
            treap[tmp2.second].ptail.second = treap[tmp1.first].tail;
            Push(tmp2.second);
        }
        tmp.first = Merge(tmp2.first, tmp2.second);
        treap.push_back(Node(K, L, treap[tmp1.first].tail));
        tmp1.first = Merge(sz(treap) - 1, tmp1.first);
        tmp.second = Merge(tmp1.first, tmp1.second);
        root = Merge(tmp.first, tmp.second);
    } else {
        int tt = L;
        pair<int, int> tmp = Split_by_key(root, L);
        pair<int, int> tmp1 = Split_by_tail(tmp.first, L - 1);
        int v_adj = Leftmost(tmp.second);
        if (v_adj >= 0 && treap[v_adj].key == L + 1) {
            Push(v_adj);
            tt = treap[v_adj].tail;
        }
        if (tmp1.second >= 0) {
            treap[tmp1.second].ptail.second = tt;
            Push(tmp1.second);
        }
        tmp.first = Merge(tmp1.first, tmp1.second);
        treap.push_back(Node(K, L, tt));
        tmp.second = Merge(sz(treap) - 1, tmp.second);
        root = Merge(tmp.first, tmp.second);
    }
}
 
int main() {
    // freopen("inp.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int l;
        cin >> l;
        Insert(l, i);
    }
    int vw = Rightmost(root);
    cout << treap[vw].tail << "\n";
    for (int i = 1; i <= treap[vw].tail; ++i) {
        int v = Find(root, i);
        cout << (v < 0 ? 0 : treap[v].val) << " ";
        // cout.flush();
    }
    return 0;
}