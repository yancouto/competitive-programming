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
#define right r_
#define left l_

const int N = 212345;

ll p[N], d[N], a[N];
int right[N], left[N];
int leaves[2][N], seen[2][N];

bool go(int u, bool from_r) {
  if (seen[from_r][u] == 1) return false;
  if (seen[from_r][u]) return leaves[from_r][u];
  seen[from_r][u] = 1;
  bool lv;
  if (from_r) {
    if (left[u] == -1)
      lv = true;
    else
      lv = go(left[u], false);
  } else {
    if (right[u] == -1)
      lv = true;
    else
      lv = go(right[u], true);
  }
  leaves[from_r][u] = lv;
  seen[from_r][u] = 2;
  debug("go(%d, %d) = %d\n", u, from_r, lv);
  return lv;
}

int main() {
  int i, n, t, q;
  ll k;
  scanf("%d", &t);
  while (t--) {
    scanf("%d %lld", &n, &k);
    for (i = 0; i < n; i++) scanf("%lld", &p[i]);
    for (i = 0; i < n; i++) scanf("%lld", &d[i]), seen[0][i] = seen[1][i] = 0;
    map<ll, int> mn, mx;
    for (i = n - 1; i >= 0; i--) {
      ll val = (p[i] - (d[i] % k) + k) % k;
      if (mn.count(val))
        right[i] = mn[val];
      else
        right[i] = -1;
      debug("right[%d] = %d\n", i, right[i]);
      mn[val] = i;
    }
    for (i = 0; i < n; i++) {
      ll val = (p[i] + d[i]) % k;
      if (mx.count(val))
        left[i] = mx[val];
      else
        left[i] = -1;
      debug("left[%d] = %d\n", i, left[i]);
      mx[val] = i;
    }
    scanf("%d", &q);
    set<ll> all;
    for (i = 0; i < q; i++) {
      scanf("%lld", &a[i]);
      all.insert(a[i]);
    }
    mn.clear();
    map<ll, bool> ans;
    for (i = n; i >= 0; i--) {
      if (i < n) {
        ll val = (p[i] - (d[i] % k) + k) % k;
        mn[val] = i;
        debug("Add val %lld for i %d\n", val, i);
      }
      while (!all.empty()) {
        ll cp = *all.rbegin();
        if (i > 0 && p[i - 1] >= cp) break;
        debug("p %lld\n", cp);
        if (!mn.count(cp % k))
          ans[cp] = true;
        else
          ans[cp] = go(mn[cp % k], true);
        all.erase(cp);
      }
    }
    for (i = 0; i < q; i++)
      if (ans[a[i]])
        puts("Yes");
      else
        puts("No");
  }
}