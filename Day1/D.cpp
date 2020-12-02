#include <bits/stdc++.h>

#define X first
#define Y second

using namespace std;

typedef pair<int, int> point;
typedef pair<pair<int, int>, pair<int, int>> rect;

istream& operator>>(istream& in, pair<int, int>& pai) {
    in >> pai.X >> pai.Y;
    return in;
}

const int N = 128, K = 8;
const int MOD = 1e9 + 7;

int n, m;
rect grid[N][N];
rect f[N][N][N][K];

rect intersect(rect a, rect b) {
    rect ret;
    ret.first.X = max(a.first.X, b.first.X);
    ret.first.Y = max(a.first.Y, b.first.Y);
    ret.second.X = min(a.second.X, b.second.X);
    ret.second.Y = min(a.second.Y, b.second.Y);
    return ret;
}

int nextv(int a, int b, int v) {
    return (1LL * a * v + b) % MOD;
}

int area(rect a) {
    if (a.first.X > a.second.X) return 0;
    if (a.first.Y > a.second.Y) return 0;
    return 1LL * (a.second.X - a.first.X) * (a.second.Y - a.first.Y) % MOD;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            point p1, p2;
            cin >> p1 >> p2;
            grid[i][j].first = {min(p1.X, p2.X), min(p1.Y, p2.Y)};
            grid[i][j].second = {max(p1.X, p2.X), max(p1.Y, p2.Y)};
        }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f[i][j][j][0] = grid[i][j];
            for (int k = j + 1; k < m; ++k) {
                f[i][j][k][0] = intersect(f[i][j][k - 1][0], grid[i][k]);
            }
        }
    }
    for (int t = 1; t < K; ++t) {
        for (int i = 0; i + (1 << t) - 1 < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int k = j; k < m; ++k) {
                    f[i][j][k][t] = intersect(f[i][j][k][t - 1], f[i + (1 << (t - 1))][j][k][t - 1]);
                }
            }
        }   
    }
    // printf("%d %d %d %d\n", f[1][0][1].first.X, f[1][0][1].first.Y, f[1][0][1].second.X, f[1][0][1].second.Y);
    int q, a, b, v0, ans = 0;
    cin >> q >> a >> b >> v0;
    while (q--) {
        int r1 = nextv(a, b, v0);
        int c1 = nextv(a, b, r1);
        int r2 = nextv(a, b, c1);
        int c2 = nextv(a, b, r2);
        v0 = c2;
        int rr1 = min(r1 % n, r2 % n);
        int rc1 = min(c1 % m, c2 % m);
        int rr2 = max(r1 % n, r2 % n);
        int rc2 = max(c1 % m, c2 % m);
        int ldelta = __lg(abs(rr1 - rr2));
        // printf("%d %d %d %d\n", rr1, rc1, rr2, rc2);
        // printf("ldelta = %d\n", ldelta);
        rect inter = intersect(f[rr1][rc1][rc2][ldelta], f[rr2 - (1 << ldelta) + 1][rc1][rc2][ldelta]);
        // printf("%d %d %d %d\n", inter.first.X, inter.first.Y, inter.second.X, inter.second.Y);
        // for (int i = rr1 + 1; i <= rr2; ++i) {
        //     inter = intersect(inter, f[i][rc1][rc2]);
        //     // printf("%d %d %d %d\n", inter.first.X, inter.first.Y, inter.second.X, inter.second.Y);
        // }
        int tmp = area(inter);
        (ans += tmp) %= MOD;
        // printf("%d %d %d %d\n", inter.first.X, inter.first.Y, inter.second.X, inter.second.Y);
    }
    cout << ans << "\n";
    return 0;
}