#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

int n, h[N], suml[N], sumr[N], ds[N], fen[N];
string s;
vector<int> v;

void f_upd(int i, int x) {
    for (; i <= n; i += i & -i) fen[i] = max(fen[i], x);
}

int f_get(int i) {
    int res = -1;
    for (; i; i -= i & -i) res = max(fen[i], res);
    return res;
}

void f_upd1(int i, int x) {
    for (; i <= n; i += i & -i) fen[i] = min(fen[i], x);
}

int f_get1(int i) {
    int res = n;
    for (; i; i -= i & -i) res = min(fen[i], res);
    return res;
}

int idx(int x) {
    return lower_bound(v.begin(), v.end(), x, greater<int>()) - v.begin();
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        v.push_back(h[i]);
    }
    sort(v.begin(), v.end(), greater<int>());
    v.erase(unique(v.begin(), v.end()), v.end());
    memset(fen, -1, sizeof(fen));
    cin >> s;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            suml[i] = ds[i - 1];
        }
        int tmp = idx(h[i]) + 1;
        // cout << v[tmp] << "\n";
        int tmp1 = f_get(tmp);
        ds[i] = tmp1 < 0 ? 1 : ds[tmp1] + 1;
        f_upd(tmp, i);
    }
    fill(fen, fen + n + 1, n);
    for (int i = n - 1; i >= 0; --i) {
        if (i < n - 1) {
            sumr[i] = ds[i + 1];
        }
        int tmp = idx(h[i]) + 1;
        // cout << v[tmp] << "\n";
        int tmp1 = f_get1(tmp);
        ds[i] = tmp1 >= n ? 1 : ds[tmp1] + 1;
        f_upd1(tmp, i);
    }
    // for (int i = 0; i < n; ++i) cerr << ds[i] << " ";
    // cerr << "\n";
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') cout << suml[i] << " ";
        else cout << sumr[i] << " ";
    }
    return 0;
}