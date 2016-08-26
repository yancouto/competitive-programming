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
const int N = 112345;

int n[2][N];
vector<int> adj[N];
char cc[N]; int c[N];

ll dfs(int u, int p, int co) {
	ll tot = 0;
	n[0][u] = n[1][u] = 0;
	for(int v : adj[u])
		if(v != p) {
			tot += dfs(v, u, !co);
			n[0][u] += n[0][v];
			n[1][u] += n[1][v];
		}
	if(co != c[u]) n[co][u]++;
	int mn = min(n[0][u], n[1][u]);
	n[0][u] -= mn;
	n[1][u] -= mn;
	tot += n[0][u] + n[1][u];
	if(u == 0 && (n[0][u] || n[1][u])) return LLONG_MAX;
	return tot;
}

int main() {
	int i, n, a, b;
	scanf("%d", &n);
	scanf("%s", cc);
	for(i = 0; i < n; i++)
		c[i] = (cc[i] == 'R');
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	ll mn = min(dfs(0, 0, 0), dfs(0, 0, 1));
	if(mn == LLONG_MAX) puts("-1");
	else printf("%lld\n", mn);
}
