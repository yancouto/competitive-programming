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
const int MAX = 50009;
vector<int> adj[MAX], path[MAX], z[MAX];
bool seen[MAX];
int last[MAX], x[MAX], y[MAX];
int pai[MAX];
void dfs(int u, int p) {
	if(seen[u]) return;
	pai[u] = p;
	seen[u] = true;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v, u);
			x[u] ^= x[v];
		}
}

void dfs2(int u) {
	if(seen[u]) return;
	seen[u] = true;
	bool has = y[u];
	for(int v : adj[u])
		if(!seen[v]) {
			dfs2(v);
			if(path[v].empty()) continue;
			if(!has) { path[u] = move(path[v]); has = true; continue; }
			path[u].pb(u);
			path[u].insert(path[u].end(), path[v].rbegin(), path[v].rend());
			printf("%d", path[u].size() - 1);
			for(int w : path[u])
				printf(" %d", w + 1);
			putchar('\n');
			has = false;
			path[u].clear();
		}
	if(has) path[u].pb(u);
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
	int i, n, m, k, a, b;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++)
		S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
		join(a, b);
	}
	memset(last, -1, sizeof last);
	int tot = 0;
	for(i = 0; i < k; i++) {
		scanf("%d", &a); a--;
		int &b = last[find(a)];
		if(b == -1) b = a;
		else {
			x[a] = x[b] = 1;
			y[a] = y[b] = 1;
			b = -1;
			tot++;
		}
	}
	for(i = 0; i < n; i++)
		dfs(i, -1);
	printf("%d\n", tot);
	memset(seen, 0, sizeof seen);
	for(i = 0; i < n; i++)
		if(!seen[i])
			dfs2(i);
}
