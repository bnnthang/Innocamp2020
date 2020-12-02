#include <bits/stdc++.h>

using namespace std;

string s, t;
vector<int> z;

int main() {
    cin >> s >> t;
    t = s + "*" + t;
    z.resize(t.size());
    for (int i = 1, l = 0, r = 0; i < (int)t.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < (int)t.size() && t[i + z[i]] == t[z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    vector<int> occurences;
    for (int i = 1 + s.size(); i <= (int)t.size(); ++i) {
        if (z[i] == (int)s.size()) {
            occurences.push_back(i - s.size());
        }
    }
    cout << occurences.size() << "\n";
    for (int i : occurences) cout << i << " ";
    return 0;
}