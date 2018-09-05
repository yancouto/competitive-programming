#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 1123456;
int n, m;
int acc[N];
ll dp[N];
ll eq[2*N];

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d", &j); acc[j - 1]++;
	}
	for(i = 1; i <= n; i++)
		acc[i] += acc[i - 1];
	dp[n] = dp[n + 1] = 1;
	for(i = n - 1; i >= 0; i--) {
		if(acc[i + 1] - acc[i] == 0) {
			eq[acc[i] - i + N] = mod(eq[acc[i] - i + N] + dp[i + 2]);
			debug("eq[%d] += %lld --> = %lld\n", acc[i] - i, dp[i + 2], eq[acc[i] - i + N]);
		}
		debug("using %d\n", (i? acc[i - 1] : 0) - i + 1);
		dp[i] = ((acc[i] - (i? acc[i - 1] : 0))? 0 : dp[i + 1]) + eq[(i? acc[i - 1] : 0) - i + 1 + N];
		dp[i] = mod(dp[i]);
		debug("dp[%d] = %lld\n", i, dp[i]);
	}
	printf("%lld\n", dp[0]);
}
