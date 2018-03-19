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

int main() {
	for_tests(tn, tt) {
		ll x;
		scanf("%lld", &x);
		ll l = 0, r = 1e6;
		while(l < r) {
			ll m = (l + r + 1) / 2;
			if((m * (m + 1ll)) / 2 <= x) l = m;
			else r = m - 1;
		}
		ll sq = l;
		ll best = LLONG_MAX;
		for(ll i = sq - 2; i <= sq + 3; i++) {
			if(i < 0) continue;
			best = min(best, i + abs((i * (i + 1ll)) / 2ll - x));
		}
		printf("%lld\n", best);
	}
}
