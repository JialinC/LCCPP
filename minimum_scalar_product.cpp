#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAX_N = 1000;


int n;
int v1[MAX_N], v2[MAX_N];

void solve() {
    sort(v1, v1 + n);
    sort(v2, v2 + n);
    ll ans = 0;
    for (int i; i < n; i++) ans += (ll)v1[i]*v2[n-1-i];
    printf("%lld\n", ans);
}