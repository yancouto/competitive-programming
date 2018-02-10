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

int a[212345];

int main() {
	int i, n, k;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		ll smx = LLONG_MIN;
		ll cur = 0;
		for(i = 0; i < n; i++) {
			cur += a[i];
			smx = max(smx, cur);
			if(cur < 0) cur = 0;
		}
		if(k == 1) {
			printf("%lld\n", smx);
			continue;
		}
		const ll sum = accumulate(a, a + n, 0ll);
		ll ans = max(sum * ll(k), smx);
		ll bl = LLONG_MIN;
		cur = 0;
		for(i = 0; i < n - 1; i++) {
			cur += a[i];
			bl = max(bl, cur);
			ans = max(ans, max(0ll, sum) * ll(k - 1) + cur);
		}
		ll br = LLONG_MIN;
		cur = 0;
		for(i = n - 1; i > 0; i--) {
			cur += a[i];
			br = max(br, cur);
			ans = max(ans, max(0ll, sum) * ll(k - 1) + cur);
		}
		ans = max(ans, max(0ll, sum) * ll(k - 2) + bl + br);
		printf("%lld\n", ans);
	}
}
