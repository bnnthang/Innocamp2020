#include <bits/stdc++.h>

#define oo LLONG_MAX

using namespace std;
using ll = long long;

random_device dev;
mt19937 gen(dev());

int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}

const int N = 1e5 + 2;

struct IT {
    struct Node {
        int l = -1, r;
        ll amin = oo;
        pair<ll, ll> pval;
    } a[N << 2];

#define md ((l + r) >> 1)
#define nx (i << 1)
    void Push(int i) {
        if (a[i].l < 0 || a[i].pval == pair<ll, ll>(0, oo)) return;
        if (a[i].pval.second == oo) {
            a[i].amin += a[i].pval.first;
            if (nx < (N << 2) && a[nx].l > 0) {
                if (a[nx].pval.second == oo)
                    a[nx].pval.first += a[i].pval.first;
                else
                    a[nx].pval.second += a[i].pval.first;
            }
            if (nx + 1 < (N << 2) && a[nx + 1].l > 0) {
                if (a[nx + 1].pval.second == oo)
                    a[nx + 1].pval.first += a[i].pval.first;
                else
                    a[nx + 1].pval.second += a[i].pval.first;
            }
        } else {
            a[i].amin = a[i].pval.second;
            if (nx < (N << 2) && a[nx].l > 0) {
                a[nx].pval = a[i].pval;
            }
            if (nx + 1 < (N << 2) && a[nx + 1].l > 0) {
                a[nx + 1].pval = a[i].pval;
            }
        }
        a[i].pval = {0, oo};
    }

    void Build(int l, int r, int i = 1) {
        a[i].l = l;
        a[i].r = r;
        a[i].pval = {0, oo};
        if (l == r) return;
        Build(l, md, nx);
        Build(md + 1, r, nx + 1);
    }

    void Set(int l, int r, ll x, int i = 1) {
        Push(i);
        if (a[i].l > r || a[i].r < l) return;
        if (l <= a[i].l && a[i].r <= r) {
            a[i].pval.second = x;
            Push(i);
            return;
        }
        Set(l, r, x, nx);
        Set(l, r, x, nx + 1);
        a[i].amin = min(a[nx].amin, a[nx + 1].amin);
    }

    void Add(int l, int r, ll x, int i = 1) {
        Push(i);
        if (a[i].l > r || a[i].r < l) return;
        if (l <= a[i].l && a[i].r <= r) {
            a[i].pval.first = x;
            Push(i);
            return;
        }
        Add(l, r, x, nx);
        Add(l, r, x, nx + 1);
        a[i].amin = min(a[nx].amin, a[nx + 1].amin);
    }

    ll Min(int l, int r, int i = 1) {
        Push(i);
        if (a[i].l > r || a[i].r < l) return oo;
        if (l <= a[i].l && a[i].r <= r) {
            return a[i].amin;
        }
        ll m1 = Min(l, r, nx), m2 = Min(l, r, nx + 1);
        a[i].amin = min(a[nx].amin, a[nx + 1].amin);
        return min(m1, m2);
    }
#undef md
#undef nx
} tree;

int n, q;
int a[N];
string cmd[N];
int l[N], r[N], x[N];

void Gen() {
    n = 7;
    for (int i = 1; i <= n; ++i) a[i] = rnd(-20, 20);
    q = rnd(5, 15);
    for (int i = 1; i <= q; ++i) {
        int t = rnd(0, 2);
        if (t == 0) {
            cmd[i] = "set";
        } else if (t == 1) {
            cmd[i] = "add";
        } else {
            cmd[i] = "min";    
        }
        l[i] = rnd(1, n);
        r[i] = rnd(1, n);
        x[i] = rnd(-10, 10);
        if (l[i] > r[i]) swap(l[i], r[i]);
    }
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
    printf("\n");
    for (int i = 1; i <= q; ++i) {
        if (cmd[i] == "min") {
            printf("min %d %d\n", l[i], r[i]);
        } else {
            printf("%s %d %d %d\n", cmd[i].c_str(), l[i], r[i], x[i]);
        }
    }
}

ll arr[N];
void testing() {
    Gen();
    tree.Build(1, n);
    for (int i = 1; i <= n; ++i) {
        arr[i] = a[i];
        tree.Set(i, i, a[i]);
    }
    for (int i = 1; i <= q; ++i) {
        if (cmd[i] == "set") {
            tree.Set(l[i], r[i], x[i]);
            for (int j = l[i]; j <= r[i]; ++j)
                arr[j] = x[i];
        } else if (cmd[i] == "add") {
            tree.Add(l[i], r[i], x[i]);
            for (int j = l[i]; j <= r[i]; ++j)
                arr[j] += x[i];
        } else {
            ll tmp1 = tree.Min(l[i], r[i]);
            ll tmp2 = oo;
            for (int j = l[i]; j <= r[i]; ++j)
                tmp2 = min(tmp2, arr[j]);
            printf("%lld %lld\n", tmp1, tmp2);
            if (tmp1 != tmp2) {
                puts("crap");
                exit(0);
            }
        }
    }
}

int main() {
    // freopen("inp.txt", "r", stdin);
    // testing();
    cin >> n;
    tree.Build(1, n);
    for (int i = 1; i <= n; ++i) {
        ll a;
        cin >> a;
        tree.Set(i, i, a);
    }
    string cmd;
    while (cin >> cmd) {
        if (cmd == "set") {
            int i, j;
            ll x;
            cin >> i >> j >> x;
            tree.Set(i, j, x);
        } else if (cmd == "add") {
            int i, j;
            ll x;
            cin >> i >> j >> x;
            tree.Add(i, j, x);
        } else if (cmd == "min") {
            int i, j;
            cin >> i >> j;
            cout << tree.Min(i, j) << "\n";
        } else {
            break;
        }
    }
    return 0;
}