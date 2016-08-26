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
const int N = 500009;
vector<int> adj[N];
int l[N], d[N];

int dfs(int u, int p) {
	if(p != -1)
		adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	for(int v : adj[u])
		l[u] += dfs(v, u);
	if(!l[u]) l[u] = 1, d[u] = 0;
	else { 
		d[u] = INT_MAX;
		for(int v : adj[u])
			d[u] = min(d[u], d[v] + 1);
	}
	return l[u];
}

ll memo[N];
ll solve(int u) {
	ll &r = memo[u];
	if(r != -1) return r;
	if(adj[u].empty()) return r = 1;
	ll wait = 0, dd = LLONG_MAX;
	for(int v : adj[u]) {
		dd = min(dd, (ll)d[v]);
		wait = max(wait, solve(v) - l[v] - (l[u] - l[v]));
	}
	wait = max(wait, dd);
	return r = wait + l[u] + 1;
}

int main() {
	int i, n, a, b;
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	if(n == 2) { puts("1"); return 0; }
	dfs(0, -1);
	ll ans = 0;
	for(int v : adj[0])
		ans = max(ans, solve(v));
	printf("%I64d\n", ans);
}
