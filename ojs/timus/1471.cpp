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
vector<pii> adj[50009];
int l[50009][20], nv[50009], w[50009];
void dfs(int u, int p, int n, int ws) {
	l[u][0] = p; nv[u] = n; w[u] = ws;
	for(int k = 1; k < 20; k++)
		l[u][k] = l[l[u][k-1]][k-1];
	for(pii e : adj[u])
		if(p != e.fst)
			dfs(e.fst, u, n + 1, ws + e.snd);
}

int lca(int u, int v) {
	if(nv[u] > nv[v]) swap(u, v);
	if(nv[u] < nv[v])
		for(int k = 19; k >= 0; k--)
			if(nv[l[v][k]] >= nv[u])
				v = l[v][k];
	if(v == u) return u;
	for(int k = 19; k >= 0; k--)
		if(l[u][k] != l[v][k])
			u = l[u][k], v = l[v][k];
	return l[u][0];
}

int main() {
	int i, n, q, a, b, c;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	dfs(0, 0, 0, 0);
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		int c = lca(a, b);
		printf("%d\n", w[a] + w[b] - 2*w[c]);
	}
}
