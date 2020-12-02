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

ll operator*(point& p, point& q) {
    return p.X * q.X - p.Y * q.Y;
}

ll operator%(point& p, point& q) {
    return p.X * q.Y - p.Y * q.X;
}

point a, b, c;
 
int main() {
    cin >> a >> b >> c;
    (cout << fixed).precision(12);
    point n = {c.Y - b.Y, b.X - c.X};
    point ba = {a.X - b.X, a.Y - b.Y};
    point ca = {a.X - c.X, a.Y - c.Y};
    point bc = {c.X - b.X, c.Y - b.Y};
    if ((n % ba) * (n % ca) < 0) {
        double ans = double(abs(bc % ba)) / sqrt(sqr(bc.X) + sqr(bc.Y));
        cout << ans;
    } else {
        ll ans1 = sqr(a.X - b.X) + sqr(a.Y - b.Y);
        ll ans2 = sqr(a.X - c.X) + sqr(a.Y - c.Y);
        double ans = sqrt(min(ans1, ans2));
        cout << ans;
    }
    return 0;
}