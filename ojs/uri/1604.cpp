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
vector<int> adj[100009];
vector<pii> ps;
bool ok;
bool dfs(int u, int p) {
	bool paired = false;
	for(int v : adj[u]) {
		if(v == p) continue;
		bool used = dfs(v, u);
		if(!used) {
			if(paired) ok = false;
			ps.pb(minmax(u, v));
			paired = true;
		}
	}
	return paired;
}

int main() {
	int i, a, b, n;
	while(scanf("%d", &n) != EOF) {
		ps.clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			adj[a].pb(b);
			adj[b].pb(a);
		}
		ok = true;
		dfs(1, 1);
		if(!ok) puts("N");
		else {
			puts("Y");
			sort(ps.begin(), ps.end());
			for(pii p : ps)
				printf("%d %d\n", p.fst, p.snd);
		}
		for(i = 1; i <= n; i++)
			adj[i].clear();
	}
}
