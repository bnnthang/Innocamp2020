#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> f;

int main() {
    cin >> n;
    f.assign(n + 2, 0);
    f[0] = false;
    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            f[i] = f[i - 1] ^ 1;
            if (i >= 2) f[i] |= f[i - 2] ^ 1;
        } else if (i % 3 == 1) {
            f[i] = f[i - 1] ^ 1;
            if (i >= 3) f[i] |= f[i - 3] ^ 1;
        } else {
            f[i] = f[i - 1] ^ 1;
            if (i >= 1) f[i] |= f[i - 2] ^ 1;
            if (i >= 3) f[i] |= f[i - 3] ^ 1;
        }
    }
    cout << (f[n] == 1 ? 1 : 2);
    return 0;
}