#include <bits/stdc++.h>

#define X first
#define Y second
#define sqr(a) ((a) * (a))

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;

istream& operator>>(istream& in, point& p) {
    in >> p.X >> p.Y;
    return in;
}

ll operator*(point a, point b) {
    return a.X * b.X + a.Y * b.Y;
}

ll operator%(point a, point b) {
    return a.X * b.Y - a.Y * b.X;
}

point operator-(point a, point b) {
    return {a.X - b.X, a.Y - b.Y};
}

long double MinDist(point a, point b, point c) {
    point ba = a - b;
    point bc = c - b;
    point ca = a - c;
    point cb = b - c;
    long double ans;
    if (ba * bc < 0) {
        ans = sqrt(sqr(a.X - b.X) + sqr(a.Y - b.Y));
    } else if (ca * cb < 0) {
        ans = sqrt(sqr(a.X - c.X) + sqr(a.Y - c.Y));
    } else {
        ans = abs(double(ba % bc) / sqrt(sqr(bc.X) + sqr(bc.Y)));
    }
    return ans;
}

point a, b, c, d;

int main() {
    cin >> a >> b >> c >> d;
    (cout << fixed).precision(12);
    point ab = b - a, cd = d - c;
    point ac = c - a;
    point ad = d - a;
    point ca = a - c;
    point cb = b - c;
    if ((ac % ab) * (ad % ab) < 0 && (ca % cd) * (cb % cd) < 0) {
        cout << 0;
        return 0;
    }
    long double ans1 = MinDist(a, c, d);
    long double ans2 = MinDist(b, c, d);
    long double ans3 = MinDist(c, a, b);
    long double ans4 = MinDist(d, a, b);
    long double ans = min(ans1, min(ans2, min(ans3, ans4)));
    cout << ans;
    return 0;
}