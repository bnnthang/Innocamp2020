#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<pair<int, int>> queries;

vector<int> SolveSub() {
    vector<int> res;
    for (int i = 1; i <= n; ++i) res.push_back(i);
    for (pair<int, int> i : queries) {
        int l = i.first - 1, r = i.second;
        reverse(res.begin(), res.begin() + l);
        reverse(res.begin() + l, res.begin() + r);
        reverse(res.begin(), res.begin() + r);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries.emplace_back(l, r);
    }
    vector<int> ans = SolveSub();
    for (int i : ans) printf("%d ", i);
    return 0;
}