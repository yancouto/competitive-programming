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
const int N = 2009;
int low[N], d[N], seen[N], tempo;
vector<int> adj[N];

bool dfs(int u, int p) {
	seen[u] = true;
	d[u] = low[u] = tempo++;
	for(int v : adj[u])
		if(!seen[v]) {
			if(dfs(v, u)) return true;
			low[u] = min(low[u], low[v]);
			if(low[v] > d[u]) return true;
		} else if(v != p) low[u] = min(low[u], d[v]);
	return false;
}

int main() {
	int i, n, m, a, b;
	while(scanf("%d %d", &n, &m) && n) {
		for(i = 0; i < n; i++) seen[i] = 0, adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b); adj[b].pb(a);
		}
		if(dfs(0, 0)) puts("N");
		else puts("S");
	}
}
