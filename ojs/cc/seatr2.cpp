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

vector<int> adj[502];
ll memo[504][20006];
int m;
//ll solve(int u, int n, int p) {
//	ll &r = memo[u][n];
//	if(r != -1) return r;
//	r = 1;
//	for(int v : adj[u])
//		if(v != p) {
//			ll t = 0;
//			for(int g = n; g <= m; g += n)
//				t += solve(v, g, u);
//			r = mod(r * mod(t));
//		}
//	return r;
//}

int es[503], to[1010], nx[1010], en;
void dfs(int u, int p) {
	for(int i = 1; i <= m; i++)
		memo[u][i] = 1;
	for(int e = es[u]; e != -1; e = nx[e]) {
		if(to[e] == p) continue;
		dfs(to[e], u);
		for(int i = 1; i <= m; i++) {
			ll tot = 0;
			for(int j = i; j <= m; j += i)
				tot += memo[to[e]][j];
			memo[u][i] = mod(memo[u][i] * mod(tot));
		}
	}
}

int main() {
	int i, n, a, b;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) es[i] = -1;
		en = 0;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			to[en] = b; nx[en] = es[a]; es[a] = en++;
			to[en] = a; nx[en] = es[b]; es[b] = en++;
		}
		dfs(0, -1);
		ll tot = 0;
		for(i = 1; i <= m; i++)
			tot += memo[0][i];
		printf("%d\n", (int) mod(tot));
	}
}
