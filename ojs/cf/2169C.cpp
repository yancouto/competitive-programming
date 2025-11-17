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

const int N = 312345;
int n;
ll a[N], pre[N];

ll go() {
  scanf("%d", &n);
  pre[0] = 0;
  for(int i = 1; i <=n ;i ++) {
    scanf("%lld", &a[i]);
    pre[i] = pre[i-1] + a[i];
  }
  ll S = accumulate(a+1, a + n+1, 0ll);
  debug("S %lld\n", S);
  ll mx = S;
  ll mxr = LLONG_MIN;
  for(ll i = n ; i >= 1; i--) {
    debug("mxr mx= %lld\n", i * i - i - pre[i]);
    mxr = max(mxr, i * i + i - pre[i]);
    debug("mx mx= %lld + %lld\n", pre[i-1] - i*i + i + S, mxr);
    mx = max(mx, pre[i-1] - i * i + i + S + mxr);
  }
  return mx;
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) printf("%lld\n", go());
}