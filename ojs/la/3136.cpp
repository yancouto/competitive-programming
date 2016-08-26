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

const int N = 50009;

int seen[N], d[N], low[N], is_c[N], t, tempo;
vector<int> adj[N];
bool has_cut;
void dfs(int u, int p) {
	if(seen[u] == t) return;
	seen[u] = t;
	d[u] = low[u] = tempo++;
	int n_sons = 0;
	for(int v : adj[u]) {
		if(v == p) continue;
		if(seen[v] != t) {
			n_sons++;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= d[u] && (u != 0 || n_sons > 1))
				is_c[u] = t;
		} else low[u] = min(low[u], d[v]);
	}
	has_cut |= (is_c[u] == t);
}

int seen2[N], t2;
int cuts;
int dfs(int u) {
	if(seen2[u] == t2) return 0;
	seen2[u] = t2;
	int r = 1;
	for(int v : adj[u])
		if(is_c[v] != t)
			r += dfs(v);
		else if(seen2[v] != t2)
			seen2[v] = t2, cuts++;
	return r;
}

int main() {
	int i, n, a, b;
	while(scanf("%d", &n) != EOF && n) {
		t++;
		map<int, int> mp;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			if(!mp.count(a)) { mp[a] = mp.size() - 1; adj[mp[a]].clear(); }
			if(!mp.count(b)) { mp[b] = mp.size() - 1; adj[mp[b]].clear(); }
			a = mp[a]; b = mp[b];
			adj[a].pb(b); adj[b].pb(a);
		}
		has_cut = tempo = 0;
		dfs(0, -1);
		printf("Case %d:", t);
		if(!has_cut) { printf(" 2 %llu\n", (ull(mp.size()) * ull(mp.size() - 1)) / 2ull); continue; }
		int b = t2, res = 0;
		ull tot = 1;
		for(i = 0; i < mp.size(); i++)
			if(is_c[i] != t && seen2[i] <= b) {
				cuts = 0; t2++;
				int g = dfs(i);
				if(cuts == 1) tot *= ull(g), res++;
			}
		printf(" %d %llu\n", res, tot);
	}
}
