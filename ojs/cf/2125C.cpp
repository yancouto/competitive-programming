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

ll solve(ll r) {
    ll ans = r - 1;
    ll p[] = {2, 3, 5, 7};
    for(int i = 1; i < (1 << 4); i++) {
        ll n = 1;
        int ct = 0;
        for(int j = 0; j < 4; j++)
            if((i >> j) & 1)
                n = n * p[j], ct++;
        ll amount = r / n;
        if(ct & 1) ans -= amount;
        else ans += amount;
    }
    return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  ll a, b;
  while(t--) { 
    scanf("%lld %lld", &a, &b);
    printf("%lld\n", solve(b) - solve(a-1));
  }
}