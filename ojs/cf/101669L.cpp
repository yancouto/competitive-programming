

#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 112345;
vector<int> adj[N], adj2[N];

struct dat {
	set<int> vx;
	set<int> adj;
	void absorb(dat &o) {
		if(o.vx.size() > vx.size()) {
			vx.swap(o.vx);
			adj.swap(o.adj);
		}
		for(int x : o.vx) adj.erase(x);
		for(int x : o.adj) if(!vx.count(x)) adj.insert(x);
		for(int x : o.vx) vx.insert(x);
	}
} s[N];

map<int, int> mp;

void dfs(int u, int p) {
	s[u].vx.insert(u);
	for(int v : adj2[u]) s[u].adj.insert(v);
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		s[u].absorb(s[v]);
	}
	if(u) assert(!s[u].adj.empty());
	if(u) mp[s[u].adj.size()]++;
}

int main() {
	int i, j;
	scanf("%d", &n);
	int a, b;
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj2[a].pb(b);
		adj2[b].pb(a);
	}
	dfs(0, 0);
	pii ans = *mp.begin();
	mp.clear();
	for(i = 0; i < n; i++) s[i].vx.clear(), s[i].adj.clear(), adj[i].swap(adj2[i]);
	dfs(0, 0);
	pii ans2 = *mp.begin();
	if(ans.first == ans2.first && ans.first == 2) ans.snd += ans2.snd;
	else ans = min<pii>(ans, ans2);
	printf("%d %d\n", ans.first + 1, ans.second);
}
