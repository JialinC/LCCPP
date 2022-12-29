#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX_N = 1000;
const int MAX_M = 1000;

// oil fill
int L, P, N;
int A[MAX_N + 1], B[MAX_N + 1];

void solve(){
    A[N] = L;
    B[N] = 0;
    N++;

    priority_queue<int> que;
    int ans = 0, pos = 0, tank = P;

    for (int i = 0; i < N; i++){
        int d = A[i] - pos;

        while(tank - d < 0){
            if(que.empty()){
                puts("-1");
                return;
            }
            tank += que.top();
            que.pop();
            ans++;
        }

        tank -= d;
        pos = A[i];
        que.push(B[i]);
    }
    printf("%d\n", ans);
}


// fence repair
typedef long long ll;

int N, LL[MAX_N];

void solve() {
    ll ans = 0;
    priority_queue<int, vector<int>, greater<int>> que;
    for (int i = 0; i < N; i++){
        que.push(LL[i]);
    }

    while (que.size() > 1){
        int l1, l2;
        l1 = que.top();
        que.pop();
        l2 = que.top();
        que.pop();

        ans += l1 + l2;
        que.push(l1 + l2);
    }
    printf("%lld\n", ans);
}

int par[MAX_N];
int rk[MAX_N];

void init(int n) {
    for (int i = 0; i < n; i++){
        par[i] = i;
        rk[i] = 0;
    }
}

int find (int x){
    if (par[x] == x){
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

void unite(int x, int y){
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rk[x] < rk[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rk[x] == rk[y]) rk[x]++;
    }
}

bool same(int x, int y){
    return find(x) == find(y);
}

int N, K;
int T[MAX_N], X[MAX_N], Y[MAX_N];

void solve(){
    init(N * 3);

    int ans = 0;
    for (int i = 0; i < K; i++){
        int t = T[i];
        int x = X[i] - 1, y = Y[i] - 1;
        if ( x < 0 || N <= x || y < 0 || N <= y){
            ans++;
            continue;
        }
        if (t == 1){
            if (same(x, y + N) || same(x, y + 2*N)){
                ans++;
            } else {
                unite(x, y);
                unite(x + N, y + N);
                unite(x + N * 2, y + N * 2);
            }
        } else {
            if (same(x, y) || same(x, y + 2 * N)){
                ans++;
            } else {
                unite(x, y + N);
                unite(x + N, y + 2 * N);
                unite(N + 2 * N, y);
            }
        }
    }
    printf("%d\n", ans);
}