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

int n;
ll x;

const int N = 212345;
int S[N], sz[N], val[N], mn[N], mx[N];

int get(int i) {
  if(S[S[i]] == S[i]) return S[i];
  return S[i] = get(S[i]);
}

int merge(int a, int b) {
  if((a = get(a)) == (b = get(b))) return a;
  // if(sz[a] < sz[b]) swap(a, b);
  S[b] = a;
  sz[a] += sz[b];
  // mn[a] = min(mn[a], mn[b]);
  // mx[a] = max(mx[a], mx[b]);
  mx[a] = mx[b];
  return a;
}

ll go() {
  scanf("%d", &n);
  set<pii> all;
  for(int i = 0; i < n; i++) {
    scanf("%lld", &x);
    mn[i] = mx[i] = S[i] = i;
    sz[i] = 1;
    val[i] = x;
    all.insert(pii(x, i));
  }
  ll tot = 0;
  
  while(all.size() > 1) {
    auto [x, i] = *all.begin();
    debug("a[%d] = %lld\n", i, x);
    all.erase(all.begin());
    i = get(i);
    int nx = get((mx[i] + 1) % n);
    int pr = get((mn[i] - 1 + n) % n);
    debug("tot += %lld\n", min(val[nx], val[pr]));
    if(val[nx] < val[pr]) {
      val[merge(i, nx)] = val[nx];
      tot += val[nx];
    } else {
      val[merge(pr, i)] = val[pr];
      tot += val[pr];
    }
  }
  return tot;

}


int main() {
  int t;
  scanf("%d", &t);
  while(t--) printf("%lld\n", go());
}