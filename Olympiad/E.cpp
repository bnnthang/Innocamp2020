#include <bits/stdc++.h>
 
using namespace std;
 
const int LIM = 1e6 + 2, oo = 1e7;
 
struct IT {
    struct Node {
        int l, r, maxl = -oo, minr = oo, res = oo * 10;
    } a[LIM << 2];
 
    void Merge(Node& lhs, Node& rhs, Node& res) {
        res.maxl = max(lhs.maxl, rhs.maxl);
        res.minr = min(lhs.minr, rhs.minr);
        res.res = min(min(lhs.res, rhs.res), rhs.minr - lhs.maxl);
    }
 
#define md ((l + r) >> 1)
#define nx (i << 1)
    void Build(int l, int r, int i = 1) {
        a[i].l = l;
        a[i].r = r;
        if (l == r) return;
        Build(l, md, nx);
        Build(md + 1, r, nx + 1);
    }
 
    void UpdL(int p, int x, int i = 1) {
        if (a[i].l > p || a[i].r < p) return;
        if (a[i].l == p && a[i].r == p) {
            a[i].minr = x;
            a[i].res = a[i].minr - a[i].maxl;
            return;
        }
        UpdL(p, x, nx);
        UpdL(p, x, nx + 1);
        Merge(a[nx], a[nx + 1], a[i]);
    }
 
    void UpdR(int p, int x, int i = 1) {
        if (a[i].l > p || a[i].r < p) return;
        if (a[i].l == p && a[i].r == p) {
            a[i].maxl = x;
            a[i].res = a[i].minr - a[i].maxl;
            return;
        }
        UpdR(p, x, nx);
        UpdR(p, x, nx + 1);
        Merge(a[nx], a[nx + 1], a[i]);
    }
#undef md
#undef nx
} it;
 
int q;
multiset<int> sl[LIM], srt;
multiset<int, greater<int>> sr[LIM], slt;
 
int main() {
    // freopen("inp.txt", "r", stdin);
    it.Build(1, LIM - 2);
    cin >> q;
    while (q--) {
        char t;
        int l, r;
        cin >> t >> l >> r;
        if (t == 'A') {
            sl[l].insert(r);
            sr[r].insert(l);
            slt.insert(l);
            srt.insert(r);
        } else {
            sl[l].erase(sl[l].find(r));
            sr[r].erase(sr[r].find(l));
            slt.erase(slt.find(l));
            srt.erase(srt.find(r));
        }
        int tl = sl[l].empty() ? oo : *sl[l].begin(), tr = sr[r].empty() ? -oo : *sr[r].begin();
        it.UpdL(l, tl);
        it.UpdR(r, tr);
        tl = *slt.begin();
        tr = *srt.begin();
        if (tl > tr) {
            cout << it.a[1].res << "\n";
        } else {
            int tl1 = *sr[tr].begin(), tr1 = *sl[tl].begin();
            cout << (tr1 - tl1) << "\n";
        }
    }
    return 0;
}