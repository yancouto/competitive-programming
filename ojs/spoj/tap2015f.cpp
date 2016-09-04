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
const int N = 51234, C = 60;
int d[C][C];
vector<int> adj[N];
int c[N];

int memo[N][C][2], e;
int seen[N][C][2], t;

int solve(int u, int C, bool par, int p) {
	int &r = memo[u][C][par];
	if(seen[u][C][par] == t) return r;
	seen[u][C][par] = t;
	if(!par) {
		if(c[u] != -1) return r = d[C][c[u]] + solve(u, c[u], true, p);
		r = INT_MAX;
		for(int i = 0; i < e; i++)
			r = min(r, d[i][C] + solve(u, i, true, p));
		return r;
	}
	r = 0;
	for(int v : adj[u])
		if(v != p)
			r += solve(v, C, false, u);
	return r;
}

int main() {
	int i, j, n, k, a, b;
	while(scanf("%d %d", &n, &e) != EOF) {
		for(i = 0; i < e; i++)
			for(j = 0; j < e; j++)
				scanf("%d", &d[i][j]);
		for(i = 0; i < e; i++)
			d[e][i] = d[i][e] = 0;
		for(i = 0; i < n; i++) c[i] = -1, adj[i].clear();
		for(i = 0; i < e; i++) {
			scanf("%d", &k);
			while(k--) {
				scanf("%d", &a); a--;
				c[a] = i;
			}
		}
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		t++;
		printf("%d\n", solve(0, e, false, 0));
	}
}
