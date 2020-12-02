#include <bits/stdc++.h>

using namespace std;

int n, k;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cur = (i - 1) * n + j;
            int div = 0;
            for (int ik = 1; ik <= cur; ++ik)
                if (cur % ik == 0) ++div;
            if (div <= k) cout << "*";
            else cout << ".";
        }
        cout << "\n";
    }
    return 0;
}