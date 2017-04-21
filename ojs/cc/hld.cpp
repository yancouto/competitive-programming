#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

const int N = 1123;
vector<int> adj[N];

void dfs(int u, int p) {
	if(p != -1) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	for(int v : adj[u])
		dfs(v, u);
}

int lg[N];
inline ll val(int x) { return x? lg[x] + 1 : 0; }

ll memo[N][N];
ll solve(int u, int up) {
	//if(adj[u].empty()) printf("memo(%d, %d) : %lld\n", u+1, up, val(up));
	if(adj[u].empty()) return val(up);
	ll &r = memo[u][up];
	if(r != -1) return r;
	r = LLONG_MAX;
	vector<ll> mxl(adj[u].size()), mxr(adj[u].size());
	for(int i = 0; i < adj[u].size(); i++)
		mxl[i] = i? max(mxl[i - 1], val(up) + 1 + solve(adj[u][i], 0)) : val(up) + 1 + solve(adj[u][i], 0);
	for(int i = adj[u].size() - 1; i >= 0; i--)
		mxr[i] = (i != adj[u].size() - 1? max(mxr[i + 1], val(up) + 1 + solve(adj[u][i], 0)) : val(up) + 1 + solve(adj[u][i], 0));
	for(int i = 0; i < adj[u].size(); i++) {
		ll mx = -1;
		if(i) mx = max(mx, mxl[i - 1]);
		if(i != adj[u].size() - 1) mx = max(mx, mxr[i + 1]);
		r = min(r, max(mx, solve(adj[u][i], up + 1)));
	}
	//printf("solve(%d, %d) = %lld\n", u+1, up, r);
	return r;
}

int main() {
	int i, n, a, b;
	lg[1] = 0;
	for(i = 2; i < N; i++)
		lg[i] = lg[(i + 1) / 2] + 1;
	for_tests(t, tt) {
		memset(memo, -1, sizeof memo);
		scanf("%d", &n);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		dfs(0, -1);
		printf("%lld\n", solve(0, 0));
		for(i = 0; i < n; i++) adj[i].clear();
	}
}
