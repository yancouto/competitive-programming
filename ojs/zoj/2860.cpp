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

const int N = 1009;

int p[N], opt[N][N]; ll dp[N][N];

void solve(int i, int j) {
	ll bm = LLONG_MAX; int bi;
	for(int k = max(opt[i][j - 1], i+1); k <= min(opt[i + 1][j], j-1); k++) {
		ll val = dp[i][k] + dp[k][j];
		if(val >= bm) continue;
		bm = val; bi = k;
	}
	dp[i][j] = bm + p[j] - p[i];
	opt[i][j] = bi;
}

int main() {
	int n, m, i, j;
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i = 1; i <= m; i++)
			scanf("%d", &p[i]);
		p[0] = 0; p[m + 1] = n;
		for(i = 0; i <= m + 1; i++)
			opt[i][i+1] = i;
		for(j = 3; j <= m + 2; j++)
			for(i = 0; i + j - 1 <= m + 1; i++)
				solve(i, i + j - 1);
		printf("%lld\n", dp[0][m+1]);
	}
}
