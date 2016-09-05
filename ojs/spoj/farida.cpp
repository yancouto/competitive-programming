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

int a[11234];
ll dp[11234];
int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		dp[n] = dp[n + 1] = 0;
		for(i = n - 1; i >= 0; i--)
			dp[i] = max(dp[i + 1], dp[i + 2] + a[i]);
		printf("Case %d: %lld\n", tt, dp[0]);
	}
}
