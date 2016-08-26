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
const int N = 212345;
vector<int> adj[N];
ll le[N], so[N], s[N], h[N], p2[N];

int dp[N], dq[N];
void dfs0(int u, int p, int d, int D[]) {
	D[u] = d;
	for(int v : adj[u])
		if(v != p)
			dfs0(v, u, d + 1, D);
}

int dfs(int u, int p) {
	if(u) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	for(int v : adj[u]) {
		le[u] += dfs(v, u);
		so[u] += so[v] + le[v];
		h[u] = max(h[u], h[v] + 1);
	}
	if(le[u] == 0) le[u] = 1;
	return le[u];
}

//void dfs2(int u, int p) {
//	if(!u) s[u] = so[u];
//	else s[u] = so[u] + s[p] - (so[u] + le[u]) + (le[0] - le[u] + ll(adj[0].size() == 1));
//	printf("s[%d] = %lld\n", u+1, s[u]);
//	for(int v : adj[u])
//		dfs2(v, u);
//}

ll calc(int u) {
	//ll x = ll(le[0] - ll(adj[u].empty()) + ll(u && adj[0].size() == 1)) * ll(max(dp[u], dq[u]));
	//printf("calc[%d] = %lld - %lld\n", u+1, x, s[u]);
	ll h = max(dp[u], dq[u]);
	return h;
}

int main() {
	int i, n, a, b;
	p2[0] = 1;
	for(i = 1; i < N; i++)
		p2[i] = mod(p2[i - 1] * 2ll);
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) adj[i].clear(), le[i] = so[i] = 0;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--, b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		for(i = 0; i < n && adj[i].size() <= 3; i++);
		if(i < n) { puts("-1"); continue; }
		dfs0(0, 0, 0, dp);
		int p = max_element(dp, dp + n) - dp;
		dfs0(p, p, 0, dp);
		int q = max_element(dp, dp + n) - dp;
		dfs0(q, q, 0, dq);
		//dfs(0, 0);
		//dfs2(0, 0);
		ll best = LLONG_MAX; int bu;
		for(i = 0; i < n; i++)
			if(adj[i].size() <= 2 && calc(i) < best) {
				best = calc(i);
				bu = i;
			}
		printf("%d %d\n", bu + 1, (int) mod(p2[best + 1] - 1 - n + modn));
	}
}
