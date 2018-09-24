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

const int N = 1123456;
ll acc[N], dp[N];

int main() {
	int n, s;
	scanf("%d %d", &n, &s);
	dp[1] = 1;
	acc[1] = 1;
	for(int i = 2; i <= n; i++) {
		dp[i] = mod(acc[i - 1] - (i - s - 1 >= 0? acc[i - s - 1] : 0) + modn);
		acc[i] = mod(acc[i - 1] + dp[i]);
	}
	ll ans = 0;
	for(ll i = 0; i < s; i++)
		ans = mod(ans + (i + 1) * dp[n - i]);
	printf("%lld\n", ans);
}
