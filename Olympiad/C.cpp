#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2;

int n, work[N], fen[N];
vector<int> idx[N];
priority_queue<int, vector<int>> pq;

void inc(int i, int x) {
    for (; i <= n; i += i & -i) {
        fen[i] += x;
    }
}

int sum(int i) {
    int res = 0;
    for (; i; i -= i & -i)
        res += fen[i];
    return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int d;
        cin >> d;
        idx[d].push_back(i);
    }
    for (int i = n; i; --i) {
        for (int j :idx[i]) pq.push(j);
        if (pq.empty()) {
            cout << -1;
            return 0;
        }
        work[i] = pq.top();
        pq.pop();
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += i - 1 - sum(work[i]);
        inc(work[i], 1);
    }
    cout << ans;
    return 0;
}