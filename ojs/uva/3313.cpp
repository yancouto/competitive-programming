#include <bits/stdc++.h>
using namespace std;
#define dmg first
#define len second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;

struct edge { int v, d, l; };
vector<edge> adj[N];

struct cmp {
	bool operator()(pii a, pii b) const {
		if(a.dmg != b.dmg) return a.dmg < b.dmg;
		return a.len > b.len;
	}
};


ll best, m;
struct info {
	ll d, l;
	set<pii, cmp> p;
	void join(info &o);
	void add(pii a);
	void bs(pii a);
	void reset() { d = l = 0; p.clear(); p.insert(pii(0ll, 0ll)); }
} st[N];

void info::bs(pii a) {
	ll M = m - a.dmg - d;
	auto it = p.upper_bound(pii(M, LLONG_MIN));	
	if(it != p.begin() && a.dmg + prev(it)->dmg + d <= m)
		best = max(best, a.len + (prev(it)->len + l));
}

void info::add(pii a) {
	a.dmg -= d;
	a.len -= l;
	if(p.count(a)) return;
	auto it = p.insert(a).first;
	if(it != p.begin() && prev(it)->len >= a.len) { p.erase(it); return; }
	while(next(it) != p.end() && a.len >= next(it)->len)
		p.erase(next(it));
}

void info::join(info &o) {
	if(p.size() < o.p.size()) {
		p.swap(o.p);
		swap(d, o.d);
		swap(l, o.l);
	}
	for(pii a : o.p) {
		a.dmg += o.d; a.len += o.l;
		bs(a);
	}
	for(pii a : o.p) {
		a.dmg += o.d; a.len += o.l;
		add(a);
	}
}


void dfs(int u, int p) {
	st[u].reset();
	for(edge e : adj[u]) {
		if(e.v == p) continue;
		dfs(e.v, u);
		st[e.v].d += e.d;
		st[e.v].l += e.l;
		st[u].join(st[e.v]);
	}
}

int main() {
	int i, n, a, b, d, l;
	for_tests(t, tt) {
		scanf("%d %lld", &n, &m);
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d %d", &a, &b, &d, &l); a--; b--;
			adj[a].pb(edge{b, d, l});
			adj[b].pb(edge{a, d, l});
		}
		best = 0;
		dfs(0, -1);
		printf("Case %d: %lld\n", tt, best);
		for(i = 0; i < n; i++) adj[i].clear();
	}

}
