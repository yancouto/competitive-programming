#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 212345;
vector<int> adj[N];
int d[N], low[N], seen[N], t, dis[N];
void dfs(int u, int p) {
	seen[u] = true;
	low[u] = d[u] = t++;
	int sons = 0;
	for(int v : adj[u])
		if(v == p) continue;
		else if(seen[v]) low[u] = min(low[u], d[v]);
		else {
			sons++;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= d[u]) dis[u]++;
		}
	if(u) dis[u]++;
	else dis[u] = sons;
}
int n, m;

int check(int u) {
	int M = m - adj[u].size();
	return n - 1 - dis[u] == M;
}

int main() {
	int i, j, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	int odd = 0;
	for(i = 0; i < n; i++)
		odd += (adj[i].size() & 1);
	if(odd != 0 && odd != 2) { puts("0"); return 0; }
	vector<int> ans;
	if(odd == 2) {
		vector<int> o;
		for(i = 0; i < n; i++)
			if(adj[i].size() & 1)
				o.pb(i);
		adj[o[0]].pb(n); adj[n].pb(o[0]);
		adj[o[1]].pb(n); adj[n].pb(o[1]);
		dfs(0, -1);
		if(check(o[1])) ans.pb(o[0]);
		if(check(o[0])) ans.pb(o[1]);
	} else {
		dfs(0, -1);
		for(i = 0; i < n; i++)
			if(check(i))
				ans.pb(i);
	}
	printf("%d\n", (int) ans.size());
	for(int x : ans) printf("%d ", x + 1);
	if(!ans.empty()) printf("\n");

}
