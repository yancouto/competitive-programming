#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[112345];
ll l[112345], r[112345];

int main() {
	int i, n, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		if(*max_element(a, a + n) <= 0) {
			printf("%d\n", *max_element(a, a + n));
			continue;
		}
		ll cur = 0;
		for(i = 0; i < n; i++) {
			cur = max(cur + a[i], 0ll);
			l[i] = cur;
		}
		cur = 0;
		for(i = n - 1; i >= 0; i--) {
			cur = max(cur + a[i], 0ll);
			r[i] = cur;
		}
		r[n] = 0;
		ll best = *max_element(l, l + n);
		for(i = 0; i < n; i++) {
			ll val = (i? l[i - 1] : 0ll) + r[i + 1];
			best = max(best, val);
		}
		printf("%lld\n", best);
	}
}
