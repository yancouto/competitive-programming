#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 312345;

ll a[N];
ll n, k;
ll modn;
const ll mod(ll x) { return x % modn; }

ll fexp(ll x, ll p) {
  ll ans = 1;
  for (ll y = x; p; p >>= 1, y = mod(y * y))
    if (p & 1) ans = mod(ans * y);
  return ans;
}

int main() {
  int i;
  scanf("%lld %lld %lld", &n, &modn, &k);
  map<int, int> cubed;
  for (i = 0; i < n; i++)
    scanf("%lld", &a[i]), cubed[mod(a[i] * mod(a[i] * a[i]))]++;
  ll ct = 0;
  for (i = 0; i < n; i++) {
    ll b = a[i];
    ll a3 = mod(mod(a[i] * a[i]) * a[i]);
    if (a3 == 0) {
      if (k == 0) ct += n - 1;
      continue;
    }
    assert(mod(a3 * fexp(a3, modn - 2)) == 1);
    ll b3 = mod(k * fexp(a3, modn - 2));
    ct += cubed[b3];
    if (a3 == b3) ct--;
  }
  printf("%lld\n", ct / 2);
}