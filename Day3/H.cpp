#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

const int N = 10002, M = 1002;

string a, b;
int nxt[M][26], f[N][M];
vector<int> pfb;

inline void Opt(int& x, int y) {
    x = min(x, y);
}

void print() {
    // for (int i = 0; i <= sz(b); ++i) {
    //     cout << a << "\n";
    //     for (char c = 'a'; c <= 'z'; ++c) {
    //         printf("nxt[%d][%c] = %d\n", i, c, nxt[i][c - 'a']);
    //     }
    // }
    for (int i = 0; i <= sz(a); ++i) {
        for (int j = 0; j < sz(b); ++j) {
            printf("f[%d][%d] = %d\n", i, j, f[i][j]);
        }
    }
}

int main() {
    cin >> a >> b;
    pfb = prefix_function(b);
    for (int i = 0; i < sz(b); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (i < sz(b) - 1 && c == b[i + 1]) {
                // printf("%d %c\n", i, c);
                nxt[i + 1][c - 'a'] = i + 2;
                continue;
            }
            int j = pfb[i];
            while (j > 0 && c != b[j])
                j = pfb[j - 1];
            if (c == b[j])
                j++;
            nxt[i + 1][c - 'a'] = j;
        }
    }
    // print();
    for (char c = 'a'; c <= 'z'; ++c)
        if (c == b[0]) {
            nxt[0][c - 'a'] = 1;
        } else {
            nxt[0][c - 'a'] = 0;
        }
    fill(f[0], f[N], INT_MAX);
    f[0][0] = 0;
    for (int i = 0; i < sz(a); ++i) {
        for (int j = 0; j < sz(b); ++j) {
            if (f[i][j] == INT_MAX) continue;
            if (nxt[j][a[i] - 'a'] < sz(b)) {
                Opt(f[i + 1][nxt[j][a[i] - 'a']], f[i][j]);
            }
            Opt(f[i + 1][j], f[i][j] + 1);
        }
    }
    // print();
    int ans = *min_element(f[sz(a)], f[sz(a)] + sz(b));
    cout << ans << "\n";
    return 0;
}