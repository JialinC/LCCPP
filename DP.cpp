#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_N = 1000;
const int MAX_M = 1000;
const int MAX_W = 1000;
const int MAX_V = 1000;
const int MAX_K = 1000;
double INF = numeric_limits<double>::infinity();
// bag & value
// use rec
int n, W;
int w[MAX_N], v[MAX_N];

int rec(int i, int j) {
    int res;
    if (i == n){
        res = 0;
    } else if (j < w[i]){
        res = rec(i+1,j);
    } else {
        res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
    }
    return res;
}

void solve(){
    printf("%d\n", rec(0, W));
}

// rec with memo
int dp[MAX_N +1][MAX_W + 1];

int rec(int i, int j) {
    if (dp[i][j] >= 0) {
        return dp[i][j];
    }
    int res;
    if (i == n){
        res = 0;
    } else if (j < w[i]){
        res = rec(i+1, j);
    } else {
        res = max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]);
    }
    return dp[i][j] = res;
}

void solve(){
    memset(dp, -1, sizeof(dp));
    printf("%d\n", rec(0,W));
}

// pure DP memo matrix
int dp[MAX_N + 1][MAX_W + 1];

void solve() {
    for (int i = n - 1; i >= 0; i--){
        for(int j = 0; j <= W; j++) {
            if (j < w[i]) {
                dp[i][j] = dp[i + 1][j];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
            }
        }
    }
    printf("%d\n",dp[0][W]);
}

// different formulation
void solve() {
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= W; j++){
            if(j < w[i]){
                dp[i + 1][j] = dp[i][j];
            } else {
                dp[i + 1][j] = max(dp[i][j], dp[i][j-w[i]] + v[i]);
            }
        }
    }
    printf("%d\n", dp[n][W]);
}

// yet another formulation
void solve() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= W; j++){
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j + w[i] <= W) {
                dp[i + 1][j + w[i]] = max(dp[i + 1][j + w[i]], dp[i][j] + v[i]);
            }
        }
    }
    printf("%d\n", dp[n][W]);
}

// longest common subsequence
int n, m;
char s[MAX_N], t[MAX_M];

int dp[MAX_N + 1][MAX_M + 1];
void solve(){
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            if (s[i] == t[j]){
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }
    printf("%d\n", dp[n][m]);
}

// bag with duplication O(nWW)
int dp[MAX_N + 1][MAX_W + 1];

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++){
            for (int k = 0; k * w[i] <= j; k++){
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - k * w[i]] + k * v[i]);
            }
        }
    }
    printf("%d\n",dp[n][W]);
}

// improved O(nW)
void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++){
            if (j < w[i]){
                dp[i + 1][j] = dp[i][j];
            } else {
                dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
            }
        }
    }
    printf("%d\n", dp[n][W]);
}

// 1D array
// 01 bag
int dp2[MAX_W + 1];
void solve() {
    for (int i = 0; i < n; i++){
        for (int j = W; j >= w[i]; j--) {
            dp2[j] = max(dp2[j],dp2[j - w[i]] + v[i]);
        }
    }
}

// full bag
void solve() {
    for (int i = 0; i < n; i++){
        for (int j = w[i]; j <= W; j++) {
            dp2[j] = max(dp2[j],dp2[j - w[i]] + v[i]);
        }
    }
    printf("%d\n", dp[W]);
}

// loop on value
int dp[MAX_N + 1][MAX_N * MAX_V + 1];

void solve(){
    fill(dp[0], dp[0] + MAX_N * MAX_V + 1, INF);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= MAX_N * MAX_V; j++){
            if (j < v[i]) {
                dp[i + 1][j] = dp[i][j];
            } else {
                dp[i + 1][j] = min(dp[i][j], dp[i][j - v[i]] + w[i]);
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= MAX_N * MAX_V; i++) if (dp[n][i] <= W) res = i;
    printf("%d\n", res);
}

// sum O(Ksum(m))
int n;
int K;
int a[MAX_N];
int mm[MAX_N];

bool dp[MAX_N + 1][MAX_K + 1];

void solve(){
    dp[0][0] = true;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= K; j++){
            for (int k = 0; k <= mm[i] && k*a[i] <= j; k++){
                dp[i + 1][j] |= dp[i][j - k * a[i]];
            }
        }
    }
    if (dp[n][K]) printf("YES");
    else printf("NO");
}

// O(nK)
int dp1[MAX_K];
void solve(){
    memset(dp, -1, sizeof(dp));
    dp1[0] = 0;
    for (int i = 0; i < n; i++){
        for(int j = 0; j <= K; j++){
            if (dp1[j] >= 0){
                dp1[j] = mm[i];
            } else if (j < a[i] || dp1[j - a[i]] <= 0){
                dp1[j] = -1;
            } else {
                dp1[j] = dp1[j - a[i]] -1;
            }
        }
    }
    if (dp[K] >= 0) printf("YES\n");
    else printf("No\n");
}

// LIS O(n2)
int n;
int a[MAX_N];
int dp[MAX_N];

void solve() {
    int res = 0;
    for (int i = 0; i < n; i++){
        dp1[i] = 1;
        for (int j = 0; j < i; j++){
            if (a[j] < a[i]){
                dp1[i] = max(dp1[i], dp1[j] + 1);
            }
        }
        res = max(res, dp1[i]);
    }
    printf("%d\n", res);
}

// O(nlogn)
int dp[MAX_N];

void solve(){
    fill (dp, dp + n, INF);
    for (int i = 0; i < n; i++){
        *lower_bound(dp1, dp1 + n, a[i]) = a[i];
    }
    printf("%d\n", lower_bound(dp1, dp1 + n, INF) - dp1);

}

// devide n into m
int n, m;
int dp[MAX_M + 1][MAX_N + 1];
int M;
void solve(){
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++){
        for(int j = 0; j <= 0; j++){
            if(j - i >= 0) {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - i]) % M;
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    printf("%d\n", dp[m][n]);
}


// multiple combination
int n, m;
int a[MAX_N];

int dp[MAX_N + 1][MAX_M + 1];

void solve() {
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < n; i++){
        for (int j = 1; j <= m; j++){
            if (j - 1 - a[i] >= 0){
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j] - dp[i][i - 1 -a[i]] + M) % M;
            } else {
                dp[i + 1][j] = (dp[i + 1][j - 1] + dp[i][j]) % M;
            }
        }
    }
    printf("%d\n", dp[n][m]);
}














