#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 123456789;
inline ll mod(ll x) { return x % modn; }

ll dp[1123456], acc[1123456];

int main() {
	int i; ll n, s;
	scanf("%lld %lld", &n, &s);
	dp[0] = acc[0] = 1;
	if(s == n) {
		ll ans = 1;
		for(i = 0; i < n; i++)
			ans = mod(ans * 2);
		printf("%lld\n", mod(ans + modn - 1));
		return 0;
	}
	for(i = 1; i <= n; i++) {
		dp[i] = mod(acc[i - 1] - (i <= s? 0 : acc[i - s - 1]) + (i < s) + modn);
		acc[i] = mod(dp[i] + acc[i - 1]);
	}
	ll ans = dp[n];
	for(int k = 1; k < s; k++) {
		if(n - s - 2 >= 0)
			ans = mod(ans - (acc[n - s - 2] - (n - s - 2 - (k - 1) - 1 < 0? 0 : acc[n - s - 2 - (k - 1) - 1])) + 2 * modn);
		if(n - k - 1 < s)
			ans = mod(ans  - 1);
	}
	printf("%lld\n", ans);
}
