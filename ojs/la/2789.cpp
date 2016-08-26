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
const int N = 112;

int ne[N], le[N], n[N], l[N];
vector<int> adj[N];

int dfs(int u, int p) {
	n[u] = ne[u]; l[u] = le[u];
	vector<int> pos;
	for(int v : adj[u])
		if(v != p) {
			dfs(v, u);
			pos.pb(v);
		}
	sort(pos.begin(), pos.end(), [](int i, int j) { return l[i] > l[j]; });
	for(int x : pos) {
		n[u] += max(0, n[x] - l[u]);
		l[u] -= min(n[x], l[u]);
		l[u] += l[x];
	}
	return n[u];
}

int main() {
	int i, n, a, m, g, b, t = 0;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++) {
			adj[i].clear();
			scanf("%d %d %d", &a, &m, &g);
			m += g;
			ne[i] = max(a, m);
			le[i] = ne[i] - m;
		}
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		int mn = INT_MAX;
		for(i = 0; i < n; i++)
			mn = min(mn, dfs(i, -1));
		printf("Case %d: %d\n", ++t, mn);
	}
}
