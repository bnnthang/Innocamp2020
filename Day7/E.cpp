#include <bits/stdc++.h>
 
#define sz(a) (int)a.size()
 
using namespace std;
 
typedef long long ll;
 
random_device dev;
mt19937 gen(dev());
 
int Rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}
 
const int ALPHABET = 26;
// a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
 
struct Treap {
    struct Node {
        ll key, delta, push_val = 0, sum = 0;
        int y, childl = -1, childr = -1;
         
        Node(ll _key, ll _delta = 0) : key(_key), delta(_delta), y(Rnd(0, INT_MAX)) {}
    };
 
    int root;
    vector<Node> container;
 
    Treap() : root(-1) { container.clear(); }
 
    void Tpush(int v) {
        container[v].key += container[v].push_val;
        if (container[v].childl >= 0) container[container[v].childl].push_val += container[v].push_val;
        if (container[v].childr >= 0) container[container[v].childr].push_val += container[v].push_val;
        container[v].push_val = 0;
    }
 
    pair<int, int> Tsplit(int v, ll key) {
        if (v < 0) return {-1, -1};
        Tpush(v);
        if (container[v].key < key) {
            pair<int, int> tmp = Tsplit(container[v].childr, key);
            container[v].childr = tmp.first;
            return {v, tmp.second};
        } else {
            pair<int, int> tmp = Tsplit(container[v].childl, key);
            container[v].childl = tmp.second;
            return {tmp.first, v};
        }
    }
 
    int Tmerge(int vl, int vr) {
        if (vl < 0) return vr;
        if (vr < 0) return vl;
        Tpush(vl);
        Tpush(vr);
        if (container[vl].y > container[vr].y) {
            container[vl].childr = Tmerge(container[vl].childr, vr);
            return vl;
        } else {
            container[vr].childl = Tmerge(vl, container[vr].childl);
            return vr;
        }
    }
 
    int Tsearch(int v, ll x) {
        if (v < 0) return -1;
        Tpush(v);
        if (container[v].key <= x && x <= container[v].key + container[v].delta - 1) return v;
        else if (x < container[v].key) return Tsearch(container[v].childl, x);
        else return Tsearch(container[v].childr, x);
    }
 
    void Tfix(ll idx, ll len) {
        int pos = Tsearch(root, idx);
        if (pos >= 0 && container[pos].key < idx) {
            ll tlen = container[pos].key + container[pos].delta - idx;
            container[pos].delta = idx - container[pos].key;
            pair<int, int> tmp = Tsplit(root, idx + 1);
            container.push_back(Node(idx, tlen));
            tmp.second = Tmerge(sz(container) - 1, tmp.second);
            root = Tmerge(tmp.first, tmp.second);
        }
        if (len == 0) return;
        pair<int, int> tmp = Tsplit(root, idx);
        if (tmp.second >= 0) container[tmp.second].push_val += len;
        root = Tmerge(tmp.first, tmp.second);
    }
 
    void Tinsert(ll idx, ll len) {
        if (root < 0) {
            container.clear();
            root = 0;
            container.push_back(Node(idx, len));
            return;
        }
        pair<int, int> tmp = Tsplit(root, idx);
        container.push_back(Node(idx, len));
        tmp.first = Tmerge(tmp.first, sz(container) - 1);
        root = Tmerge(tmp.first, tmp.second);
    }
 
    void Tremove(ll idx, ll len) {
        if (root < 0) return;
        Tfix(idx, 0);
        Tfix(idx + len, 0);
        pair<int, int> tmp = Tsplit(root, idx);
        pair<int, int> tmp1 = Tsplit(tmp.second, idx + len);
        if (tmp1.second >= 0) container[tmp1.second].push_val -= len;
        root = Tmerge(tmp.first, tmp1.second);
    }
 
    bool Tquery(ll l, ll r, int v) {
        if (v < 0) return false;
        Tpush(v);
        if (max(container[v].key, l) <= min(container[v].key + container[v].delta - 1, r))
            return true;
        if (container[v].key > r && container[v].childl >= 0)
            return Tquery(l, r, container[v].childl);
        if (container[v].key + container[v].delta - 1 < l && container[v].childr >= 0)
            return Tquery(l, r, container[v].childr);
        return false;
    }
} treaps[ALPHABET];
 
int main() {
    // freopen("inp.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int iq = 0; iq < n; ++iq) {
        char tc;
        cin >> tc;
        if (tc == '+') {
            ll idx, len;
            char t;
            cin >> idx >> len >> t;
            for (int i = 0; i < ALPHABET; ++i)
                treaps[i].Tfix(idx, len);
            treaps[t - 'a'].Tinsert(idx, len);
        } else if (tc == '-') {
            ll idx, len;
            cin >> idx >> len;
            for (int i = 0; i < ALPHABET; ++i)
                treaps[i].Tremove(idx, len);
        } else {
            ll l, r, ans = 0;
            cin >> l >> r;
            for (int i = 0; i < ALPHABET; ++i)
                ans += treaps[i].Tquery(l, r, treaps[i].root);
            cout << ans << "\n";
        }
    }
    return 0;
}