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

struct no {
	int u; ll d; int p;
	bool operator < (no o) const { return d > o.d; }
};

const int N = 212345;
vector<int> adj[N], rev[N];
vector<pii> adj_[N];
ll d[N];
int tempo = 1;
int low[N], sz[N];
map<pii, int> mrk;
int ans[N], seen[N];
int lc[N][20];
int h[N];
int val[N];

int lca(int u, int v) {
	if(h[u] > h[v]) swap(u, v);
	for(int i = 19; i >= 0; i--)
		if(h[lc[v][i]] >= h[u])
			v = lc[v][i];
	if(u == v) return u;
	for(int i = 19; i >= 0; i--)
		if(lc[u][i] != lc[v][i])
			u = lc[u][i], v = lc[v][i];
	return lc[u][0];
}

void go(int u, int p) {
	h[u] = h[p] + 1;
	lc[u][0] = p;
	for(int i = 1; i < 20; i++)
		lc[u][i] = lc[lc[u][i - 1]][i - 1];
	seen[u] = 2;
	for(int v : adj[u]) {
		if(seen[v] == 2) continue;
		go(v, u);
	}
}

map<int, int> mp[N];
void go2(int u) {
	seen[u] = 3;
	for(int v : adj[u]) {
		if(seen[v] == 3) continue;
		//printf("%d -> %d\n", u + 1, v + 1);
		go2(v);
		if(mp[v].size() > mp[u].size()) mp[u].swap(mp[v]);
		for(pii e : mp[v])
			mp[u][e.fst] += e.snd;
	}
	//puts("=====");
	//for(pii e : mp[u])
	//	printf("[%d] %d = %d\n", u + 1, e.fst, e.snd);
	int mn = u;
	for(int v : rev[u]) {
		if(v == lc[u][0]) continue;
		//printf("rev[%d] = %d\n", u + 1, v + 1);
		int g = lca(u, v);
		if(h[g] < h[mn])
			mn = g;
	}
	int tot = 0;
	while(!mp[u].empty()) {
		auto it = prev(mp[u].end());
		if(it->fst >= h[mn]) {
			tot += it->snd;
			mp[u].erase(it);
		} else {
			break;
		}
	}
	//puts("------");
	mp[u][h[mn]] = tot + 1;
	if(u) {
		::ans[mrk[pii(u, lc[u][0])]] = (mn == u? prev(mp[u].end())->snd : 0);
		//printf("(%d, %d) = %d\n\n", u + 1, lc[u][0] + 1, ::ans[mrk[pii(u, lc[u][0])]]);
	}
	//for(pii e : mp[u])
	//	printf("[%d] %d = %d\n", u + 1, e.fst, e.snd);
	//puts("ooooo");
}


int main() {
	int i, n, m, a, b, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj_[a].pb(pii(b, c));
		adj_[b].pb(pii(a, c));
		mrk[pii(a, b)] = mrk[pii(b, a)] = i;
	}
	priority_queue<no> pq;
	pq.push(no{0, 0, -1});
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.u]) {
			if(x.d == d[x.u] && x.p != -1) {
				adj[x.p].pb(x.u);
				rev[x.u].pb(x.p);
				//adj[x.u].pb(x.p);
			}
			continue;
		} else {
			if(x.p != -1) {
				adj[x.p].pb(x.u);
				rev[x.u].pb(x.p);
				//adj[x.u].pb(x.p);
			}
			seen[x.u] = 1, d[x.u] = x.d;
		}
		for(pii e : adj_[x.u])
			pq.push(no{e.fst, x.d + e.snd, x.u});
	}
	go(0, 0);
	go2(0);
	for(i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}
