#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 2e7 + 2;
 
int n, m;
long long x, y, z, t, a[N], b[N], c[N];
 
int main() {
    cin >> n >> x >> y >> a[0] >> m >> z >> t >> b[0];
    c[0] = b[0] % n;
    for (int i = 1; i < n; ++i) {
        a[i] = (a[i - 1] * x + y) % (1LL << 16);
    }
    for (int i = 1; i < n; ++i) {
        a[i] += a[i - 1];
    }
    for (int i = 1; i < m * 2; ++i) {
        b[i] = (b[i - 1] * z + t) % (1LL << 30);
        if (b[i] < 0) b[i] += 1LL << 30;
        c[i] = b[i] % n;
    }
    c[0] = b[0] % n;
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        long long l = c[i * 2], r = c[i * 2 + 1];
        if (l > r) swap(l, r);
        if (l == 0) {
            ans += a[r];
            // cout << a[r] << "\n";
        } else {
            long long sum = a[r] - a[l - 1];
            ans += sum;
            // cout << sum << "\n";
        }
    }
    cout << ans;
    return 0;
}