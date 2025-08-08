#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

const int N = 212345;
int l[N], r[N];
ll p[N], q[N];
ll pre[N];
vector<int> start[N];
  int n, m;

ll fexp(ll x, ll p) {
  ll ans = 1;
  for(; p; x = mod(x * x), p /= 2)
    if(p & 1)
      ans = mod(ans * x);
  return ans;
}

ll inv(ll x) {
  return fexp(x, modn - 2);
}

ll frac(ll x, ll p) {
  return mod(x * inv(p));
}

ll memo[N];
ll solve(int k) {
  if(k == m + 1) return 1;
  if(start[k].empty()) return 0;
  ll &ans = memo[k];
  if(ans == -1) {
    ans = 0;
    for(int i : start[k]) {
      ll with_i = mod(solve(r[i]+1) * frac(p[i], q[i]));
      with_i = mod(with_i * frac(pre[r[i]], pre[l[i] - 1]));
      with_i = frac(with_i, frac(q[i] - p[i], q[i]));
      ans = mod(ans + with_i);
    }
  }
  return ans;
}

int main() {
  memset(memo, -1, sizeof memo);
  scanf("%d %d", &n, &m);
  for(int i = 0; i < n; i++) {
    scanf("%d %d %lld %lld", &l[i], &r[i], &p[i], &q[i]);
    start[l[i]].pb(i);
  }
  ll cur = 1;
  pre[0] = 1;
  for(int i = 1; i <= m; i++) {
    for(int j : start[i])
      cur = mod(cur * frac((q[j] - p[j]), q[j]));
    pre[i] = cur;
  }
  printf("%lld\n", solve(1));
}