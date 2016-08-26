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
const int MAX = 100009;
vector<pii> adj[MAX]; int tot;
void dfs(int u, int pai, int bic) {
	for(pii p : adj[u])
		if(p.snd != pai)
			dfs(p.snd, u, p.fst);
	adj[u].pb(pii(0, -1));
	sort(adj[u].begin(), adj[u].end());
	int t = 0;
	for(int i = 0; i < adj[u].size() - 1; i++)
		t += adj[u][i].fst;
	int h = adj[u].back().fst;
	if(h <= t) h = ((h + t) & 1);
	else h -= t;
	tot += h;
}

int main() {
	int i, n, a, b, c;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			adj[i].clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[--a].pb(pii(c, --b));
			adj[b].pb(pii(c, a));
		}
		tot = 0; dfs(0, -1, 0);
		printf("Case #%d: %d\n", tt, tot/2);
	}
	return 0;
}
