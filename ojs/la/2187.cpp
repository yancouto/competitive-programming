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
const int MAX = 100009;
vector<int> adj[MAX];
int seen[MAX], d[MAX], low[MAX], tempo;
int lucky[MAX], co[MAX], cn, st[MAX], sn, color[MAX];
bool dfs2(int u, int c) {
	if(seen[u] == 2) return color[u] != c;
	color[u] = c;
	seen[u] = 2;
	for(int v : adj[u])
		if(co[v] == co[u] && dfs2(v, !c))
			return true;
	return false;
}

void dfs(int u, int p) {
	if(seen[u]) return;
	seen[u] = 1;
	st[sn++] = u;
	d[u] = low[u] = tempo++;
	int mnlow = d[u];
	for(int v : adj[u]) {
		if(v == p) continue;
		int k = sn;
		dfs(v, u);
		mnlow = min(mnlow, low[v]);
		if(low[v] < d[u]) continue;
		st[sn++] = u; cn++; int sz = 0;
		while(sn != k) {
			int a = st[--sn];
			seen[a] = 1;
			co[a] = cn;
			sz++;
		}
		bool good = dfs2(u, 0);
		for(int i = 0; i < sz; i++)
			lucky[st[k + i]] |= good;
	}
	low[u] = min(low[u], mnlow);
}

int main() {
	int i, n, m, a, b;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		memset(seen, 0, sizeof seen);
		memset(co, 0, sizeof seen);
		memset(lucky, 0, sizeof lucky);
		sn = cn = tempo = 0;
		for(i = 0; i < n; i++)
			dfs(i, -1);
		printf("%d\n", accumulate(lucky, lucky + n, 0));
	}
}
