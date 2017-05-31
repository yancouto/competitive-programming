#include <vector>
#include <algorithm>
#include <cstdio>
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
const int N = 112345;

int S[N], sz[N], up[N], d[N], low[N], seen[N], nv[N], p[N], bs, tempo;
vector<int> adj[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	if(nv[up[b]] < nv[up[a]])
		up[a] = up[b];
}
int nxnv(int u) {
	return nv[up[find(p[u])]];
}

void dfs(int u, int p, int h) {
	::p[u] = p;
	nv[u] = h;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	for(int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if(!seen[v]) {
			dfs(v, u, h + 1);
			low[u] = min(low[u], low[v]);
			if(low[v] < d[v]) join(v, u);
			else bs++;
		} else if(v != p) low[u] = min(low[u], d[v]);
	}
}

int main() {
	int i, n, m, a, b, tt = 0;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < n; i++) adj[i].clear(), S[i] = i, sz[i] = 1, up[i] = i, seen[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b); adj[b].pb(a);
		}
		bs = 0;
		dfs(0, 0, 0);
		printf("Case %d:\n", ++tt);
		for_tests(t, tt) {
			scanf("%d %d", &a, &b);
			a = up[find(a - 1)]; b = up[find(b - 1)];
			while(a != b) {
				if(!a || !b) a = a + b, b = 0;
				else if(nxnv(a) > nxnv(b)) swap(a, b);
				bs--;
				join(a, p[a]);
				a = up[find(a)];
			}
			printf("%d\n", bs);
		}
		putchar('\n');
	}
}
