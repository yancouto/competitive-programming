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

char s[1123456];

int main() {
  int t;
  scanf("%d", &t);
  ll a, b, k;
  while(t--) { 
    scanf("%lld %lld %lld", &a, &b, &k);
    ll g = __gcd(a, b);
    if((a/g) <= k && (b/g) <= k) puts("1");
    else puts("2");
  }
}