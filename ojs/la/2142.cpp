#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

vector<pii> adj[64];

void dfs(int u, int p) {
	if(p != -1) {
		int i;
		for(i = 0; adj[u][i].fst != p; i++);
		swap(adj[u][i], adj[u].back());
		adj[u].pop_back();
	}
	for(pii p : adj[u])
		dfs(p.fst, u);
}
int dis(int, int, int, int);

int memo[62][2][62];
int solve(int u, bool usd, int k) {
	if(k < 0) return -100000000;
	int &r = memo[u][usd][k];
	if(r != -1) return r;
	if(adj[u].empty()) return r = 0;
	if(usd) r = max(dis(u, adj[u].size(), 1, k), dis(u, adj[u].size(), 0, k));
	else r = max(dis(u, adj[u].size(), 0, k), max(dis(u, adj[u].size(), 1, k - 1), dis(u, adj[u].size(), 2, k - 1)));
	return r;
}

int m2[62][3][62];
int dis(int u, int m, int ch, int k) {
	if(m == 1) {
		if(ch > 1) return -100000000;
		return solve(adj[u].front().fst, ch, k) + ch * adj[u].front().snd;
	}
	int &r = m2[adj[u][m-1].fst][ch][k];
	if(r != -1) return r;
	for(int j = 0; j <= k; j++)
		for(int i = 0; i <= 1 && i <= ch; i++)
			r = max(r, dis(u, m - 1, ch - i, k - j) + solve(adj[u][m-1].fst, i, j) + i * adj[u][m-1].snd);
	return r;
}

int main() {
	int n, k, i, a, b, d;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a, &b, &d);
			adj[--a].pb(pii(--b, d));
			adj[b].pb(pii(a, d));
		}
		dfs(0, -1);
		memset(memo, -1, sizeof memo);
		memset(m2, -1, sizeof m2);
		printf("%d\n", solve(0, false, k));
	}
}
