#include "headers.h"

int n, k;
int a[MAX_N];

void solve(){
    int lb = -1, ub = n;

    while (ub - lb > 1){
        int mid = (lb + ub) / 2;
        if (a[mid] > = k){
            ub = mid;
        } else {
            lb = mid;
        }
    }
    printf("%d\n", ub);
}

int N, K;
double L[MAX_N];

bool C(double x){
    int num = 0;
    for (int i = 0; i < N; i++){
        num += (int)(L[i] / x);
    }
    return num >= K;
}

void solve() {
    double lb = 0, ub = INF;

    for (int i = 0; i < 100; i++){
        double mid = (lb + ub) / 2;
        if (C(mid)) lb = mid;
        else ub = mid;
    }

    printf("%.2f\n", floor(ub * 100)/100);
}

// Aggressive cows
int N, M;
int x[MAX_N];

bool C(int d){
    int last = 0;
    for (int i = 1; i < M; i++){
        int crt = last + 1;
        while (crt < N && x[crt] - x[last] < d) {
            crt++;
        }
        if (crt == N) return false;
        last = crt;
    }
    return true;
}

void solve() {
    sort(x, x + N);
    int lb = 0, ub = INF;

    while (ub - lb > 1) {
        int mid = (lb + ub) / 2;
        if (C(mid)) lb = mid;
        else ub = mid;
    }
    printf("%d\n", lb);
}

int n, k;
int w[MAX_N], v[MAX_N];

double y[MAX_N];

bool C(doule x){
    for (int i = 0; i < n; i++){
        y[i] = v[i] - x * w[i];
    }
    sort(y, y + n);
    double sum = 0;
    for (int i = 0; i < k; i++){
        sum += y[n - i -1];
    }

    return sum >= 0;
}

void solve() {
    double lb = 0, ub = INF;
    for (int i = 0; i < 100; i++){
        double mid = (lb + ub) / 2;
        if (C(mid)) lb = mid;
        else ub = mid;
    }

    printf("%.2f\n", ub);
}

// cpp lower_bound
template <class ForwardIterator, class T>
  ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
  ForwardIterator it;
  iterator_traits<ForwardIterator>::difference_type count, step;
  count = distance(first,last);
  while (count>0)
  {
    it = first; step=count/2; advance (it,step);
    if (*it<val) {                 // or: if (comp(*it,val)), for version (2)
      first=++it;
      count-=step+1;
    }
    else count=step;
  }
  return first;
}

// cpp upper_bound
template <class ForwardIterator, class T>
  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
  ForwardIterator it;
  iterator_traits<ForwardIterator>::difference_type count, step;
  count = std::distance(first,last);
  while (count>0)
  {
    it = first; step=count/2; std::advance (it,step);
    if (!(val<*it))                 // or: if (!comp(val,*it)), for version (2)
      { first=++it; count-=step+1;  }
    else count=step;
  }
  return first;
}