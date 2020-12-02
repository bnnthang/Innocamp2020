#include <bits/stdc++.h>
  
using namespace std;
  
typedef long long ll;
  
ll xor_sum(ll x) {
    switch (x % 4) {
    case 0:
        return x;
    case 1:
        return 1;
    case 2:
        return x + 1;
    default:
        return 0;
    }
}
  
int n;
vector<pair<ll, ll>> a;
  
int main() {
    cin >> n;
    a.resize(n);
    ll nim = 0;
    for (pair<ll, ll>& i : a) {
        cin >> i.first >> i.second;
        nim ^= xor_sum(i.second) ^ xor_sum(i.first - 1);
    }
    if (nim == 0) {
        cout << "Lose";
    } else {
        cout << "Win\n";
        int d = __lg(nim);
        for (pair<ll, ll> i : a) {
            if (i.first >> d & 1) {
                cout << i.first << " " << (i.first ^ nim);
                break;
            } else {
                ll tmp = 1LL << d;
                for (int j = 60; j > d; --j) tmp += (i.first >> j & 1) << j;
                if (tmp <= i.second) {
                    cout << tmp << " " << (tmp ^ nim);
                    break;
                }
            }
        }
    }
    return 0;
}