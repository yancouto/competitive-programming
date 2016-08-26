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

int seen[200], x[200];
vector<int> adj[200];
bool dfs(int u, int c) {
	if(seen[u]) return c == x[u];
	seen[u] = true;
	x[u] = c;
	for(int v : adj[u])
		if(!dfs(v, !c))
			return false;
	return true;
}

int main() {
	int i, n, a;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		while(true) {
			scanf("%d", &a);
			if(!a) break;
			adj[i].pb(a - 1);
			adj[a - 1].pb(i);
		}
	}
	if(!dfs(0, 0)) { puts("-1"); return 0; }
	for(i = 0; i < n; i++)
		putchar(x[i] + '0');
	putchar('\n');
}
