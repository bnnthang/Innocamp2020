#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 2, K = 19, MOD = 1e9 + 7;

int n, q, h[N], hs[N], nxtl[K][N], vall[K][N], nxtr[K][N], valr[K][N];
vector<int> st;

void Prep() {
    for (int i = 1; i <= n; ++i) hs[i] = (hs[i - 1] + h[i]) % MOD;
    memset(nxtl, -1, sizeof(nxtl));
    memset(nxtr, -1, sizeof(nxtr));
    h[0] = h[n + 1] = INT_MAX;
    st.push_back(n + 1);
    for (int i = n; i; --i) {
        while (h[i] > h[st.back()]) st.pop_back();
        nxtr[0][i] = st.back();
        valr[0][i] = (1LL * h[i] * (nxtr[0][i] - 1 - i) % MOD - (hs[nxtr[0][i] - 1] - hs[i] + MOD) % MOD + MOD) % MOD;
        for (int j = 1; j < K; ++j) {
            if (nxtr[j - 1][i] < 0) break;
            nxtr[j][i] = nxtr[j - 1][nxtr[j - 1][i]];
            valr[j][i] = (valr[j - 1][i] + valr[j - 1][nxtr[j - 1][i]]) % MOD;
        }
        st.push_back(i);
    }
    st.clear();
    st.push_back(0);
    for (int i = 1; i <= n; ++i) {
        while (h[i] > h[st.back()]) st.pop_back();
        nxtl[0][i] = st.back();
        vall[0][i] = (1LL * h[i] * (i - 1 - nxtl[0][i]) % MOD - (hs[i - 1] - hs[nxtl[0][i]] + MOD) % MOD + MOD) % MOD;
        for (int j = 1; j < K; ++j) {
            if (nxtl[j - 1][i] < 0) break;
            nxtl[j][i] = nxtl[j - 1][nxtl[j - 1][i]];
            vall[j][i] = (vall[j - 1][i] + vall[j - 1][nxtl[j - 1][i]]) % MOD;
        }
        st.push_back(i);
    }
}

int Query(int l, int r) {
    int res = 0, tl = l, tr = r;
    for (int j = K - 1; j >= 0; --j) {
        if (0 <= nxtr[j][tl] && nxtr[j][tl] <= r) {
            (res += valr[j][tl]) %= MOD;
            tl = nxtr[j][tl];
        }
    }
    for (int j = K - 1; j >= 0; --j) {
        if (0 <= nxtl[j][tr] && nxtl[j][tr] >= l) {
            (res += vall[j][tr]) %= MOD;
            tr = nxtl[j][tr];
        }
    }
    if (tl > tr) {
        swap(tl, tr);
        (res += MOD - (1LL * min(h[tl], h[tr]) * (tr - tl - 1) % MOD - (hs[tr - 1] - hs[tl] + MOD) % MOD + MOD) % MOD) %= MOD;
    } else if (tl < tr) {
        (res += (1LL * min(h[tl], h[tr]) * (tr - tl - 1) % MOD - (hs[tr - 1] - hs[tl] + MOD) % MOD + MOD) % MOD) %= MOD;
    }
    return res;
}

int main() {
    // freopen("inp.txt", "r", stdin);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
    Prep();
    int ans = 0;
    for (int iq = 0; iq < q; ++iq) {
        int l, r;
        scanf("%d%d", &l, &r);
        int tmp = Query(l, r);
        // printf("%d\n", tmp);
        (ans += tmp) %= MOD;
    }
    printf("%d", ans);
    return 0;
}