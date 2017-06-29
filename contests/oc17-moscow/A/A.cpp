#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1123;
int mx[N], sz[N], n;
int bad[N];

struct cent {
	map<int, vector<int>> adj;
	int root;
};

int dfs(map<int, vector<int>> &adj, int u, int p) {
	sz[u] = 1;
	mx[u] = 0;
	for(int v : adj[u])
		if(v != p && !bad[v]) {
			sz[u] += dfs(adj, v, u);
			mx[u] = max(mx[u], sz[v]);
		}
	mx[u] = max<int>(mx[u], adj.size() - sz[u]);
	return sz[u];
}

map<int, vector<int>> aux;
void dfs2(map<int, vector<int>> &adj, int u, int p) {
	aux[u] = adj[u];
	for(int v : adj[u])
		if(v != p && !bad[v])
			dfs2(adj, v, u);
}


cent centroid(map<int, vector<int>> &adj) {
	dfs(adj, adj.begin()->first, -1);
	int i = adj.begin()->first;
	for(auto &pe : adj)
		if(mx[pe.first] < mx[i])
			i = pe.first;
	bad[i] = 1;
	cent c;
	c.root = i;
	for(int v : adj[i])
		if(!bad[v]) {
			aux.clear();
			dfs2(adj, v, -1);
			map<int, vector<int>> adj2 = aux;
			cent c2 = centroid(adj2);
			c.adj[i].pb(c2.root);
			//c.adj[c2.root].pb(i);
			for(auto pe : c2.adj) {
				c.adj.insert(pe);
			}
		}
	return c;
}

int main () {
	int i, t, n, a, b;
	scanf("%d %d", &t, &n);
	while(t--) {
		map<int, vector<int>> adj;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			adj[a].pb(b);
			adj[b].pb(a);
		}
		for(i = 1; i <= n; i++) bad[i] = 0;
		map<int, vector<int>> adj2 = centroid(adj).adj;
		map<int, vector<int>> adj3;
		for(auto pe : adj2) {
			for(int x : pe.second) {
				adj3[pe.first].pb(x);
				adj3[x].pb(pe.first);
			}
		}
		adj2 = centroid(adj3).adj;
		adj3.clear();
		for(auto pe : adj2) {
			for(int x : pe.second) {
				adj3[pe.first].pb(x);
				adj3[x].pb(pe.first);
			}
		}
		adj2 = centroid(adj3).adj;
		adj3.clear();
		for(auto pe : adj2) {
			for(int x : pe.second) {
				adj3[pe.first].pb(x);
				adj3[x].pb(pe.first);
			}
		}
		adj2 = centroid(adj3).adj;
		adj3.clear();
		for(auto pe : adj2) {
			for(int x : pe.second) {
				adj3[pe.first].pb(x);
				adj3[x].pb(pe.first);
			}
		}
		adj2 = centroid(adj3).adj;
		adj3.clear();
		for(auto pe : adj2) {
			for(int x : pe.second) {
				adj3[pe.first].pb(x);
				adj3[x].pb(pe.first);
			}
		}

		for(auto pe : adj)
			sort(pe.second.begin(), pe.second.end());
		for(auto pe : adj3)
			sort(pe.second.begin(), pe.second.end());
		if(adj == adj3) puts("Centroid");
		else puts("Random");
	}
}
