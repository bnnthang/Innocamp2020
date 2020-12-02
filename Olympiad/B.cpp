#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

int n, l, r, y, cnt[N];
vector<pair<int, int>> seg, pts;

int main() {
    cin >> n >> l >> r >> y;
    seg.emplace_back(l, r + 1);
    for (int i = 0; i < n; ++i) {
        int x, v, h;
        cin >> x >> v >> h;
        long long x1 = x + 1LL * y * h / v;
        long long x2 = x - 1LL * y * h / v;
        if (1LL * y * h % v == 0) --x1, ++x2;
        if (x1 >= x2)
            seg.emplace_back(max(x2, 1LL * l), min(x1, 1LL * r) + 1);
        // printf("%d %d %d\n", x, x2, x1);
    }
    for (pair<int, int> i : seg) {
        pts.emplace_back(i.first, 1);
        pts.emplace_back(i.second, -1);
    }
    sort(pts.begin(), pts.end());
    // for (pair<int, int> i : pts) {
    //     cerr << i.first << " " << i.second << endl;
    // }
    int cur = -1;
    for (int l = 0, r = 0; l < pts.size(); l = r) {
        while (r < pts.size() && pts[r].first == pts[l].first) ++r;
        for (int i = l; i < r; ++i)
            cur += pts[i].second;
        if (r == pts.size()) continue;
        cnt[cur] += pts[r].first - pts[l].first;
    }
    for (int i = 0; i <= n; ++i) {
        if (i) cnt[i] += cnt[i - 1];
        cout << cnt[i] << "\n";
    }
    return 0;
}