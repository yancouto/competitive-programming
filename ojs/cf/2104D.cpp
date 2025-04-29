#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) \
  int t;                 \
  scanf("%d", &t);       \
  for (int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 412345, M = 6123456;
int a[N], prime[N];
int cr[M];
ll sum_l[N];

int main() {
  int i, n;
  int ct_primes = 0;
  for (i = 2; i < (M + i - 1) / i; i++) {
    if (cr[i]) continue;
    for (int j = i * i; j < M; j += i) cr[j] = i;
  }
  for (i = 2; i < M; i++)
    if (cr[i] == 0) prime[ct_primes++] = i;
  sum_l[0] = prime[0];
  for (i = 1; i < N; i++) sum_l[i] = sum_l[i - 1] + prime[i];
  for_tests(t, tt) {
    scanf("%d", &n);
    ll sum = 0;
    for (i = 0; i < n; i++) scanf("%d", &a[i]), sum += a[i];
    sort(a, a + n);
    if (sum_l[n - 1] <= sum || n < 2) {
      puts("0");
      continue;
    }
    for (i = 0; i < n; i++) {
      sum -= a[i];
      if (sum_l[n - 2 - i] <= sum || i == n - 2) {
        printf("%d\n", i + 1);
        break;
      }
    }
  }
}