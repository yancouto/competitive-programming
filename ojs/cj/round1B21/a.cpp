#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define mp make_pair
const ll modn = 360ll * 12ll * 10000000000ll;
inline ll mod(ll x) { return x % modn; }

ll e9 = 1000000000ll;
ll h, m, s, n;

vector<pii> pos;

pii from(vector<ll> all) {
  sort(all.begin(), all.end());
  return pii(all[2] - all[0], all[1] - all[0]);
}

void go() {
  ll a1, a2, a3;
  scanf("%lld %lld %lld", &a1, &a2, &a3);
  vector<ll> v = {a1, a2, a3};
  pii th = from(v);
  // printf("looking for %lld, %lld\n", th.fst, th.snd);
  for (int i = 0; i < 60 * 60 * 12; i++) {
    if (pos[i] == th) {
      // printf("Found at %d!\n", i);
      n = 0;
      s = (i % 60);
      m = (i / 60) % 60;
      h = (i / (60 * 60));
      return;
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (ll i = 0; i < 60 * 60 * 12; i++) {
    ll h = e9 * i;
    ll m = mod(h * 12ll);
    ll s = mod(h * 720ll);
    vector<ll> a = {h, m, s};
    pos.pb(from(a));
  }
  // auto x = pos[6 * 60 * 60 + 30 * 60];
  //    printf("(%lld, %lld)\n", x.fst, x.snd);
  for (int tt = 1; tt <= t; tt++) {
    go();
    printf("Case #%d: %lld %lld %lld %lld\n", tt, h, m, s, n);
  }
  return 0;
}