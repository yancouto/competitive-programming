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
const int N = 150009;
const int K = 312;

int ord[N], nx[N], w[N], o;
vector<int> adj[N];
int memo[N][K];

int dfs(int u) {
	ord[o++] = u;
	for(int v : adj[u])
		dfs(v);
	nx[u] = o;
}

int main() {
	int i, n, k, j, x, r;
	while(scanf("%d %d", &n, &k) != EOF) {
		o = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &w[i]);
			if(x) adj[x - 1].pb(i);
			else r = x;
		}
		dfs(r);
		for(i = 0; i < n; i++) adj[i].clear();
		for(j = 1; j <= k; j++) memo[n][j] = INT_MIN;
		memo[n][0] = 0;
		for(i = n - 1; i >= 0; i--) {
			for(j = 1; j <= k; j++)
				memo[i][j] = max(memo[i + 1][j], memo[nx[ord[i]]][j - 1] + w[ord[i]]);
			memo[i][0] = 0;
		}
		if(memo[0][k] > 0) printf("%d\n", memo[0][k]);
		else puts("impossible");
	}
}
