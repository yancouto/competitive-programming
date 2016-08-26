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
int dp[N][N], acc[N][N], a[N], b[N];

void solve(int l, int r, int lo, int ro, int q) {
	if(r < l) return;
	int m = (l + r) / 2;
	int bm = INT_MAX, bi;
	for(int i = max(m, lo); i <= ro; i++) {
		int val = dp[i + 1][q - 1] + acc[m+1][i+1];
		if(val >= bm) continue;
		bm = val; bi = i;
	}
	dp[m][q] = bm;
	solve(l, m - 1, lo, bi, q);
	solve(m + 1, r, bi, ro, q);
}


int main() {
	int i, j, n, m;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i] + b[i - 1];
		}
		for(i = 1; i <= n; i++)
			for(j = i + 1; j <= n; j++)
				acc[i][j] = acc[i][j - 1] + a[j] * (b[j - 1] - b[i - 1]);
		for(i = 0; i < n; i++)
			dp[i][0] = 100000000;
		dp[n][0] = 0;
		for(i = 1; i <= m+1; i++)
			solve(0, n - 1, 0, n - 1, i);
		printf("%d\n", dp[0][m+1]);
	}
}
