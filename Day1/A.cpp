#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2, L = 17;

int n, m, a[N][L], u, v;

int main() {
    cin >> n >> m >> a[1][0] >> u >> v;
    for (int i = 2; i <= n; ++i)
        a[i][0] = (a[i - 1][0] * 23 + 21563) % 16714589;
    for (int j = 1; j < L; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            a[i][j] = min(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
        }
    }
    int ans;
    for (int i = 1; i <= m; ++i) {
        // u <= v
        int tu = u, tv = v;
        if (tu > tv) swap(tu, tv);
        int l = __lg(tv - tu + 1);
        ans = min(a[tu][l], a[tv - (1 << l) + 1][l]);
        if (i == m) break;
        // printf("%d %d %d\n", u, v, ans);
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }
    cout << u << " " << v << " " << ans << "\n";
    return 0;
}