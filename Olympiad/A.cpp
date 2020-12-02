#include <bits/stdc++.h>

using namespace std;

int n;
string s;
vector<int> ones;

int main() {
    cin >> n >> s;
    s = '1' + s + '1';
    int lim = n;
    for (int i = 0; i < n + 2; ++i)
        if (s[i] == '1') {
            ones.push_back(i);
            if (ones.size() > 2 && i < n + 1) {
                lim = min(lim, ones.back() - ones[ones.size() - 2]);
            }
        }
    cerr << lim << endl;
    if (ones.size() < 3) {
        cout << (n - 1) << "\n";
        return 0;
    }
    int l = 0, r = lim, ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        // fprintf(stderr, "%d %d %d\n", l, r, m);
        bool flag = false;
        int cnt2 = 0;
        if (ones[0] + 1 + m * 2 <= ones[1] || ones[ones.size() - 2] + m * 2 < ones.back()) {
            flag = true;
        }
        if (1 + m <= ones[1]) ++cnt2;
        if (ones[ones.size() - 2] + m < ones.back()) ++cnt2;
        for (int i = 2; i < (int)ones.size() - 1; ++i) {
            if (ones[i - 1] + m * 3 <= ones[i]) {
                flag = true;
                break;
            }
            if (ones[i - 1] + m * 2 <= ones[i]) ++cnt2;
        }
        if (cnt2 > 1) flag = true;
        // cerr << m << " " << flag << "\n";
        if (flag) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}