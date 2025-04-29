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

const int N = 212345;

ll a[N], ans[N], sum_r[N], mn_r[N];

int main() {
  int i, n;
  for_tests(t, tt) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%lld", &a[i]);
    sum_r[n] = 0;
    mn_r[n] = LLONG_MAX;
    for (i = n - 1; i >= 0; i--)
      sum_r[i] = sum_r[i + 1] + a[i], mn_r[i] = min(mn_r[i + 1], a[i]);
    ans[n] = sum_r[0];
    ll mx_l = LLONG_MIN;
    for (i = 0; i < n - 1; i++) {
      mx_l = max(mx_l, a[i]);
      ans[n - i - 1] = max(sum_r[i + 1], sum_r[i + 1] - a[i + 1] + mx_l);
    }
    for (i = 1; i <= n; i++) printf("%lld%c", ans[i], " \n"[i == n]);
  }
}