#include <bits/stdc++.h>

using namespace std;

vector<int> z_function(string s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    freopen("keepcounted.in", "r", stdin);
    freopen("keepcounted.out", "w", stdout);
    string s, cur = "";
    int ans = 0;
    cin >> s;
    for (int i = 0; i < (int)s.size(); ++i) {
        cur += s[i];
        reverse(cur.begin(), cur.end());
        vector<int> zf = z_function(cur);
        reverse(cur.begin(), cur.end());
        int tmp = *max_element(zf.begin(), zf.end());
        ans += cur.size() - tmp;
        cout << ans << "\n";
    }
    return 0;
}