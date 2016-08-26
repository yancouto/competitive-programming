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
const int N = 10009;

int tempo;
int d[N], low[N];
vector<int> adj[N], v;
bool seen[N];

void dfs(int u, int p) {
	seen[u] = true;
	d[u] = low[u] = tempo++;
	bool any = false; int nf = 0;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v, u); nf++;
			any |= (low[v] >= d[u]);
			low[u] = min(low[u], low[v]);
		} else if(v != p) low[u] = min(low[u], d[v]);
	if(u? any : nf > 1) v.pb(u);
}

int main() {
	int i, n, m, a, b, tt = 0;
	while(scanf("%d %d", &n, &m) && n) {
		v.clear();
		for(i = 0; i < n; i++) adj[i].clear(), seen[i] = false;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b); adj[b].pb(a);
		}
		dfs(0, 0);
		sort(v.begin(), v.end());
		printf("Teste %d\n", ++tt);
		if(v.empty()) printf("nenhum");
		else for(int x : v) printf("%d ", x + 1);
		printf("\n\n");
	}
}
