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
#define debug(...) ((void) 0)

ll h[212], d;
int n;
ll memo[112][21234];
int l[21234], r[21234], e[21234];

int main() {
	int i, j, k;
	for_tests(t, tt) {
		scanf("%d %lld", &n, &d);
		for(i = 0; i < n; i++) scanf("%lld", &h[i]);
		vector<ll> pos;
		ll mn = *min_element(h, h + n);
		ll mx = *max_element(h, h + n);
		for(i = 0; i < n; i++)
			for(j = -(i + 1); j <= (i + 1); j++) {
				ll x = h[i] + ll(j) * d;
				if(x >= mn && x <= mx)
					pos.pb(h[i] + ll(j) * d);
			}
		sort(pos.begin(), pos.end());
		pos.erase(unique(pos.begin(), pos.end()), pos.end());
		int pn = pos.size();
		for(j = 0; j < pn; j++) {
			if(pos[j] == h[n - 1])
				memo[n - 1][j] = 0;
			else
				memo[n - 1][j] = 1e18;
			l[j] = lower_bound(pos.begin(), pos.end(), pos[j] - d) - pos.begin();
			r[j] = (upper_bound(pos.begin(), pos.end(), pos[j] + d) - pos.begin()) - 1;
			e[j] = 31 - __builtin_clz(r[j] - l[j] + 1);
		}
		for(i = n - 2; i >= 0; i--) {
			priority_queue<ll, vector<ll>, greater<ll>> s;
			priority_queue<ll, vector<ll>, greater<ll>> rm;
			int L = pn, R = pn - 1;
			//for(j = pn - 1; j >= 0; j--) {
			//	lc[j][0] = memo[i + 1][j];
			//	for(k = 1; j + (1 << k) - 1 < pn; k++)
			//		lc[j][k] = min(lc[j][k - 1], lc[j + (1 << (k - 1))][k - 1]);
			//}
			for(j = pn - 1; j >= 0; j--) {
				while(L > l[j]) s.push(memo[i + 1][--L]);
				while(R > r[j]) rm.push(memo[i + 1][R--]);
				while(!rm.empty() && s.top() == rm.top()) s.pop(), rm.pop();
				//memo[i][j] = min(lc[l[j]][e[j]], lc[r[j] - (1 << e[j]) + 1][e[j]]) + abs(h[i] - pos[j]);
				//debug("(%d, %lld) = %lld + %lld\n", i, pos[j], *s.begin(), abs(h[i] - pos[j]));
				memo[i][j] = s.top() + abs(h[i] - pos[j]);
			}
		}
		ll ans = memo[0][lower_bound(pos.begin(), pos.end(), h[0]) - pos.begin()];
		if(ans > 1e14) puts("impossible");
		else printf("%lld\n", ans);
	}
}
