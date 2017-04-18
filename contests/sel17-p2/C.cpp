#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

const int N = 11234;
int T;

int dp[N], p[N], vx[N], mrk[N], d[N];
vector<int> adj[N], adj2[N];
int lf[N], acc[N];

int go(int, int);

int memo[10109][10109];
char seen[10109][10109];

int choose(int u, int m, int k) {
	int v = adj2[u][m];
	int &r = memo[v][k];
	if(seen[v][k] == T) return r;
	seen[v][k] = T;
	r = 0;
	//if(m == adj2[u].size() - 1) printf("(%d, %d [%d], %d) = %d\n", u+1, m, v+1, k, go(v, k));
	if(m == adj2[u].size() - 1) return r = go(v, k);
	for(int i = max(0, k - acc[adj2[u][m + 1]]); i <= lf[v] && i <= k; i++)
		r = max<int>(r, go(v, i) + choose(u, m + 1, k - i));
	//printf("choose(%d, %d [%d], %d) = %d\n", u+1, m, v+1, k, (int) r);
	return r;
}

int go(int i, int k) {
	//printf("go(%d, %d)\n", i+1, k);
	assert(k <= lf[i]);
	if(k == 0) return 0;
	if(adj2[i].empty()) return 1;
	return 1 + choose(i, 0, k);
}

void dfs(int u, int p) {
	lf[u] = 0;
	for(int v : adj[u])
		if(v != p && mrk[v]) {
			adj2[u].pb(v);
			dfs(v, u);
			lf[u] += lf[v];
		}
	if(lf[u] == 0) lf[u] = 1;
	acc[u] = lf[u];
	for(int i = adj2[u].size() - 2; i >= 0; i--)
		acc[adj2[u][i]] += acc[adj2[u][i + 1]];
}

void prn(int u) {
	for(int v : adj2[u]) {
		printf("%d->%d\n", u+1, v+1);
		prn(v);
	}
}

int main() {
	scanf("%d", &T); T++;
	int n, m, k, a, b, i;
	while(--T >= 1) {
		scanf("%d %d %d", &n, &m, &k);
		for(i = 0; i <= n; i++) adj[i].clear(), d[i] = 0, mrk[i] = 0, adj2[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b); d[a]++;
			adj[b].pb(a); d[b]++;
		}
		vector<int> d1;
		for(i = 0; i < n; i++)
			if(d[i] == 1)
				d1.pb(i);
		int tot = 0;
		while(!d1.empty()) {
			tot++;
			int x = d1.back(); d1.pop_back();
			mrk[x] = 1;
			for(int y : adj[x])
				if(--d[y] == 1)
					d1.pb(y);
		}
		vector<int> roots;
		int nv = n;
		for(i = 0; i < n; i++)
			if(mrk[i])
				for(int j : adj[i])
					if(!mrk[j])
						adj[nv].pb(i);
		tot++;
		dfs(nv, -1);
		k = min(k, lf[nv]);
		//prn(nv); printf("choose %d leaves = %d\n", k, go(nv, k));
		printf("%d\n", tot - go(nv, k));
	}
}
