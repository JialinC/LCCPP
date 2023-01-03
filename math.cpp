#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MAX_N = 1000;
const int MAX_L = 1000;
const int MAX_SQRT_B = 1000;
// gcd(a, b) = gcd(b, a % b)
// Euclidean algorithm O(log max(a, b))
int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b, a % b);
}

// must exist (x, y) make ax + by = gcd(a, b)


// prime
bool is__prime (int n) {
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0) return false;
    }
    return n != 1;
}

vector<int> divisor(int n){
    vector<int> res;
    for (int i = 1; i * i <= n; i++){
        if (n % i == 0){
            res.push_back(i);
            if (i != n/i) res.push_back(n / i);
        }
    }
    return res;
}

map<int, int> prime_factor(int n ){
    map<int, int> res;
    for (int i = 2; i * i <= n; i++){
        while (n % i == 0){
            ++res[i];
            n /= i;
        }
    }
    if (n != 1) res[n] = 1;
    return res;
}

// Sieve of Eratosthenes O(nlog(log(n)))
int prime[MAX_N];
bool is_prime[MAX_N + 1];

int sieve(int n){
    int p = 0;
    for (int i = 0; i <= n; i++) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++){
        if (is_prime[i]){
            prime[p++] = i;
            for (int j = 2 * i; j <= n; j += i) is_prime[j] = false;
        }
    }
    return p;
}

// prime number in range
typedef long long ll;

bool is_prime[MAX_L];
bool is_prime_small[MAX_SQRT_B];

void segment_sieve(ll a, ll b){
    for (int i = 0; (ll)i * i < b; i++) is_prime_small[i] = true;
    for (int i = 0; i < b - a; i++) is_prime[i] = true;

    for (int i = 2; (ll)i * i < b; i++){
        if(is_prime_small[i]) {
            for (int j = 2 * i; (ll)j * j < b; j += i) is_prime_small[j] = false;
            for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) is_prime[j - a] = false;
        }
    }

}

ll mod_pow(ll x, ll n, ll mod){
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    res;
}

ll mod_pow(ll x, ll n, ll mod){
    if (n == 0) return 1;
    ll res = mod_pow (x * x % mod, n / 2, mod);
    if (n & 1) res = res * x % mod;
    return res;
}