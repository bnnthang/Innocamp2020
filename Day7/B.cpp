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

struct Node {
    int y, key, childl, childr;
    long long sum;
    Node(int _key) : y(Rnd(0, INT_MAX)), key(_key), childl(-1), childr(-1), sum(_key) {}
};

int root;
vector<Node> treap;

void Tupd(int v) {
    treap[v].sum = treap[v].key;
    if (treap[v].childl >= 0) treap[v].sum += treap[treap[v].childl].sum;
    if (treap[v].childr >= 0) treap[v].sum += treap[treap[v].childr].sum;
}

pair<int, int> Tsplit(int v, int key) {
    if (v < 0) return {-1, -1};
    if (treap[v].key < key) {
        pair<int, int> tmp = Tsplit(treap[v].childr, key);
        treap[v].childr = tmp.first;
        Tupd(v);
        return {v, tmp.second};
    } else {
        pair<int, int> tmp = Tsplit(treap[v].childl, key);
        treap[v].childl = tmp.second;
        Tupd(v);
        return {tmp.first, v};
    }
}

int Tmerge(int vl, int vr) {
    if (vl < 0) return vr;
    if (vr < 0) return vl;
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

bool Exist(int x, int v = root) {
    if (treap[v].key == x) return true;
    if (treap[v].key < x) {
        if (treap[v].childr >= 0) return Exist(x, treap[v].childr);
        else return false;
    } else {
        if (treap[v].childl >= 0) return Exist(x, treap[v].childl);
        else return false;
    }
}

void Print() {
    fprintf(stderr, "root = %d\n", root);
    for (Node i : treap) {
        fprintf(stderr, "key = %d y = %d sum = %lld childl = %d childr = %d\n", i.key, i.y, i.sum, i.childl, i.childr);
    }
}

int main() {
    treap.clear();
    int n;
    cin >> n;
    ll res = 0;
    treap.push_back(Node(-1));
    root = 0;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            ll x;
            cin >> x;
            x = (res + x) % 1000000000;
            res = 0;
            if (Exist(x)) continue;
            treap.push_back(Node(x));
            pair<int, int> t1 = Tsplit(root, x);
            t1.first = Tmerge(t1.first, sz(treap) - 1);
            root = Tmerge(t1.first, t1.second);
        } else if (c == '?') {
            int l, r;
            cin >> l >> r;
            pair<int, int> t1 = Tsplit(root, l);
            pair<int, int> t2 = Tsplit(t1.second, r + 1);
            if (t2.first < 0) {
                res = 0;
            } else {
                res = treap[t2.first].sum;
            }
            t1.second = Tmerge(t2.first, t2.second);
            root = Tmerge(t1.first, t1.second);
            cout << res << "\n";
        }
        // } else {
        //     Print();
        // }
    }
    return 0;
}