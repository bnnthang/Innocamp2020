#include <bits/stdc++.h>

#define X first
#define Y second

using namespace std;

typedef pair<long long, long long> point;
typedef pair<long long, long long> gvector;

istream& operator>>(istream& in, point& p) {
    in >> p.X >> p.Y;
    return in;
}

gvector operator-(point a, point b) {
    return {a.X - b.X, a.Y - b.Y};
}

long long operator*(gvector a, gvector b) {
    return a.X * b.Y - a.Y * b.X;
}

int main() {
    point a, b, c;
    cin >> a >> b >> c;
    gvector ba = a - b, bc = c - b;
    if (ba * bc == 0 && 
        min(b.X, c.X) <= a.X && a.X <= max(b.X, c.X) && 
        min(b.Y, c.Y) <= a.Y && a.Y <= max(b.Y, c.Y)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}