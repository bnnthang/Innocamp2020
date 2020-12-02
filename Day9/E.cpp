#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

long long n;
string sn;
bool flag[20];

bool check(long long x) {
    string tmp = to_string(x);
    for (int i = 1; i < sz(tmp); ++i)
        if (tmp[i] == tmp[i - 1]) return false;
    return true;
}

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

template<typename T = int>
T Rand(T l, T r) {
    uniform_int_distribution<T> dis(l, r);
    return dis(gen);
}

string solve() {
    sn = to_string(n);
    flag[0] = true;
    for (int i = 1; i < sz(sn); ++i)
        flag[i] = flag[i - 1] & (sn[i] != sn[i - 1]);
    for (int i = sz(sn) - 1; i >= 0; --i) {
        if (!flag[i]) continue;
        // cerr << "clgt " << i << "\n";
        int j = i + 1;
        if (j >= sz(sn)) {
            return sn;
        }
        int xk = -1;
        if (sn[0] < '9') xk = 0;
        for (int k = j; k; --k)
            if (sn[k] < '9' && (sn[k] + 1 != sn[k - 1] || sn[k - 1] < '9')) {
                xk = k;
                break;
            }
        // cerr << "xk = " << xk << "\n";
        if (xk < 0) {
            // cerr << "clgt\n";
            string ans = "";
            for (int t = 0; t <= sz(sn); ++t)
                if (t % 2 == 0) ans += '1';
                else ans += '0';
            // cout << ans << "\n";
            return ans;
        } else {
            // cerr << "clgt\n";
            string ans = "";
            for (int t = 0; t < xk; ++t) ans += sn[t];
            // cerr << ans << endl;
            ++sn[xk];
            if (xk > 0 && sn[xk] == sn[xk - 1]) ++sn[xk];
            ans += sn[xk];
            // cerr << ans << endl;
            for (int t = xk + 1; t < sz(sn); ++t)
                if ((t - xk) % 2 == 0) ans += '1';
                else ans += '0';
            // cout << ans << "\n";
            return ans;
        }
    }
    return "crap";
}


int main() {
    // while (true) {
        // n = Rand(1, 100000000);
        // n = 31643992;
        // printf("n = %lld\n", n);
        cin >> n;
        ++n;
        string res = solve();
        // while (!check(n)) ++n;
        // string res1 = to_string(n);
        // cout << res << "\n" << res1 << "\n";
        cout << res;
        // if (res != res1) break;
    // }
    return 0;
}