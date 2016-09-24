// INCOMPLETE
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int dfs(int u, int p) {
	sz[u] = 1;
	for(int v : adj[u])
		if(v != p && !h[v])
			sz[u] += dfs(v, u);
	return sz[u];
}

void go(int u, int p) {
	dfs(u, u);
	int ls = -1;
	while(true) {
		int bs = -1;
		for(int v : adj[u])
			if(!h[v] && (sz[v] > sz[u] / 2))
				bs = v;
		if(bs != -1) ls = u, u = bs;
		else {
			h[u] = h[p] + 1;
			::p[u] = p;
			for(int v : adj[u])
				if(!h[v])
					go(v, u);
			if(ls != -1) go(ls, u);
			return;
		}
	}
}

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(i = 0; i < n; i++)
		dist[i] = 1e8;
	go(0, 0);
	paint(0);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &op, &u); u--;
		if(op == 1) paint(u);
		else printf("%d\n", query(u));
	}
}
