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

const int N = 512345;
int a[N];

set<int> out;
int oc[N];
ll dp[N];

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 1; i <= n; i++) scanf("%d", &a[i]);
	if(k == 0) {
		for(i = 1; i <= n && a[i] != 0; i++);
		if(i <= n) puts("0");
		else {
			ll ans = 1;
			for(i = 0; i < n - 1; i++) ans = mod(ans * 2ll);
			printf("%lld\n", ans);
		}
		return 0;
	}
	if(k > n) {
		ll ans = 1;
		for(i = 0; i < n - 1; i++) ans = mod(ans * 2ll);
		printf("%lld\n", ans);
		return 0;
	}
	for(i = 1; i <= n; i++) a[i] = min(a[i], n + 10);
	for(i = 0; i <= n + 20; i++) out.insert(i);
	dp[n + 1] = 1;
	int r = n;
	for(i = n; i >= 1; i--) {
		if(oc[a[i]]++ == 0) out.erase(a[i]);
		while(*out.begin() > k)
			if(--oc[a[r--]] == 0)
				out.insert(a[r + 1]);
		dp[i] = mod(dp[i + 1] - dp[r + 2] + modn);
		dp[i] = mod(dp[i] + dp[i + 1]);
	}
	printf("%lld\n", mod(dp[1] - dp[2] + modn));
}
