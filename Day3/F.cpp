#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;
using ll = long long;

const int N = 2e5 + 2;
const ll BASE = 31;
//const ll MOD = 3000000003;

ll pw[N];
void Prep() {
    pw[0] = 1;
    for (int i = 1; i < N; ++i)
        pw[i] = pw[i - 1] * BASE;
}

struct HashTable {
    vector<ll> tab;

    HashTable() { tab.clear(); }

    void Build(string& s) {
        tab.assign(sz(s) + 2, 0);
        for (int i = 1; i <= sz(s); ++i) {
            tab[i] = (tab[i - 1] * BASE + (s[i - 1] - 'A' + 1));
        }
    }

    ll GetRange(int l, int r) {
        ll ret = tab[r] - tab[l - 1] * pw[r - l + 1];
        return ret;
    }
};

int n;
vector<string> s;
vector<HashTable> hs;
map<ll, int> cnt;
set<ll> vl;

bool Check(int m, ll& hsh) {
    cnt.clear();
    for (int i = 1; i <= n; ++i) {
        vl.clear();
        for (int j = 1; j + m - 1 <= sz(s[i]); ++j) {
            vl.insert(hs[i].GetRange(j, j + m - 1));
        }
        for (ll j : vl) {
            if ((++cnt[j]) >= n) {
                hsh = j;
                return true;
            }
        }
    }
    return false;
}

void Print(int len, ll expect) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j + len - 1 <= sz(s[i]); ++j) {
            // ll tmp = hs[i].GetRange(j, j + len - 1);
            if (hs[i].GetRange(j, j + len - 1) == expect) {
                cout << s[i].substr(j - 1, len);
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    Prep();
    cin >> n;
    s.resize(n + 2);
    hs.resize(n + 2);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        hs[i].Build(s[i]);
    }
    int l = 1, r = N, len = 0;
    ll hsh = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        ll thsh;
        if (Check(m, thsh)) {
            len = m;
            hsh = thsh;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    Print(len, hsh);
    return 0;
}