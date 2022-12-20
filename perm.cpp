#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_N = 100000000;
bool used[MAX_N];
int perm[MAX_N];

void permutation1(int pos, int n){
    if(pos == n){
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            perm[pos] = i;
            used[i] = true;
            permutation1(pos + 1, n);
            used[i] = false;
        }
    }
    return;
}

int perm2[MAX_N];

void permutation2(int n){
    for (int i = 0; i < n; i++){
        perm2[i] = i;
    }
    do {
        // do
    } while (next_permutation(perm2, perm2 + n));
    return;
}

