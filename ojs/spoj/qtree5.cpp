#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
int nw;
int d[20][N];
int sz[N], mrk[N], p[N];
vector<int> adj[N];
multiset<int> best[N];
int c[N];

int dfs(int u, int p, int hc, int h) {
	d[hc][u] = h;
	sz[u] = 1;
	for(int v : adj[u])
		if(v != p && !mrk[v])
			sz[u] += dfs(v, u, hc, h + 1);
	return sz[u];
}

void go(int u, int p, int h) {
	dfs(u, u, h - 1, 1);
	int S = sz[u], lst = u;
	while(true) {
		int w = -1;
		for(int v : adj[u])
			if(v != lst && !mrk[v] && sz[v] * 2 >= S)
				w = v;
		if(w != -1) lst = u, u = w;
		else break;
	}
	mrk[u] = h;
	::p[u] = p;
	d[h][u] = 0;
	best[u].insert(1e8);
	for(int v : adj[u])
		if(!mrk[v])
			go(v, u, h + 1);
}

void paint(int u) {
	nw++; c[u] = 1;
	for(int v = u; v != -1; v = p[v])
		best[v].insert(d[mrk[v]][u]);
}

void unpaint(int u) {
	nw--; c[u] = 0;
	for(int v = u; v != -1; v = p[v])
		best[v].erase(best[v].find(d[mrk[v]][u]));
}

int query(int u) {
	if(nw == 0) return -1;
	int ans = INT_MAX;
	for(int v = u; v != -1; v = p[v])
		ans = min(ans, d[mrk[v]][u] + *best[v].begin());
	return ans;
}

int main() {
	int i, n, a, b, op;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	go(0, -1, 1);
	for_tests(qn, qq) {
		scanf("%d %d", &op, &a); a--;
		if(op == 0 && c[a] == 0) paint(a);
		else if(op == 0) unpaint(a);
		else printf("%d\n", query(a));
	}
}
