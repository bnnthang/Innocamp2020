#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

const int N = 1e5 + 2;

long long F(long long a, long long b) {
    if (a == LLONG_MAX) return b;
    else return max(a, b);
}

struct IT {
    struct Node {
        int il, ir, tcnt = 0;
        long long tmin = LLONG_MAX, tval = LLONG_MAX;
    } a[N * 4];

#define md ((l + r) >> 1)
#define nx (i << 1)
    void Lazy(int i) {
        if (a[i].tval == LLONG_MAX) return;
        a[nx].tval = F(a[nx].tval, a[i].tval);
        a[nx].tmin = min(a[nx].tmin, a[nx].tval);
        a[nx].tcnt = a[nx].ir - a[nx].il + 1;
        a[nx + 1].tval = F(a[nx + 1].tval, a[i].tval);
        a[nx + 1].tmin = min(a[nx + 1].tmin, a[nx + 1].tval);
        a[nx + 1].tcnt = a[nx + 1].ir - a[nx + 1].il + 1;
        a[i].tval = LLONG_MAX;
    }

    void Build(int l, int r, int i = 1) {
        a[i].il = l;
        a[i].ir = r;
        if (l == r) return;
        Build(l, md, nx);
        Build(md + 1, r, nx + 1);
    }

    void Assign(int l, int r, long long x, int i = 1) {
        if (a[i].il > r || a[i].ir < l) return;
        if (l <= a[i].il && a[i].ir <= r) {
            a[i].tval = F(a[i].tval, x);
            a[i].tmin = min(a[i].tmin, a[i].tval);
            a[i].tcnt = a[i].ir - a[i].il + 1;
            return;
        }
        Lazy(i);
        Assign(l, r, x, nx);
        Assign(l, r, x, nx + 1);
        a[i].tmin = min(a[nx].tmin, a[nx + 1].tmin);
        a[i].tcnt = a[nx].tcnt + a[nx + 1].tcnt;
    }

    long long Min(int l, int r, int i = 1) {
        if (a[i].il > r || a[i].ir < l) return LLONG_MAX;
        if (l <= a[i].il && a[i].ir <= r) return a[i].tmin;
        Lazy(i);
        long long res = min(Min(l, r, nx), Min(l, r, nx + 1));
        a[i].tmin = min(a[nx].tmin, a[nx + 1].tmin);
        a[i].tcnt = a[nx].tcnt + a[nx + 1].tcnt;
        return res;
    }

    int Slots(int l, int r, int i = 1) {
        if (a[i].il > r || a[i].ir < l) return 0;
        if (l <= a[i].il && a[i].ir <= r) return a[i].tcnt;
        Lazy(i);
        int res = Slots(l, r, nx) + Slots(l, r, nx + 1);
        a[i].tmin = min(a[nx].tmin, a[nx + 1].tmin);
        a[i].tcnt = a[nx].tcnt + a[nx + 1].tcnt;
        return res;
    }

    long long Get(int p, int i = 1) {
        if (a[i].il > p || a[i].ir < p) return LLONG_MIN;
        if (a[i].il == p && a[i].ir == p) return a[i].tval;
        Lazy(i);
        return max(Get(p, nx), Get(p, nx + 1));
    }
#undef md
#undef nx
} it;

int n, m;
long long a[N];
vector<pair<int, pair<int, int>>> q;

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    cin >> n >> m;
    q.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> q[i].se.fi >> q[i].se.se;
        cin >> q[i].fi;
    }
    sort(q.begin(), q.end(), greater<pair<int, pair<int, int>>>());
    it.Build(1, n);
    for (int i = 0; i < m; ++i) {
        int l = q[i].se.fi, r = q[i].se.se;
        long long vmin = it.Min(l, r);
        int slots = it.Slots(l, r);
        if (slots < r - l + 1) {
            it.Assign(l, r, q[i].fi);
        } else {
            if (vmin > q[i].fi) {
                cout << "inconsistent\n";
                return 0;
            }
        }
    }
    cout << "consistent\n";
    for (int i = 1; i <= n; ++i) {
        cout << min(it.Get(i), 1LL * INT_MAX) << " ";
    }
    cout << "\n";
    return 0;
}