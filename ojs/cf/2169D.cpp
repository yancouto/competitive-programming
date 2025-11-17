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

ll solve(ll x, ll y, ll k) {
  debug("solve(%lld, %lld, %lld)\n", x, y, k);
  if(x == 0) return k;
  if(y == 1 || k > 1000000000000ll) return -1;
  if(k < y) return k;
  ll prev = 0;
  ll z = k;
  int its = 0;
  // debug("(%lld) > %lld\n", (z/y), (prev/y));
  while((z / y) > (prev / y)) {
    its++;
    debug("(%lld)=%lld/%lld > (%lld)=%lld/%lld\n", (z/y),z,y, (prev/y),prev,y);
    ll oz = z;
    debug("z %lld += %lld\n", z, (z/y) - (prev/y));
    z = z + ((z / y) - (prev / y));
    prev = oz;
  }
  debug("its %d\n", its);
  assert(its > 0);
  if(true) {
    ll added = z - k;
    ll until = (ll(z / y) + 1ll) * y - 1ll;
    debug("cur z %lld until %lld added %lld\n", z, until, added);
    ll a = (until - z) / added;
    a = min(a, x - 1);
    debug("skipped %lld, from z %lld to %lld\n", a, z, z + a * added);
    return solve(x - 1 - a, y, z + a * added);
  }
  return solve(x - 1, y, z);
}

ll go() {
  ll x, y, k;
  scanf("%lld %lld %lld", &x, &y, &k);
  ll ans = solve(x, y, k);
  if(ans > 1000000000000ll) return -1;
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) printf("%lld\n", go());
}