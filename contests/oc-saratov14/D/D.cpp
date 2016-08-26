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
const int N = 412345;

struct ed {
	int a, b, w;
	bool operator < (ed o) const {
		if(w != o.w) return w < o.w;
		return pii(a, b) < pii(o.a, o.b);
	}
};

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
}

ll ans;
vector<ed> mst(int n, vector<ed> es) {
	ans = 0;
	sort(es.begin(), es.end());
	for(int i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	vector<ed> g;
	for(ed e : es) {
		assert(e.a >= 0 && e.a < n && e.b >= 0 && e.b < n);
		if(find(e.a) == find(e.b)) continue;
		join(e.a, e.b);
		ans += e.w;
		g.pb(e);
	}
	if(sz[find(0)] != n) { ans = -1; return vector<ed>(); }
	return g;
}

int h[N], lc[N][20], d[N], f[N], tempo;
vector<int> adj[N];
void dfs0(int u, int p, int x) {
	h[u] = x;
	if(u != p) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, p));
	d[u] = tempo++;
	lc[u][0] = p;
	for(int i = 1; i < 20; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	for(int v : adj[u])
		dfs0(v, u, x + 1);
	f[u] = tempo++;
}

int lca(int a, int b) {
	if(h[a] > h[b]) swap(a, b);
	for(int i = 19; i >= 0; i--)
		if(h[lc[b][i]] >= h[a])
			b = lc[b][i];
	if(a == b) return a;
	for(int i = 19; i >= 0; i--)
		if(lc[a][i] != lc[b][i])
			a = lc[a][i], b = lc[b][i];
	return lc[a][0];
}

vector<ed> eh[N], og[N];
set<ed> sets[N];
int r;
int a[N];

set<ed> &dfs(int u) {
	set<ed> &mine = sets[u];
	bool bad = false;
	vector<ed> ot;
	vector<int> pre;
	int son = 0;
	for(int v : adj[u]) {
		//printf("%d->%d\n", u, v);
		pre.pb(d[v]);
		set<ed> &s = dfs(v);
		while(!s.empty() && (s.begin()->a == u || s.begin()->b == u))
			s.erase(s.begin());
		if(!s.empty()) {
			ed f = *s.begin();
			if(h[f.a] > h[f.b]) swap(f.a, f.b);
			assert(f.a != u);
			assert(d[u] > d[f.a] && ::f[u] < ::f[f.a]);
			f.a = adj[u].size();
			f.b = son;
			ot.pb(f);
		}
		if(s.size() > mine.size()) s.swap(mine);
		for(ed x : s) mine.insert(x);
		son++;
	}
	for(ed e : og[u]) {
		ed f = e;
		if(u == f.b) swap(f.a, f.b);
		if(h[f.b] >= h[u]) mine.erase(e);
	}
	if(lc[u][0] != u && !adj[u].empty() && !bad) { 
		for(ed e : eh[u]) {
			e.a = (upper_bound(pre.begin(), pre.end(), d[e.a]) - pre.begin()) - 1;
			e.b = (upper_bound(pre.begin(), pre.end(), d[e.b]) - pre.begin()) - 1;
			assert(e.a != e.b);
			ot.pb(e);
		}
		vector<ed> ms = mst(adj[u].size() + 1, ot);
		if(ans < 0) a[u] = -1;
		else {
			int mn = INT_MAX;
			for(ed e : og[u])
				mn = min(mn, e.w);
			a[u] = mn;
			for(ed e : ms) a[u] = max(a[u], e.w);
		}
	} else if(lc[u][0] == u || adj[u].empty()) a[u] = 0;
	else a[u] = -1;
	for(ed e : og[u]) {
		if(e.b == u) swap(e.a, e.b);
		if(d[u] > d[e.b] && f[u] < f[e.b]) mine.insert(e);
	}
	return mine;
}

ll ct[N];
vector<ed> a2[N];

int main() {
	int tt = 0, i, n, m, a, b, w;
	while(scanf("%d %d", &n, &m) != EOF) {
		printf("Case %d:", ++tt);
		for(i = 0; i < n; i++) adj[i].clear(), S[i] = i, sz[i] = 1, og[i].clear(), eh[i].clear(), ct[i] = 0, a2[i].clear();
		vector<ed> es;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &w); a--; b--;
			es.pb(ed{a, b, w});
			og[a].pb(es.back()); og[b].pb(es.back());
		}
		vector<ed> tr = mst(n, es);
		int tot = INT_MIN;
		for(ed e : tr) tot = max(tot, e.w);
		//printf("original mst %lld\n", tot);
		if(tot < 0) {
			for(i = 0; i < n; i++) printf(" -1");
			putchar('\n');
			continue;
		}
		set<ed> all(tr.begin(), tr.end());
		for(ed e : tr) adj[e.a].pb(e.b), adj[e.b].pb(e.a), a2[e.a].pb(e), a2[e.b].pb(e);
		for(i = 0; adj[i].size() > 1; i++);
		//printf("root %d\n", i);
		dfs0(i, i, 0);
		for(ed e : es) {
			int c = lca(e.a, e.b);
			if(c == e.a || c == e.b) continue;
			eh[c].pb(e);
		}
		dfs(i);
		// arrumar os as
		for(i = 0; i < n; i++)
			if(::a[i] == 0) ::a[i] = tot;
			else if(::a[i] != -1) {
				for(ed e : a2[i]) all.erase(e);
				if(!all.empty()) ::a[i] = max(::a[i], all.rbegin()->w);
				for(ed e : a2[i]) all.insert(e);
			}
		for(i = 0; i < n; i++) printf(" %d", ::a[i]); putchar('\n');
	}
}
