#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

template<typename T = int>
T Rand(T l, T r) {
    uniform_int_distribution<T> dis(l, r);
    return dis(gen);
}

const int oo = 2e9;

struct Treap {
    struct Node {
        int key, y, childl, childr;
        Node(int _key) : key(_key), y(Rand(0, oo)), childl(-1), childr(-1) {}
    };
    int root;
    vector<Node> container;

    Treap() {
        container.clear();
        container.push_back(Node(oo));
        root = 0;
    }

    void Print() {
        for (Node i : container) {
            fprintf(stderr, "%d %d %d %d\n", i.y, i.key, i.childl, i.childr);
        }
    }

    pair<int, int> Split(int v, int key) {
        if (v < 0) return {-1, -1};
        if (container[v].key <= key) {
            pair<int, int> tmp = Split(container[v].childr, key);
            container[v].childr = tmp.first;
            return {v, tmp.second};
        } else {
            pair<int, int> tmp = Split(container[v].childl, key);
            container[v].childl = tmp.second;
            return {tmp.first, v};
        }
    }

    int Merge(int vl, int vr) {
        if (vl < 0) return vr;
        if (vr < 0) return vl;
        if (container[vl].y > container[vr].y) {
            container[vl].childr = Merge(container[vl].childr, vr);
            return vl;
        } else {
            container[vr].childl = Merge(vl, container[vr].childl);
            return vr;
        }
    }

    void Insert(int x) {
        if (Exist(x, root)) return;
        container.push_back(Node(x));
        pair<int, int> tmp = Split(root, x);
        tmp.first = Merge(tmp.first, sz(container) - 1);
        root = Merge(tmp.first, tmp.second);
    }

    void Delete(int x) {
        if (!Exist(x, root)) return;
        pair<int, int> tmp = Split(root, x - 1);
        pair<int, int> tmp1 = Split(tmp.second, x);
        int tmp2 = Merge(container[tmp1.first].childl, container[tmp1.first].childr);
        tmp.second = Merge(tmp2, tmp1.second);
        root = Merge(tmp.first, tmp.second);
    }

    bool Exist(int x, int v) {
        if (container[v].key == x) return true;
        if (container[v].key < x) {
            if (container[v].childr < 0) return false;
            else return Exist(x, container[v].childr);
        } else {
            if (container[v].childl < 0) return false;
            else return Exist(x, container[v].childl);
        }
    }

    int Next(int x) {
        pair<int, int> tmp = Split(root, x);
        // Print();
        // fprintf(stderr, "%d %d\n", tmp.first, tmp.second);
        if (tmp.second < 0) return oo;
        int cur = tmp.second;
        while (container[cur].childl >= 0)
            cur = container[cur].childl;
        cur = container[cur].key;
        // fprintf(stderr, "%d\n", cur);
        root = Merge(tmp.first, tmp.second);
        return cur;
    }

    int Prev(int x) {
        // Print();
        pair<int, int> tmp = Split(root, x - 1);
        // Print();
        // fprintf(stderr, "%d %d\n", tmp.first, tmp.second);
        if (tmp.first < 0) return -oo;
        int cur = tmp.first;
        while (container[cur].childr >= 0)
            cur = container[cur].childr;
        cur = container[cur].key;
        root = Merge(tmp.first, tmp.second);
        return cur;
    }
} treap;

int main() {
    string cmd;
    while (cin >> cmd) {
        int x;
        cin >> x;
        if (cmd == "insert") {
            treap.Insert(x);
        } else if (cmd == "delete") {
            treap.Delete(x);
        } else if (cmd == "exists") {
            bool res = treap.Exist(x, treap.root);
            cout << (res ? "true\n" : "false\n");
        } else if (cmd == "next") {
            int res = treap.Next(x);
            if (abs(res) == oo) cout << "none\n";
            else cout << res << "\n";
        } else if (cmd == "prev") {
            int res = treap.Prev(x);
            if (abs(res) == oo) cout << "none\n";
            else cout << res << "\n";
        } else {
            treap.Print();
        }
    }
    return 0;
}