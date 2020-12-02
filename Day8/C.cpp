#include <bits/stdc++.h>

using namespace std;

const int N = 5002;

int n, grundy[N];
bool cnt[N];

int nim_sum(int a, int b) {
    return a ^ b;
}

int main() {
    memset(grundy, 0, sizeof(grundy));
    cin >> n;
    grundy[0] = 0;
    for (int i = 1; i <= n; ++i) {
        memset(cnt, false, sizeof(cnt));
        for (int j = 1; j <= i; ++j) {
            cnt[nim_sum(grundy[j > 2 ? j - 1 : 0], grundy[i - j > 1 ? i - j : 0])] = true;
        }
        while (cnt[grundy[i]]) ++grundy[i];
    }
    if (grundy[n] > 0) {
        cout << "Schtirlitz\n";
        for (int j = 1; j <= n; ++j) {
            if (nim_sum(grundy[j > 2 ? j - 1 : 0], grundy[n - j > 1 ? n - j : 0]) == 0) {
                cout << j << " ";
            }
        }
    } else {
        cout << "Mueller";
    }
    return 0;
}