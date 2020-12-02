#include <bits/stdc++.h>

#define sz(a) (int)a.size()

using namespace std;

const int N = 2002;

int n;
bool color[N][N]; // blue = 0, red = 1
int link[N][2], head, cycle[N];

void find_cycle(int x) {
    memset(link, -1, sizeof(link));
    head = -1;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (i != x) {
        if (head < 0) {
            head = i;
        } else {
            if (cnt == 1) {
                link[head][0] = i;
                link[i][1] = head;
            } else if (cnt == 2) {
                int u = link[head][0];
                link[head][1] = i;
                link[i][0] = head;
                link[i][1] = u;
                link[u][0] = i;
                if (color[i][u] != color[head][i]) head = i;
            } else {
                if (color[head][link[head][0]] != color[head][i]) {
                    int u = link[head][0];
                    link[head][0] = i;
                    link[i][1] = head;
                    link[i][0] = u;
                    link[u][1] = i;
                    if (color[head][i] == color[i][u]) head = u;
                    else head = i;
                } else {
                    int u = link[head][1];
                    link[head][1] = i;
                    link[i][0] = head;
                    link[i][1] = u;
                    link[u][0] = i;
                    if (color[head][i] == color[i][u]) head = u;
                    else head = i;
                }
            }
        }
        ++cnt;
    }
    int u = head;
    cnt = 0;
    do {
        cycle[++cnt] = u;
        u = link[u][0];
    } while (u > 0 && u != head);
}

int main() {
    // freopen("inp.txt", "r", stdin);
    cin >> n;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j < i; ++j) {
            char c;
            cin >> c;
            color[i][j] = color[j][i] = c == 'R';
        }
    for (int i = 1; i <= n; ++i) {;
        find_cycle(i);
        if (color[i][head] != color[head][cycle[2]])
            reverse(cycle + 2, cycle + n);
        cout << n << "\n" << i << " ";
        for (int j = 1; j < n; ++j) cout << cycle[j] << " ";
        cout << "\n";
    }
    return 0;
}