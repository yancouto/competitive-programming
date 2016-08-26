#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

struct ed {
	int a, b, c;
	bool operator < (ed o) const { return c < o.c; }
} es[30], e2[30];
int n, m;

vector<int> adj[100];
int seen[16], d[16], low[16], tempo;
bool dfs(int u, int p, int bm) {
	if(seen[u]) return true;
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	for(int e : adj[u]) {
		if(!(bm & (1 << e))) continue;
		int v = es[e].a == u? es[e].b : es[e].a;
		if(v == p) continue;
		if(!dfs(v, u, bm))
			return false;
		if(low[v] > d[u]) return false;
		low[u] = min(low[u], low[v]);
	}
	return true;
}

int main() {
	int i, j, t = 0;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &es[i].a, &es[i].b, &es[i].c);
			es[i].a--; es[i].b--;
			adj[es[i].a].pb(i);
			adj[es[i].b].pb(i);
		}
		int mn = INT_MAX;
		for(i = 0; i < (1 << m); i++) {
			memset(seen, 0, sizeof seen);
			tempo = 0;
			if(!dfs(0, -1, i)) continue;
			for(j = 0; j < n; j++)
				if(!seen[j])
					break;
			if(j < n) continue;
			int ct = 0;
			for(j = 0; j < m; j++)
				if(i & (1 << j))
					ct += es[j].c;
			mn = min(mn, ct);
		}
		if(mn == INT_MAX) printf("There is no reliable net possible for test case %d.\n", ++t);
		else printf("The minimal cost for test case %d is %d.\n", ++t, mn);
	}
}
