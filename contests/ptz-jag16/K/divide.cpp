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

const int N = 1e3+4;
const int K = 53;
const ll INF = 1e14;

int n, m, k, s;
ll memo[2][N][N];
ll v[N];

void solve (int a, int b, int l, int r) {
	if (a > b) return;
	int j = (a+b)/2;

	ll & me = memo[k&1][s][j];
	int x = min(j-1, l);
	me = INF;

	for (int i = s; i < j; i++) {
	//for (int i = x; i <= r && i < j; i++) {
		ll loc = memo[!(k&1)][s][i] + memo[!(k&1)][i+1][j] + v[j] - v[i];

		if (loc <= me) {
			me = loc;
			x = i;
		}
	}

	solve(a, j-1, l, x);
	solve(j+1, b, x, r);
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%lld", v+i);

	sort(v, v+n);

	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			memo[0][i][j] = INF;

	for (int i = 0; i < n; i++)
		memo[0][i][i] = 0;
	
	for (k = 1 ; k <= m; k++) {
		for (s = n-1; s >= 0; s--) {
			memo[k&1][s][s] = 0;
			solve(s+1, n-1, s, n-1);
		}
	}

	printf("%lld\n", memo[(m&1)][0][n-1]);
}
