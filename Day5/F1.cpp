#include <bits/stdc++.h>

#define sz(a) (int)a.size()
#define sqr(a) ((a) * (a))

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    Point(ll _x = 0, ll _y = 0) {
        x = _x;
        y = _y;
    }
};

bool operator <(const Point &a, const Point &b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool operator ==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

ostream& operator <<(ostream &out, Point &p) {
    out << p.x << " " << p.y;
    return out;
}

bool cw(Point &a, Point &b, Point &c) {
    return (b.x - a.x) * (c.y - a.y) < (b.y - a.y) * (c.x - a.x);
}

bool ccw(Point &a, Point &b, Point &c) {
    return (b.x - a.x) * (c.y - a.y) > (b.y - a.y) * (c.x - a.x);
}

void convex_hull(vector<Point> &a, vector<Point> &h) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    Point P = a.front(), Q = a.back();
    vector<Point> u, d;

#define Compare function<bool(Point&, Point&, Point&)>
    function<void(Point&, vector<Point>&, Compare)> exec = [&](Point &p, vector<Point> &v, Compare comp) {
        while (sz(v) > 1 && !comp(v[sz(v) - 2], v[sz(v) - 1], p)) v.pop_back();
        v.push_back(p);
    };
#undef Compare

    for (int i = 0; i < sz(a); ++i) {
        if (i == 0 || i == sz(a) - 1 || cw(P, a[i], Q)) exec(a[i], u, cw);
        if (i == 0 || i == sz(a) - 1 || ccw(P, a[i], Q)) exec(a[i], d, ccw);
    }

//    for (Point i : u) cout << i << "\n";
//    cout << "\n";
//    for (Point i : d) cout << i << "\n";

    h = u;
    for (int i = sz(d) - 2; i > 0; --i) h.push_back(d[i]);
}

int n;
vector<Point> a, h;

int main() {
    ios::sync_with_stdio(false);
    (cout << fixed).precision(20);
    // freopen("inp.txt", "r", stdin);

    cin >> n;
    a.clear();
    h.clear();

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
    }

    convex_hull(a, h);
    reverse(h.begin(), h.end());

    double peri = 0;
    for (int i = 0; i < sz(h); ++i) {
        peri += sqrt(sqr(h[i].x - h[(i + 1) % sz(h)].x) + sqr(h[i].y - h[(i + 1) % sz(h)].y));
    }
    cout << peri;

    return 0;
}