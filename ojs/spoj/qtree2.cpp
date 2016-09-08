#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 11234;

vector<pii> adj[N];
int h[N], lc[N][15], w[N];
void dfs(int u, int p, int nv, int acc) {
	h[u] = nv;
	w[u] = acc;
	lc[u][0] = p;
	for(int i = 1; i < 15; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	for(pii e : adj[u])
		if(e.fst != p)
			dfs(e.fst, u, nv + 1, acc + e.snd);
}

int la(int a, int k) {
	for(int i = 0; (1 << i) <= k; i++)
		if((1 << i) & k)
			a = lc[a][i];
	return a;
}

int lca(int a, int b) {
	if(h[a] > h[b]) swap(a, b);
	b = la(b, h[b] - h[a]);
	if(a == b) return a;
	for(int i = 14; i >= 0; i--)
		if(lc[a][i] != lc[b][i])
			a = lc[a][i], b = lc[b][i];
	return lc[a][0];
}

char s[110];
int main() {
	int a, b, c, k, i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		dfs(0, 0, 0, 0);
		while(true) {
			scanf("%s", s);
			if(s[1] == 'O') break;
			scanf("%d %d", &a, &b); a--; b--;
			c = lca(a, b);
			if(s[0] == 'D') {
				printf("%d\n", w[a] + w[b] - 2 * w[c]);
			} else {
				scanf("%d", &k);
				if(k <= h[a] - h[c] + 1) printf("%d\n", la(a, k - 1) + 1);
				else printf("%d\n", la(b, (h[b] - h[c]) - (k - (h[a] - h[c] + 1))) + 1);
			}
		}
		putchar('\n');
	}
}
