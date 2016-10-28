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

const int N = 112345, L = 20;
int d[L][N], sz[N], mrk[N], p[N], de[N], fe[N], inv[N], tempo;
vector<pii> adj[N];
pii tr[L][4 * N]; int n;
multiset<int> best;
int cur[N], c[N];
multiset<int> mp[N];
multiset<int> bests[N];

int dfs(int u, int p, int hc, int h, int pp) {
	d[hc][u] = h;
	mp[pp].insert(h);
	sz[u] = 1;
	for(pii e : adj[u])
		if(e.fst != p && !mrk[e.fst])
			sz[u] += dfs(e.fst, u, hc, h + e.snd, pp);
	return sz[u];
}

inline void calc(int u) {
	if(cur[u] != -1) best.erase(best.find(cur[u]));
	if(bests[u].size() < 2) cur[u] = -1;
	else {
		cur[u] = *bests[u].rbegin() + *next(bests[u].rbegin());
		best.insert(cur[u]);
	}
}

void go(int u, int p, int h, int ih) {
	dfs(u, u, h - 1, ih, u);
	int S = sz[u], lst = u, ou = u;
	while(true) {
		int w = -1;
		for(pii e : adj[u])
			if(!mrk[e.fst] && e.fst != lst && sz[e.fst] * 2 >= S)
				w = e.fst;
		if(w != -1) lst = u, u = w;
		else break;
	}
	mp[ou].swap(mp[u]);
	if(p != -1) bests[p].insert(*mp[u].rbegin());
	d[h][u] = 0;
	bests[u].insert(0);
	bests[u].insert(0);
	c[u] = 1;
	mrk[u] = h;
	::p[u] = p;
	de[u] = tempo;
	inv[tempo++] = u;
	for(pii e : adj[u])
		if(!mrk[e.fst])
			go(e.fst, u, h + 1, e.snd);
	fe[u] = tempo - 1;
	cur[u] = -1;
	calc(u);
}

inline void paint(int u) {
	c[u] = 1;
	bests[u].insert(0);
	bests[u].insert(0);
	calc(u);
	int lst = u;
	for(int v = p[u]; v != -1; lst = v, v = p[v]) {
		if(!mp[lst].empty()) bests[v].erase(bests[v].find(*mp[lst].rbegin()));
		mp[lst].insert(d[mrk[v]][u]);
		bests[v].insert(*mp[lst].rbegin());
		calc(v);
	}
}

inline void unpaint(int u) {
	c[u] = 0;
	bests[u].erase(bests[u].find(0));
	bests[u].erase(bests[u].find(0));
	calc(u);
	int lst = u;
	for(int v = p[u]; v != -1; lst = v, v = p[v]) {
		bests[v].erase(bests[v].find(*mp[lst].rbegin()));
		mp[lst].erase(mp[lst].find(d[mrk[v]][u]));
		if(!mp[lst].empty()) bests[v].insert(*mp[lst].rbegin());
		calc(v);
	}
}

#define gc getchar_unlocked
#define pc putchar_unlocked

inline int get() {
	char c;
	while(isspace(c = gc()));
	int x = c - '0';
	bool neg = false;
	if(c == '-') x = 0, neg = true;
	while(isdigit(c = gc()))
		x = (x << 3) + (x << 1) + c - '0';
	return neg? -x : x;
}

inline void prn(int x) {
	if(!x) { pc('0'); pc('\n'); return; }
	int y = 0, ct = 0;
	while(x) y = (y << 3) + (y << 1) + (x % 10), x /= 10, ct++;
	while(ct--) pc((y % 10) + '0'), y /= 10;
	pc('\n');
}

const char * nop = "They have disappeared.\n";

int main() {
	int i, a, b, c; char op;
	n = get();
	for(i = 0; i < n - 1; i++) {
		a = get() - 1; b = get() - 1; c = get();
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	go(0, -1, 1, 0);
	for_tests(qn, qq) {
		while(isspace(op = gc()));
		if(op == 'A') {
			if(best.empty()) for(int j = 0; nop[j]; j++) pc(nop[j]);
			else prn(*best.rbegin());
		} else {
			a = get() - 1;
			if(::c[a]) unpaint(a);
			else paint(a);
		}
	}
}
