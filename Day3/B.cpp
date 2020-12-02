#include <bits/stdc++.h>

using namespace std;

string s;
vector<int> z;

int main() {
    cin >> s;
    z.resize(s.size());
    for (int i = 1, l = 0, r = 0; i < (int)s.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < (int)s.size() && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        cout << z[i] << " ";
    }
    return 0;
}