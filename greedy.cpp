#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
// coin
const int V[6] = {1, 5,10, 50, 100, 500};
//input
int C[6];
int A;

void solve() {
    int ans = 0;

    for (int i = 5; i >= 0; i--){
        int t = min(A / V[i], C[i]);
        A -= t * V[i];
        ans += t;
    }

    printf("%d\n", ans);
}

// overlap interval
const int MAX_N = 100000;
// input
int N, S[MAX_N], T[MAX_N];
pair<int, int> itv[MAX_N];
void solve() {
    for (int i = 0; i < N; i++){
        itv[i].first = T[i];
        itv[i].second = S[i];
    }
    sort(itv, itv+N);

    int ans = 0, t = 0;
    for (int i = 0; i < N; i++){
        if (t < itv[i].second){
            ans++;
            t = itv[i].first;
        }
    }
    printf("%d\n",ans);
}

//dc order
int N;
char S[MAX_N+1];

void solve(){
    int a = 0, b = N - 1;
    while (a <= b){
        bool left = false;
        for (int i = 0; a + i <= b; i++){
            if(S[a+i] < S[b-i]){
                left = true;
                break;
            }
            else if (S[a+i]>S[b-i]){
                left = false;
                break;
            }
        }
        if (left) putchar(S[a++]);
        else putchar(S[b--]);
    }
    putchar('\n');
}

// cover
int N, R;
int X[MAX_N];

void solve() {
    sort(X, X + N);
    int i = 0, ans = 0;
    while (i < N){
        int s = X[i++];
        while (i < N && X[i] <= s + R) i++;
        int p = X[i-1];
        while (i < N && X[i] <= p + R) i++;
        ans++;
    }
    printf("%d\n", ans);
}

// cutting stick
typedef long long ll;
int N, L[MAX_N];

void solve() {
    ll ans = 0;

    while (N>1){
        int mii1 = 0, mii2 = 1;
        if (L[mii1] > L[mii2]) swap(mii1, mii2);
        for (int i = 2; i < N; i++){
            if (L[i] < L[mii1]){
                mii2 = mii1;
                mii1 = i;
            }
            else if(L[i] < L[mii2]){
                mii2 = i;
            }
        }

        int t = L[mii1]+L[mii2];
        ans += t;

        if (mii1 == N-1) swap(mii1,mii2);
        L[mii1] = t;
        L[mii2] = L[N-1];
        N--;
    }
    printf("%lld\n",ans);
}