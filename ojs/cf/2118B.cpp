#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#define debug
#else
#define debug printf
#endif

ll a[5123];

int main() {
  int t, n, j;
  ll k;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %lld", &n, &k);
    set<pii> ops;
    ll val = 0;
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
      for (j = 0; (a[i] >> j) > 0; j++) val += ((a[i] >> j) & 1);
      for (j = 0; (a[i] >> j) & 1ll; j++);
      ops.emplace((1ll << j), i);
    }
    while (true) {
      auto [cst, i] = *ops.begin();
      ops.erase(ops.begin());
      debug("k %lld op cst %lld val %lld i %d\n", k, cst, val, i);
      if (k < cst) break;
      a[i] += cst;
      val++;
      k -= cst;
      for (j = 0; (a[i] >> j) & 1ll; j++);
      ops.emplace((1ll << j), i);
    }
    printf("%lld\n", val);
  }
}