#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

#define fst first
#define snd second

int best = 0; ll tot = 0;
int k;
const int N = 112345;

struct st_ {
	int osz, ow;
	map<int, int> qt, lg;
	void init() {
		qt[0] = 1; osz = ow = 0;
		lg[0] = 0;
	}
	void join(st_ &o) {
		//for(pii p : qt)
		//	printf("sz %d qt %d w %d\n", p.fst + osz, p.snd, lg[p.fst]);
		if(o.qt.size() > qt.size()) {
			swap(osz, o.osz); swap(ow, o.ow);
			qt.swap(o.qt); lg.swap(o.lg);
		}
		for(pii p : o.qt) {
			int sz = p.fst + o.osz; int ct = p.snd; int w = o.lg[p.fst] + o.ow;
			if(!qt.count(k - sz - osz)) continue;
			if(lg[k - sz - osz] + ow + w > best)
				best = lg[k - sz - osz] + ow + w, tot = 0;
			if(lg[k - sz - osz] + ow + w == best)
				tot += ll(qt[k - sz - osz]) * ll(ct);
		}
		for(pii p : o.qt) {
			int sz = p.fst + o.osz; int ct = p.snd; int w = o.lg[p.fst] + o.ow;
			if(!lg.count(sz - osz) || w - ow > lg[sz - osz]) {
				lg[sz - osz] = w - ow;
				qt[sz - osz] = 0;
			}
			if(w - ow == lg[sz - osz])
				qt[sz - osz] += ct;
		}
		//printf("\n=== after join\n");
		//for(pii p : qt)
		//	printf("sz %d qt %d w %d\n", p.fst + osz, p.snd, lg[p.fst]);
	}
} st[N];

vector<pii> adj[N], sons[N];


void dfs(int u) {
	st[u].init();
	for(pii e : sons[u]) {
		int v = e.fst; int c = e.snd;
		//printf("%d -> %d\n", u, v);
		dfs(v);
		st[v].osz++;
		st[v].ow += c;
		//printf("\n%d join\n", u);
		st[u].join(st[v]);
	}
}

int seen[N];

struct no {
	int u, d, p, c, t;
	bool operator < (const no &o) const {
		if(d != o.d) return d > o.d;
		if(u != o.u) return u > o.u;
		return t > o.t;
	}
};

int d[N];

void pre(int u) {
	seen[u] = 2;
	sort(adj[u].begin(), adj[u].end());
	for(pii e : adj[u])
		if(d[e.fst] - d[u] == e.snd && seen[e.fst] != 2) {
			//printf("(%d) => %d\n", u, e.fst);
			sons[u].pb(e);
			pre(e.fst);
		}
}

int main () {
	int i, n, a, b, c, m;
	scanf("%d %d %d", &n, &m, &k); k--;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb(pii(b, c)); adj[b].pb(pii(a, c));
	}
	priority_queue<no> pq;
	pq.push(no{1, 0, -1, 0, -1});
	int t = 0;
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.u]) continue;
		//printf("(%d) ->%d\n", x.p, x.u);
		d[x.u] = x.d;
		seen[x.u] = 1;
		for(pii e : adj[x.u])
			pq.push(no{e.fst, e.snd + x.d, x.u, e.snd, t++});
	}
	pre(1);
	dfs(1);
	printf("%d %lld\n", best, tot);
}
