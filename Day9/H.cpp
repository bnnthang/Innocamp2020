#include <bits/stdc++.h>

using namespace std;

const int N = 402;

int n, m;
char ans[N][N];

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n >> m;
    for (int j = 1; j <= m; ++j) {
        int a;
        cin >> a;
        int lj = (j - 1) * 4 + 1, rj = j * 4;
        for (int ii = 4; ii; --ii) {
            for (int jj = rj; jj >= lj; --jj) {
                if (a > 0) {
                    ans[ii][jj] = '*';
                    --a;
                } else ans[ii][jj] = '.';
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int a;
            cin >> a;
            int li = (i - 1) * 4 + 1, ri = i * 4, lj = (j - 1) * 4 + 1, rj = j * 4;
            for (int jj = lj; jj <= rj; ++jj) {
                for (int ii = li; ii <= ri; ++ii) {
                    if (a > 0) {
                        ans[ii][jj] = '*';
                        --a;
                    } else ans[ii][jj] = '.';
                }
            }
        }
    }
    for (int i = 1; i <= n * 4; ++i) {
        for (int j = 1; j <= m * 4; ++j) {
            cout << ans[i][j];
        }
        cout << "\n";
    }
}