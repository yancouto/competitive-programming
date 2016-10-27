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
const int N = 1123;
int to[N], c[N], f[N], tempo, seen[N];
vector<int> adj[N];

int dfs(int u, int mn) {
	if(u == 1) return mn;
	seen[u] = tempo;
	for(int e : adj[u])
		if(seen[to[e]] < tempo && c[e] - f[e] > 0)
			if(int a = dfs(to[e], min(mn, c[e] - f[e]))) {
				f[e] += a;
				f[e ^ 1] -= a;
				return a;
			}
	return 0;
}

int main() {
	int i, n, m, a, b, c, en;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		en = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			to[en] = b; ::c[en] = c; f[en] = 0; adj[a].pb(en++);
			to[en] = a; ::c[en] = c; f[en] = 0; adj[b].pb(en++);
		}
		tempo++;
		while(dfs(0, INT_MAX)) tempo++;
		for(i = 0; i < n; i++)
			if(seen[i] == tempo)
				for(int e : adj[i])
					if(seen[to[e]] < tempo)
						printf("%d %d\n", i + 1, to[e] + 1);
		putchar('\n');
		for(i = 0; i < n; i++) adj[i].clear();
	}
}
