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

const int N = 212, M = 21234;
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

int main() {
	int i, n, m, s, t, tt = 0;
	while(scanf("%d", &n) != EOF && n) {
		scanf("%d %d %d", &s, &t, &m);
		en = 0;
		for(i = 1; i <= n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &to[en + 1], &to[en], &c[en]);
			c[en + 1] = c[en];
			f[en] = f[en + 1] = 0;
			adj[to[en+1]].pb(en);
			adj[to[en]].pb(en + 1);
			en += 2;
		}
		printf("Network %d\nThe bandwidth is %d.\n\n", ++tt, max_flow(s, t));
	}
}
