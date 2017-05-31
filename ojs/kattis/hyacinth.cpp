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

int cnt = 2;
int c1[11234], c2[11234];
vector<int> adj[11234];

void dfs(int u, int p, int a) {
	int b = cnt++;
	c1[u] = a; c2[u] = b;
	for(int v : adj[u])
		if(v != p)
			dfs(v, u, b);
}

int main() {
	int i, n, a, b;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(i = 0; i < n && adj[i].size() > 1; i++);
	if(n == 2) { puts("1 2\n1 2"); return 0; }
	dfs(i, -1, 1);
	for(i = 0; i < n; i++)
		printf("%d %d\n", c1[i], c2[i]);
}
