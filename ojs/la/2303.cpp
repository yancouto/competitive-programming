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
vector<pii> adj[200009];

int a[200009];
int dfs(int u, int p) {
	a[u] = 0;
	for(pii e : adj[u])
		if(e.fst != p)
			a[u] += max(0, dfs(e.fst, u) + e.snd);
	return a[u];
}

int main() {
	int t = 0, n, a, b, c, i;
	while(true) {
		t++;
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		for(i = 0; i < 200008; i++)
			::a[i] = 0;
		dfs(a, -1);
		int mx = 0;
		for(i = 0; i < 200008; i++)
			mx = max(mx, ::a[i]);
		printf("%d\n", mx);
		for(i = 0; i < 200002; i++)
			adj[i].clear();
	}
}
