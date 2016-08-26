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
int k;
vector<int> adj[150004];
int a[150004];
void dfs(int u, int *best) {
	int b2[k + 1], i;
	for(i = 0; i <= k; i++)
		b2[i] = best[i];
	for(int v : adj[u])
		dfs(v, b2);
	b2[0] = best[0] = 0;
	// b2 usa seus filhos, best eh independente de vc
	for(i = 1; i <= k; i++)
		b2[i] = max(b2[i], best[i - 1] + a[u]);
	for(i = 0; i <= k; i++)
		best[i] = b2[i];
}

int main() {
	int i, n, x;
	while(scanf("%d %d", &n, &k) != EOF) {
		int r;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &a[i]);
			if(x) adj[x - 1].pb(i);
			else r = i;
		}
		int best[k + 1];
		fill(best, best + k + 1, INT_MIN);
		dfs(r, best);
		if(best[k] < 0) puts("impossible");
		else printf("%d\n", best[k]);
		for(i = 0; i < n; i++)
			adj[i].clear();
	}
}
