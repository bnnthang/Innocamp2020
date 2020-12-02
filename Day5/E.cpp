#include <bits/stdc++.h>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;

istream& operator>>(istream& in, point& p) {
    in >> p.X >> p.Y;
    return in;
}

ll operator*(point a, point b) {
    return a.X * b.Y - a.Y * b.X;
}

int n;
vector<point> a;

int main() {
    cin >> n;
    a.resize(n);
    for (point& i : a) cin >> i;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] * a[(i + 1) % n];
    }
    ll ans = abs(sum) / 2;
    cout << ans;
    if (sum % 2 != 0) {
        cout << ".5";
    }
    return 0;
}