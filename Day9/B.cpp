#include <bits/stdc++.h>
 
using namespace std;
 
long long a[4];
 
int main() {
    for (int i = 0; i < 4; ++i) scanf("%lld", &a[i]);
    sort(a, a + 4);
    long long numer1 = a[0] * a[3] + a[1] * a[2];
    long long numer2 = a[1] * a[3] + a[0] * a[2];
    if (numer1 < numer2) {
        printf("%lld %lld %lld %lld", a[0], a[2], a[1], a[3]);
    } else {
        printf("%lld %lld %lld %lld", a[1], a[2], a[0], a[3]);
    }
}