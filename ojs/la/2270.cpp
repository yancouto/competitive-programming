#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[112345];

ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	int tt = 0;
	int n, t, i;
	while(scanf("%d %d", &n, &t) != EOF && n) {
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a + n);
		ll prob = 0;
		for(i = 0; i < n; i++) {
			//ll pr = prob;
			if(a[i] == 0) prob += (t < 0? n : 0);
			else if(a[i] > 0) {
				if(t >= 0) prob += (a + n) - upper_bound(a, a + n, t / a[i]);
				else prob += (a + n) - upper_bound(a, a + n, -((-t + a[i] - 1) / a[i]));
			} else {
				if(t >= 0) prob += lower_bound(a, a + n, -(t / (-a[i]))) - a;
				else prob += lower_bound(a, a + n, ((-t - a[i] - 1) / (-a[i]))) - a;
			}
			//printf("%d: add %lld\n", a[i], prob - pr);
		}
		ll div = ll(n) * ll(n);
		ll x = gcd(prob, div);
		printf("Case %d: %lld/%lld\n", ++tt, prob / x, div / x);
	}
}
