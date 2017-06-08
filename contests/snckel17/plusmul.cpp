
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

ll a[1123456], dp[1123456];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++) scanf("%lld", &a[i]);
		//mul[0] = 1;
		//for(i = 1; i <= n; i++) mul[i] = mod(a[i] * mul[i - 1]);
		//inv[n] = fexp(mul[n], modn - 2);
		//for(i = n - 1; i >= 0; i--)
		//	inv[i] = mod(inv[i + 1] * a[i + 1]);
		dp[1] = a[1];
		ll cur = a[1];
		ll sum = dp[1];
		ll p = 1;
		for(i = 2; i <= n; i++) {
			cur = mod(mod(cur + p) * a[i]);
			dp[i] = mod(cur + sum);
			sum = mod(sum + dp[i]);
			p = mod(p * 2ll);
		}
		printf("%lld\n", dp[n]);
	}

}

