#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000003;
inline ll mod(ll x) { return x % modn; }

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

inline ll inv(ll x) { return fexp(x, modn - 2); }

const int N = 112345;

map<int, int> s[N];

vector<int> adj[N];
ll mult[N], k;
int x[N];
pii ans;

void dfs(int u, int p) {
	s[u][x[u]] = u;
	mult[u] = 1;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		bool ch = false;
		if(s[v].size() > s[u].size()) s[v].swap(s[u]), swap(mult[u], mult[v]), ch = true;
		//printf("%d <<<----- %d \n", u, v);
		for(auto e : s[v]) {
			ll x = mod(mod(inv(mod(e.fst * mult[v])) * inv(mult[u])) * k);
			//printf("%d <<<----- %d expects %lld to complete %lld\n", u, v, x, mod(e.fst * mult[v]));
			if(s[u].count(x)) {
				int a = s[u][x], b = e.snd;
				if(a > b) swap(a, b);
				ans = min(ans, pii(a, b));
			}
		}
		if(ch) mult[u] = mod(mult[u] * x[u]);
		else mult[v] = mod(mult[v] * x[u]);
		for(auto e : s[v]) {
			ll x = mod(mod(e.fst * mult[v]) * inv(mult[u]));
			if(s[u].count(x)) s[u][x] = min(s[u][x], e.snd);
			else s[u][x] = e.snd;
		}
	}
	//printf("AT %d:\n", u);
	//for(auto e : s[u]) {
	//	printf("val %d: min node %d\n", (int) mod(e.fst * mult[u]), -e.snd);
	//}
	//puts("=======");
}

int main() {
	int i, n, a, b;
	while(scanf("%d %lld", &n, &k) != EOF) {
		//puts("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n\n");
		for(i = 0; i < n; i++) scanf("%d", &x[i]);
		for(i = 0; i < n; i++) adj[i].clear(), s[i].clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		ans = pii(INT_MAX, INT_MAX);
		dfs(0, 0);
		if(ans.fst == INT_MAX) puts("No solution");
		else printf("%d %d\n", ans.fst + 1, ans.snd + 1);
	}
}
