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
const int MAXN = 3009, MAXM = 100009;

vector<pii> adj[MAXN];
int pai[MAXN], cst[MAXN], nv[MAXN];
void dfs(int u, int p, int nv) {
	::nv[u] = nv;
	pai[u] = p;
	for(pii e : adj[u]) {
		if(e.fst == p) continue;
		cst[e.fst] = e.snd;
		dfs(e.fst, u, nv + 1);
	}
}

int solve(int u, int v) {
	if(nv[u] > nv[v]) swap(u, v);
	int val = 0;
	while(nv[v] > nv[u]) {
		val = max(val, cst[v]);
		v = pai[v];
	}
	while(u != v) {
		val = max(val, max(cst[v], cst[u]));
		v = pai[v]; u = pai[u];
	}
	return val;
}


int S[MAXN], sz[MAXN];
int find(int i) {
	if(S[S[i]] != S[i]) return S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}
int a[MAXM], b[MAXM], w[MAXM], p[MAXM];
int main() {
	int n, m, q, u, v, i;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a[i], &b[i], &w[i]); a[i]--; b[i]--;
			p[i] = i;
		}
		for(i = 0; i < n; i++)
			S[i] = i, sz[i] = 1;
		sort(p, p + m, [](int i, int j) { return w[i] < w[j]; });
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < m; i++) {
			int aa = a[p[i]], bb = b[p[i]];
			if(find(aa) == find(bb)) continue;
			join(aa, bb);
			adj[aa].pb(pii(bb, w[p[i]]));
			adj[bb].pb(pii(aa, w[p[i]]));
		}
		dfs(0, 0, 0);
		scanf("%d", &q);
		printf("Case %d\n", tt);
		for(i = 0; i < q; i++) {
			scanf("%d %d", &u, &v); u--; v--;
			printf("%d\n", solve(u, v));
		}
		putchar('\n');
	}
}
