#include <bits/stdc++.h>

#define X first
#define Y second
#define sqr(a) ((a) * (a))

using namespace std;

typedef pair<double, double> point;

struct Circle {
    point o;
    double r;
};

istream& operator>>(istream& in, point& p) {
    in >> p.X >> p.Y;
    return in;
}

ostream& operator<<(ostream& out, point& p) {
    out << p.X << " " << p.Y;
    return out;
}

istream& operator>>(istream& in, Circle& c) {
    in >> c.o >> c.r;
    return in;
}

point operator+(point a, point b) {
    return {a.X + b.X, a.Y + b.Y};
}

point operator-(point a, point b) {
    return {a.X - b.X, a.Y - b.Y};
}

point operator*(point a, double k) {
    return {a.X * k, a.Y * k};
}

point operator/(point a, double k) {
    return {a.X / k, a.Y / k};
}

int test;
Circle c1, c2;

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> test;
    (cout << fixed).precision(12);
    while (test--) {
        cin >> c1 >> c2;
        if (sqr(c1.r + c2.r) < sqr(c1.o.X - c2.o.X) + sqr(c1.o.Y - c2.o.Y)) {
            cout << "0\n";
        } else if (sqr(c1.r + c2.r) == sqr(c1.o.X - c2.o.X) + sqr(c1.o.Y - c2.o.Y)) {
            point v = ((c2.o - c1.o) * c1.r) / (c1.r + c2.r);
            point ans = c1.o + v;
            cout << "1\n" << ans << "\n";
        } else if (sqr(c1.r - c2.r) < sqr(c1.o.X - c2.o.X) + sqr(c1.o.Y - c2.o.Y)) {
            double ss = sqr(c1.o.X - c2.o.X) + sqr(c1.o.Y - c2.o.Y);
            double rhs = sqr(c1.r) - sqr(c2.r) + ss;
            double x = rhs / (sqrt(ss) * 2);
            double y = sqrt(sqr(c1.r) - sqr(x));
            point oo = c2.o - c1.o;
            point n = {c1.o.Y - c2.o.Y, c2.o.X - c1.o.X};
            point hp = n * (y / sqrt(sqr(n.X) + sqr(n.Y)));
            point inter = c1.o + (oo * (x / sqrt(sqr(oo.X) + sqr(oo.Y))));
            point i1 = inter + hp;
            point i2 = inter - hp;
            cout << "2\n" << inter << "\n" << abs(x) << " " << y << "\n" << i1 << "\n" << i2 << "\n";
        } else if (sqr(c1.r - c2.r) == sqr(c1.o.X - c2.o.X) + sqr(c1.o.Y - c2.o.Y)) {
            if (c1.o == c2.o) {
                cout << "3\n";
            } else {
                if (c1.r < c2.r) swap(c1, c2);
                point oo = c2.o - c1.o;
                point v = oo * (c1.r / sqrt(sqr(oo.X) + sqr(oo.Y)));
                point ans = c1.o + v;
                cout << "1\n" << ans << "\n";
            }
        } else {
            cout << "0\n";
        }
    }
    return 0;
}