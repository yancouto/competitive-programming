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
const int N = 212345;
int a[2][N], mxru[N], mnru[N], mxld[N], mnld[N];

inline bool up(int l, int r, int j) {
  return mxru[j] <= r && mnru[j] >= l;
}

bool ok(int l, int r) {
  if(a[0][0] < l || a[0][0] > r || a[1][n-1] < l || a[1][n-1] > r) return false;
  assert(up(l, r, 0));
  int ul = 0, ur = n - 1;
  while(ul < ur) {
    int um = (ul + ur + 1) / 2;
    if(up(l, r, um)) ul = um;
    else ur = um - 1;
  }
  assert(up(l, r, ul));
  return (mxld[ul] <= r && mnld[ul] >= l);
}

ll go() {
  scanf("%d", &n);
  for(int i = 0; i < 2; i++)
    for(int j = 0; j < n; j++)
      scanf("%d", &a[i][j]);
  mxru[0] = mnru[0] = a[0][0];
  for(int j = 1; j < n; j++) {
    mxru[j] = max(mxru[j-1], a[0][j]);
    mnru[j] = min(mnru[j-1], a[0][j]);
  }
  mxld[n-1] = mnld[n-1] = a[1][n-1];
  for(int j = n - 2; j >= 0; j--) {
    mxld[j] = max(mxld[j+1], a[1][j]);
    mnld[j] = min(mnld[j+1], a[1][j]);
  }
  ll ans = 0;
  for(int i = 1; i <= 2*n; i++) {
    if(!ok(i, 2*n)) continue;
    int jl = i, jr = 2*n;
    while(jl < jr) {
      int jm = (jl + jr) / 2;
      if(ok(i, jm)) jr = jm;
      else jl = jm + 1;
    }
    // printf("[%d..%d]\n", i, jl);
    ans += ll(2 * n - jl + 1);
  }
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) printf("%lld\n", go());
}