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
const int MAX = 10009;
vector<int> adj[MAX];
int nv[MAX], d[MAX], low[MAX], tempo;
int brid[MAX], pai[MAX];
void dfs(int u, int p, int nv) {
	if(d[u]) return;
	pai[u] = p;
	::nv[u] = nv;
	d[u] = low[u] = tempo++;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u, nv + 1);
		low[u] = min(low[u], low[v]);
		if(low[v] > d[u])
			brid[v] = 1;
	}
}

char* ok(int u, int v) {
	if(nv[u] > nv[v]) swap(u, v);
	while(nv[v] > nv[u])
		if(!brid[v])
			return "N";
		else
			v = pai[v];
	if(u == v) return "Y";
	while(u != v)
		if(!brid[u] || !brid[v])
			return "N";
		else
			u = pai[u], v = pai[v];
	return "Y";
}

int S[MAX], sz[MAX];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int main() {
	int i, n, m, q, a, b;
	while(scanf("%d %d %d", &n, &m, &q) != EOF && n) {
		for(i = 0; i < n; i++)
			adj[i].clear(), S[i] = i, sz[i] = 1;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
			join(a, b);
		}
		memset(d, 0, sizeof d);
		memset(brid, 0, sizeof brid);
		tempo = 1;
		for(i = 0; i < n; i++)
			dfs(i, -1, 0);
		for(i = 0; i < q; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			if(find(a) != find(b)) { puts("N"); continue; }
			puts(ok(a, b));
		}
		puts("-");
	}
}
