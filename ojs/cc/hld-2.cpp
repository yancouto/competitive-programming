#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

const int N = 112345;
vector<int> adj[N];
int ch[N], sz[N];
multiset<int> H[N];

int dfs(int u, int p, int h) {
	sz[u] = 1;
	if(p != -1) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	if(adj[u].empty()) { return h; }
	ch[u] = -1;
	int cur;
	for(int v : adj[u]) {
		int hh = dfs(v, u, h + 1);
		sz[u] += sz[v];
		if(ch[u] == -1 || hh > cur || (hh == cur && sz[v] > sz[ch[u]])) ch[u] = v, cur = hh;
	}
	return cur;
}

int lg[N];
inline ll val(int x) { return x? lg[x] + 1 : 0; }

ll solve(int u, int up) {
	//if(adj[u].empty()) printf("memo(%d, %d) : %lld\n", u+1, up, val(up));
	if(adj[u].empty()) return val(up);
	ll ans = 0;
	for(int v : adj[u]) {
		if(v == ch[u]) ans = max(ans, solve(v, up + 1));
		else ans = max(ans, 1 + val(up) + solve(v, 0));
	}
	return ans;
}

int main() {
	int i, n, a, b;
	lg[1] = 0;
	for(i = 2; i < N; i++)
		lg[i] = lg[(i + 1) / 2] + 1;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		dfs(0, -1, 0);
		printf("%lld\n", solve(0, 0));
		for(i = 0; i < n; i++) adj[i].clear();
	}
}
