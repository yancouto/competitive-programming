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

int k, l;

bool pos(ll g) {
	ll cur = 0;
	int all = 0;
	for(int i = 0; i < l; i++) {
		cur += 2 * i + 1;
		if(cur >= g) cur = 0, all++;
	}
	return all >= k;
}

int main() {
	while(scanf("%d %d", &l, &k) != EOF) {
		ll l = 1, r = 1e16;
		while(l < r) {
			ll m = (l + r + 1) / 2;
			if(pos(m)) l = m;
			else r = m - 1;
		}
		printf("%lld\n", l);
	}
}
