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
const int N = 100009;
vector<int> adj[N];
int d[N], low[N], seen[N], deg[N], comp[N], st[N], tempo, sn;

void dfs(int u) {
	seen[u] = true;
	d[u] = low[u] = tempo++;
	st[sn++] = u;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else low[u] = min(low[u], d[v]);
	if(low[u] >= d[u]) {
		int a = -1;
		while(a != u) {
			a = st[--sn];
			comp[a] = u;
			d[a] = INT_MAX;
		}
	}
}

int main() {
	int i, n, m, a, b;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) adj[i].clear(), seen[i] = false, deg[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
		}
		for(i = 0; i < n; i++)
			if(!seen[i])
				dfs(i);
		for(i = 0; i < n; i++)
			for(int v : adj[i])
				if(comp[i] != comp[v])
					deg[comp[v]]++;
		int tot = 0;
		for(i = 0; i < n; i++)
			if(deg[comp[i]] == 0) {
				deg[comp[i]] = 1;
				tot++;
			}
		printf("%d\n", tot);
	}
}
