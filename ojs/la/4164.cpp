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
	int n, i, j;
	ll p, k;
	for_tests(tn, tt) {
		scanf("%d", &n);
		ll d = 1;
		ll N = 1;
		for(i = 0; i < n; i++) {
			scanf("%lld %lld", &p, &k);
			ll v = 1;
			ll nd = 0;
			for(j = 0; j < k; j++) {
				nd = mod(nd + d * v);
				v = mod(v * p);
			}
			N = mod(N * v);
			d = nd = mod(nd + d * mod(v * ll(k + 1ll)));
		}
		printf("Case %d: %lld\n", tt, mod(N + d));
	}
}
