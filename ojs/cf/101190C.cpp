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

const int N = 112345;
int st[N], sn;

int cn;
vector<int> C[N];
vector<int> adj[N];
set<int> bad[N];
vector<int> cs[N];

void dfs(int u, int p) {
	st[sn++] = u;
	seen[u] = true;
	for(int v : adj[u]) {
		if(v == p || bad[u].count(v)) continue;
		if(!seen[v]) { dfs(v, u); ++it; }
		else {
			C[cn].pb(v); cs[v].pb(cn);
			bad[v].insert(u);
			bad[u].insert(v);
			for(int i = sn - 1; st[i] != v; i--) {
				C[cn].pb(st[i]);
				cs[st[i]].pb(cn);
				bad[st[i]].insert(st[i - 1]);
				bad[st[i - 1]].insert(st[i]);
			}
			cn++;
		}
	}
	sn--;
}

int main() {
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d", &k);
		scanf("%d", &a);
		while(--k) {
			scanf("%d", &b);
			adj[a].pb(b); adj[b].pb(a);
			a = b;
		}
	}
	for(i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i, -1);
}
