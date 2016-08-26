#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define pb push_back
typedef pair<int, int> pii;
const int MAX = 1000009;
vector<pii> adj[MAX];
void dfs(int u, int p) {
	if(p != -1) {
		int i;
		for(i = 0; adj[u][i].fst != p; i++);
		swap(adj[u][i], adj[u].back());
		adj[u].pop_back();
	}
	for(pii e : adj[u])
		dfs(e.fst, u);
}

int memo[MAX][2];
int solve(int u, int m, bool can) {
	if(m == 0) return 0;
	int v = adj[u][m-1].fst;
	int &r = memo[v][can];
	if(r != -1) return r;
	r = solve(u, m - 1, can) + solve(v, adj[v].size(), true);
	if(can) r = max(r, solve(u, m - 1, false) + solve(v, adj[v].size(), false) + 1);
	return r;
}

int a[MAX], b[MAX];
void build(int u, int m, bool can) {
	if(m == 0) return;
	int v = adj[u][m-1].fst;
	if(solve(u, m, can) == solve(u, m - 1, can) + solve(v, adj[v].size(), true)) {
		build(u, m - 1, can);
		build(v, adj[v].size(), true);
	}
	else {
		printf("%d %d\n", a[adj[u][m-1].snd], b[adj[u][m-1].snd]);
		build(u, m - 1, false);
		build(v, adj[v].size(), false);
	}
}

int main() {
	int n, i;
	scanf("%d %*d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a[i], &b[i]);
		adj[a[i]].pb(pii(b[i], i));
		adj[b[i]].pb(pii(a[i], i));
	}
	memset(memo, -1, sizeof memo);
	dfs(1, -1);
	printf("%d\n", solve(1, adj[1].size(), true));
	build(1, adj[1].size(), true);
	return 0;
}
