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

point a, b, c;

int main() {
    cin >> a >> b >> c;
    (cout << fixed).precision(12);
    point ba = a - b;
    point bc = c - b;
    point ca = a - c;
    point cb = b - c;
    double ans;
    if (ba * bc < 0) {
        ans = sqrt(sqr(a.X - b.X) + sqr(a.Y - b.Y));
    } else if (ca * cb < 0) {
        ans = sqrt(sqr(a.X - c.X) + sqr(a.Y - c.Y));
    } else {
        ans = abs(double(ba % bc) / sqrt(sqr(bc.X) + sqr(bc.Y)));
    }
    cout << ans;
    return 0;
}