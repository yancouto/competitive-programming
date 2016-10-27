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
const int N = 2123;
int seen[N], to[N], c[N], f[N], tempo;
vector<int> adj[N];


int dfs(int u, int mn) {
	if(u + 'A' == 'Z') return mn;
	seen[u] = tempo;
	for(int e : adj[u])
		if(seen[to[e]] < tempo && c[e] - f[e] > 0)
			if(int a = dfs(to[e], min(mn, c[e] - f[e]))) {
				f[e] += a;
				f[e ^ 1] -= a;
				return a;
			}
	return 0;
}

int main() {
	int n, c, fl = 0, en; char a, b;
	scanf("%d", &n);
	while(n--) {
		scanf(" %c %c %d", &a, &b, &c); a -= 'A'; b -= 'A';
		to[en] = b; ::c[en] = c; adj[a].pb(en++);
		to[en] = a; ::c[en] = 0; adj[b].pb(en++);
	}
	tempo++;
	while(int x = dfs(0, INT_MAX)) {
		fl += x;
		tempo++;
	}
	printf("%d\n", fl);
}
