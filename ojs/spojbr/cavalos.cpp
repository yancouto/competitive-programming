// TLE com dfs
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

const int N = 500, M = 11234;
int to[M], c[M], f[M], seen[N], tempo, en;
vector<int> adj[N];

int dfs(int s, int t, int mn) {
	if(s == t) return mn;
	seen[s] = tempo;
	for(int e : adj[s])
		if(seen[to[e]] < tempo && f[e] < c[e])
			if(int a = dfs(to[e], t, min(mn, c[e] - f[e]))) {
				f[e] += a;
				f[e ^ 1] -= a;
				return a;
			}
	return 0;
}

int max_flow(int s, int t) {
	int fl = 0; tempo++;
	while(int a = dfs(s, t, INT_MAX))
		fl += a, tempo++;
	return fl;
}

void add_edge(int a, int b, int cp, int rc) {
	to[en] = b; c[en] = cp; f[en] = 0; adj[a].pb(en++);
	to[en] = a; c[en] = rc; f[en] = 0; adj[b].pb(en++);
}


int main() {
	int t = 0, i, n, m, a, b, k;
	while(scanf("%d %d %d", &n, &m, &k) != EOF) {
		en = 0;
		for(i = 0; i < n + m + 2; i++) adj[i].clear();
		for(i = 0; i < n; i++) {
			scanf("%d", &a);
			add_edge(n + m, i, a, 0);
		}
		for(i = 0; i < m; i++) add_edge(i + n, n + m + 1, 1, 0);
		for(i = 0; i < k; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			add_edge(a, b + n, 1, 0);
		}
		printf("Instancia %d\n%d\n\n", ++t, max_flow(n + m, n + m + 1));
	}
}
