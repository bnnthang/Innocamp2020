#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

const int lim = 1e6;

int n, f[lim], sumlen[lim], pre[lim];
vector<string> words;
deque<int> dq;

int digits(int x) {
    int res = 0;
    while (x > 0) {
        ++res;
        x /= 10;
    }
    return res;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    string sn;
    getline(cin, sn);
    n = stoi(sn);
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        while (s.back() != ' ') s.pop_back();
        string cur = "";
        for (int i = 0; i < sz(s); ++i) {
            if (s[i] == ' ') {
                if (cur.size() > 0) {
                    words.push_back(cur);
                    // cout << cur << "\n";
                    cur = "";
                }
            } else {
                cur += s[i];
            }
        }
    }
    for (int i = 1; i <= sz(words); ++i) {
        sumlen[i] = sumlen[i - 1] + sz(words[i - 1]);
    }
    for (int lastlen = 1; lastlen <= 5; ++lastlen) {
        vector<pair<int, int>> lines;
        lines.clear();
        for (int l = 1, r = 1; l <= sz(words); l = r) {
            int curline = sz(lines) + 1;
            while (r <= sz(words) && sumlen[r] - sumlen[l - 1] + r - l + 1 + 1 + digits(curline) + 1 + lastlen + 1 <= 280) ++r;
            lines.emplace_back(l, r);
        }
        if (digits(sz(lines)) == lastlen) {
            int curline = 0;
            cout << sz(lines) << "\n";
            for (pair<int, int> line : lines) {
                string txt = "";
                for (int i = line.first; i < line.second; ++i) {
                    txt += words[i - 1] + " ";
                }
                txt += "(" + to_string(++curline) + "/" + to_string(sz(lines)) + ")";
                cout << txt << "\n";
            }
            return 0;
        }
    }
    return 1;
}