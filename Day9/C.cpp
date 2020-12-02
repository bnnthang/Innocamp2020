#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2;

int n, a[N], p[N];
set<int> app;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        app.insert((i - a[i] + n) % n);
    }
    for (int i = 0; i < n; ++i) {
        if (app.find(i) == app.end()) {
            cout << i;
            return 0;
        }
    }
    cout << -1;
    return 0;
}