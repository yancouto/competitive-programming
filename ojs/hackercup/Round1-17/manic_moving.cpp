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

int n, m, K;
int s[5123], d[5123];
int adj[112][112];
ll memo[5123][112];
int seen[5123][112], t;
ll solve(int i, int v) {
	ll &r = memo[i][v];
	if(seen[i][v] == t) return r;
	seen[i][v] = t;
	if(i == K - 1) return r = adj[v][d[i]];
	r = solve(i + 1, s[i + 1]) + adj[v][d[i]] + adj[d[i]][s[i + 1]];
	r = min(r, solve(i + 1, d[i]) + adj[v][s[i + 1]] + adj[s[i + 1]][d[i]]);
	return r;
}

int main() {
	int i, j, k, a, b, c;
	for_tests(tn, tt) {
		scanf("%d %d %d", &n, &m, &K);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				adj[i][j] = 1e8;
		for(i = 0; i < n; i++) adj[i][i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			adj[a][b] = adj[b][a] = min(adj[a][b], c);
		}
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
		bool ok = true;
		for(i = 0; i < K; i++) {
			scanf("%d %d", &s[i], &d[i]); s[i]--; d[i]--;
			if(adj[s[i]][d[i]] > .9e8) ok = false;
			if(i && adj[d[i - 1]][s[i]] > .9e8) ok = false;
		}
		if(adj[0][s[0]] > .9e8) ok = false;
		printf("Case #%d: ", tt);
		if(!ok) { puts("-1"); continue; }
		t++;
		printf("%d\n", solve(0, s[0]) + adj[0][s[0]]);
	}
}
