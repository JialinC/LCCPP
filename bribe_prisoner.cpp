#include "headers.h"

int P, Q, A[MAX_Q + 2];
int dp[MAX_Q + 1][MAX_Q + 2];

// example
// P = 20 Q = 3 A = {3, 6, 14}
// A = [0, 3, 6, 14, 21]
// dp = [0, X, 0, 0, 0]
//      [0, 0, X, 0, 0]
//      [0, 0, 0, X, 0]
//      [0, 0, 0, 0, X]
//
// w = 2
// i = 0 j = 2
// k = 1
// dp[0][1] + dp[1][2]

// i = 1 j = 3
// k = 2
// dp[1][2] + dp[2][3]

// i = 2 j = 4
// k = 3
// dp[2][3] + dp[3][4]

// w = 3
// i = 0 j = 3
// k = 1
// dp[0][1] + dp[1][3]
// k = 2
// dp[0][2] + dp[2][3]

// i = 1 j = 4
// k = 2
// dp[1][2] + dp[2][4]
// k = 3
// dp[1][3] + dp[3][4]

// w = 4
// i = 0 j = 4
// k = 1
// dp[0][1] + dp[1][4]
// k = 2
// dp[0][2] + dp[2][4]
// k = 3
// dp[0][3] + dp[3][4]

void solve(){
    A[0] = 0;
    A[Q + 1] = P + 1;

    for (int q = 0; q <= Q; q++){
        dp[q][q + 1] = 0;
    }

    // not include the start but include the end
    for (int w = 2; w <= Q + 1; w++){
        for (int i = 0; i + w <= Q + 1; i++){
            int j = i + w; // end index
            int t = INT_MAX;

            for (int k = i + 1; k < j; k++){
                t = min(t, dp[i][k] + dp[k][j]);
            }

            dp[i][j] = t + A[j] - A[i] - 2;
        }
    }

    printf("%d\n", dp[0][Q + 1]);
}