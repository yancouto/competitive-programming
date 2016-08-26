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
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n;
const int MAX = 100009;
vector<int> adj[MAX];
int h[MAX], d[MAX], f[MAX], tempo;
int pai[MAX][20];
void dfs(int u, int p, int nv) {
	pai[u][0] = p;
	h[u] = nv;
	d[u] = tempo++;
	for(int i = 1; i < 20; i++)
		pai[u][i] = pai[pai[u][i - 1]][i - 1];
	for(int v : adj[u])
		if(v != p)
			dfs(v, u, nv + 1);
	f[u] = tempo++;
}

int lca(int u, int v) {
	if(h[u] > h[v]) swap(u, v);
	if(h[u] < h[v])
		for(int i = 19; i >= 0; i--)
			if(h[pai[v][i]] >= h[u])
				v = pai[v][i];
	if(u == v) return u;
	for(int i = 19; i >= 0; i--)
		if(pai[u][i] != pai[v][i]) {
			u = pai[u][i];
			v = pai[v][i];
		}
	return pai[u][0];
}

bool is_anc(int u, int v) {
	return d[v] >= d[u] && f[v] <= f[u];
}

bool cmp_h(int u, int v) {
	return h[u] > h[v];
}
int ks[MAX];
int main() {
	int i, j, a, b, q, k;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			adj[--a].pb(--b);
			adj[b].pb(a);
		}
		tempo = 0;
		dfs(0, 0, 0);
		scanf("%d", &q);
		for(i = 0; i < q; i++) {
			scanf("%d", &k);
			for(j = 0; j < k; j++) {
				scanf("%d", &ks[j]);
				ks[j]--;
			}
			sort(ks, ks + k, cmp_h);
			for(j = 1; j < k && is_anc(ks[j], ks[0]); j++);
			int node2 = ks[(j < k)? j : 0];
			int lc = lca(ks[0], node2);
			for(j = 1; j < k; j++) {
				bool a1 = is_anc(ks[j], ks[0]);
				bool a2 = (node2 != ks[0]) && is_anc(ks[j], node2);
				if(a1 && a2 && ks[j] != lc) break;
				if(!a1 && !a2) break;
			}
			if(j == k) puts("Yes");
			else puts("No");
		}
		for(i = 0; i < n; i++)
			adj[i].clear();
	}
	return 0;
}
