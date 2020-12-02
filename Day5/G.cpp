#include <bits/stdc++.h>
  
#define sz(a) (int)a.size()
  
using namespace std;
  
struct point { long double x, y; };
struct line { long double a, b, c; };
  
const int N = 2002;
const long double EPS = 1e-10;
const long double oo = 1e14;
  
point intersect(const line& l1, const line& l2) {
    long double d = l1.b * l2.a - l1.a * l2.b + 0.0;
    long double dx = l1.c * l2.b - l2.c * l1.b + 0.0;
    long double dy = l1.a * l2.c - l1.c * l2.a + 0.0;
    if (abs(d) < EPS) {
        if (abs(dx) < EPS && abs(dy) < EPS) return {oo, oo}; // duplicate
        else return {oo, -oo}; // parallel
    } else {
        return {dx / d + 0.0, dy / d + 0.0}; // intersect
    }
}
  
bool ok(point p, line l) {
    return l.a * p.x + l.b * p.y + l.c + 0.0 >= -EPS;
}
  
int n;
line a[N];
vector<point> vp;
  
bool operator<(const point &a, const point &b) {
    return abs(a.x - b.x) < EPS ? a.y < b.y : a.x < b.x;
}
  
bool operator==(const point &a, const point &b) {
    return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}
  
istream& operator>>(istream& in, line& l) {
    in >> l.a >> l.b >> l.c;
    return in;
}
  
bool cw(point &a, point &b, point &c) {
    return (b.x - a.x + 0.0) * (c.y - a.y + 0.0) < (b.y - a.y + 0.0) * (c.x - a.x + 0.0);
}
  
bool ccw(point &a, point &b, point &c) {
    return (b.x - a.x + 0.0) * (c.y - a.y + 0.0) > (b.y - a.y + 0.0) * (c.x - a.x + 0.0);
}
  
void convex_hull(vector<point> &a, vector<point> &h) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
  
    point P = a.front(), Q = a.back();
    vector<point> u, d;
  
#define Compare function<bool(point&, point&, point&)>
    function<void(point&, vector<point>&, Compare)> exec = [&](point &p, vector<point> &v, Compare comp) {
        while (sz(v) > 1 && !comp(v[sz(v) - 2], v[sz(v) - 1], p)) v.pop_back();
        v.push_back(p);
    };
#undef Compare
  
    for (int i = 0; i < sz(a); ++i) {
        if (i == 0 || i == sz(a) - 1 || cw(P, a[i], Q)) exec(a[i], u, cw);
        if (i == 0 || i == sz(a) - 1 || ccw(P, a[i], Q)) exec(a[i], d, ccw);
    }
  
//    for (point i : u) cout << i << "\n";
//    cout << "\n";
//    for (point i : d) cout << i << "\n";
  
    h = u;
    for (int i = sz(d) - 2; i > 0; --i) h.push_back(d[i]);
}
  
int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            point p = intersect(a[i], a[j]);
            if (abs(p.x - oo) < EPS) continue;
            bool flag = true;
            for (int k = 1; k <= n; ++k) {
                if (!ok(p, a[k])) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                vp.push_back(p);
            }
        }
    }
    vector<point> hull;
    hull.clear();
    convex_hull(vp, hull);
    long double ans = 0;
    for (int i = 0; i < sz(hull); ++i) {
        ans += (hull[i].y + hull[(i + 1) % sz(hull)].y + 0.0) * (hull[i].x - hull[(i + 1) % sz(hull)].x + 0.0) + 0.0;
    }
    ans = abs(ans) / 2.0 + 0.0;
    (cout << fixed).precision(12);
    cout << ans;
    return 0;
}