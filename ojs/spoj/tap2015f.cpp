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
const int N = 112345, E = 60;

vector<int> adj[N];
int d[E][E], c[N];
int memo[N][E], e;
int seen[N][E], t;
int solve(int u, int C, int p) {
	int &r = memo[u][C];
	if(seen[u][C] == t) return r;
	seen[u][C] = t;
	r = 1e8;
	for(int i = 0; i < e; i++) {
		if(c[u] != -1) i = c[u];
		int g = d[C][i];
		for(int v : adj[u])
			if(v != p)
				g += solve(v, i, u);
		r = min(r, g);
		if(c[u] != -1) break;
	}
	return r;
}

int main() {
	int i, j, n, a, b;
	while(scanf("%d %d", &n, &e) != EOF) {
		for(i = 0; i < e; i++)
			for(j = 0; j < e; j++)
				scanf("%d", &d[i][j]);
		for(i = 0; i < e; i++) d[e][i] = d[i][e] = 0;
		for(i = 0; i < n; i++) adj[i].clear(), c[i] = -1;
		for(i = 0; i < e; i++) {
			scanf("%d", &a);
			while(a--) {
				scanf("%d", &b);
				c[--b] = i;
			}
		}
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		t++;
		printf("%d\n", solve(0, e, 0));
	}
}
