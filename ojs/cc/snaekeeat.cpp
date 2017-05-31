#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

const int N = 112345;
int a[N];
ll acc[N];

inline bool ok(ll k, ll n, ll i) {
	//printf("%lld >= %lld * %lld - (%lld - %lld)\n", i, k, n - i, acc[n-1], i? acc[i - 1] : 0ll);
	return i >= k * (n - i) - (acc[n-1] - (i? acc[i - 1] : 0ll));
}

int main() {
	int i, n, q, k;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &q);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a + n);
		acc[0] = a[0];
		for(i = 1; i < n; i++) acc[i] = acc[i - 1] + a[i];
		//for(i = 0; i < n; i++) printf("a[%d] = %d || %lld\n", i, a[i], acc[i]);
		while(q--) {
			scanf("%d", &k);
			int on = lower_bound(a, a + n, k) - a;
			int ans = n - on;
			int l = 0, r = on;
			while(l < r) {
				int m = (l + r) / 2;
				//printf("ok(%d, %d, %d) = %d\n", k, on, m, ok(k, on, m));
				if(ok(k, on, m)) r = m;
				else l = m + 1;
			}
			ans += on - l;
			printf("%d\n", ans);
		}
	}
}
