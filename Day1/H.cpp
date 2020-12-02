#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;
const int B = 300, B1 = 340;
int bcnt;

int n, m, q, a[N], pt1[B1][B + 2], pt2[B1][B + 2], pt3[B1][B + 2][B + 2], pt4[B1][B1];

inline int bl(int i) {
    return (i - 1) * B + 1;
}

inline int br(int i) {
    return min(i * B, n);
}

inline int bi(int i) {
    return (i - 1) / B + 1;
}

int main() {
    cin >> n >> m >> q >> a[1];
    for (int i = 2; i <= n; ++i) {
        a[i] = (a[i - 1] * 23 + 21563) % 16714589;
    }
    bcnt = (n + B - 1) / B;
    for (int i = 1; i <= bcnt; ++i) {
        pt1[i][0] = pt2[i][0] = 1;
        for (int j = bl(i); j <= br(i); ++j) {
            pt1[i][j - bl(i) + 1] = 1LL * pt1[i][j - bl(i)] * a[j] % m;
        }
        for (int j = br(i); j >= bl(i); --j) {
            pt2[i][br(i) - j + 1] = 1LL * pt2[i][br(i) - j] * a[j] % m;
        }
        for (int j = bl(i); j <= br(i); ++j) {
            pt3[i][j - bl(i) + 1][j - bl(i)] = 1;
            for (int k = j; k <= br(i); ++k) {
                pt3[i][j - bl(i) + 1][k - bl(i) + 1] = 1LL * pt3[i][j - bl(i) + 1][k - bl(i)] * a[k] % m;
            }
        }
    }
    for (int i = 1; i <= bcnt; ++i) {
        pt4[i][i - 1] = 1;
        for (int j = i; j <= bcnt; ++j) {
            pt4[i][j] = 1LL * pt4[i][j - 1] * pt1[j][br(j) - bl(j) + 1] % m;
        }
    }
    int u, v, res;
    cin >> u >> v;
    for (int i = 1; i <= q; ++i) {
        int l = min(u, v), lb = bi(l);
        int r = max(u, v), rb = bi(r);
        if (lb == rb) {
            res = pt3[lb][l - bl(lb) + 1][r - bl(lb) + 1];
        } else {
            res = 1LL * pt2[lb][br(lb) - l + 1] * pt1[rb][r - bl(rb) + 1] % m;
            ++lb;
            --rb;
            if (lb <= rb) {
                res = 1LL * res * pt4[lb][rb] % m;
            }
        }
        if (i == q) break;
        u = (17 * u + 751 + res + i * 2) % n + 1;
        v = (13 * v + 593 + res + i * 5) % n + 1;
    }
    cout << u << " " << v << " " << res << "\n";
    return 0;
}