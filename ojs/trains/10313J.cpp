#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define i first
#define j second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int n, m;
set<pii> oc;
inline bool valid(int i, int j, bool skip=false) { return i >= 0 && j >= 0 && i < n && j < m && (skip || !oc.count(pii(i, j))); }

int di[] = {1, -1, 0, 0, -1, 1};
int dj[] = {0, 0, -1, 1, 1, -1};

map<pii, int> mp;
set<pii> reach(pii x, int r, bool skip = false) {
	queue<pii> q;
	map<pii, int> d;
	q.push(x); d[x] = 0;
	while(!q.empty()) {
		x = q.front(); q.pop();
		mp[x] = 0;
		if(d[x] == r) continue;
		for(int dd = 0; dd < 6; dd++) {
			int ni = x.i + di[dd], nj = x.j + dj[dd];
			if(!valid(ni, nj, skip) || d.count(pii(ni, nj))) continue;
			d[pii(ni, nj)] = d[x] + 1;
			q.push(pii(ni, nj));
		}
	}
	set<pii> s;
	for(auto &e : d) s.insert(e.fst);
	return s;
}

namespace f {

const int N = 112345, M = 112345 * 2;
typedef int val;
typedef int num;
int es[N], to[M], nx[M], en, pai[N];
val fl[M], cp[M];
num cs[M], d[N];
const num inf = 1e8, eps = 0;
const val infv = INT_MAX;
int seen[N], tempo;
int qu[N];

num tot;
bool spfa(int s, int t) {
	tempo++;
	int a = 0, b = 0;
	for(int i = 0; i < N; i++) d[i] = inf;
	d[s] = 0;
	qu[b++] = s;
	seen[s] = tempo;
	while(a != b) {
		int u = qu[a++]; if(a == N) a = 0;
		seen[u] = 0;
		for(int e = es[u]; e != -1; e = nx[e])
			if(cp[e] - fl[e] > val(0) && d[u] + cs[e] < d[to[e]] - eps) {
				d[to[e]] = d[u] + cs[e]; pai[to[e]] = e ^ 1;
				if(seen[to[e]] < tempo) { seen[to[e]] = tempo; qu[b++] = to[e]; if(b == N) b = 0; }
			}
	}
	if(d[t] == inf) return false;
	val mx = infv;
	for(int u = t; u != s; u = to[pai[u]])
		mx = min(mx, cp[pai[u] ^ 1] - fl[pai[u] ^ 1]);
	tot += d[t] * val(mx);
	for(int u = t; u != s; u = to[pai[u]])
		fl[pai[u]] -= mx, fl[pai[u] ^ 1] += mx;
	return mx;
}

void init(int n) {
	en = 0;
	memset(es, -1, sizeof(int) * n);
}

val flow;
num mncost(int s, int t) {
	tot = 0; flow = 0;
	while(val a = spfa(s, t)) flow += a;
	return tot;
}

void add_edge(int u, int v, val c, num s) {
	fl[en] = 0; cp[en] = c; to[en] = v; nx[en] = es[u]; cs[en] =  s; es[u] = en++;
	fl[en] = 0; cp[en] = 0; to[en] = u; nx[en] = es[v]; cs[en] = -s; es[v] = en++;
}
}

const int N = 1123;

int tn, cn;
int cv[N], tp[N];
pii c[N], t[N];
set<pii> tr[N], cr[N];
map<int, pii> inv;
bool solve(int bm, bool build = false) {
	f::init(cn + 2 * mp.size() + tn + 2);
	int TO = cn + 2 * mp.size();
	int S = TO + tn;
	int T = S + 1, i;
	for(i = 0; i < cn; i++) {
		f::add_edge(S, i, 1, 0);
		for(pii p : cr[i])
			f::add_edge(i, mp[p], 1, 0);
	}
	for(auto &e : mp)
		f::add_edge(e.snd, e.snd + 1, 1, 0),
		f::add_edge(e.snd + 1, T, 1, 0);
	int lf = 0;
	for(i = 0; i < tn; i++) {
		if(!((bm >> i) & 1)) continue;
		lf += tp[i];
		for(pii p : tr[i])
			f::add_edge(mp[p] + 1, TO + i, 1, 0);
		f::add_edge(TO + i, T, tp[i], -1);
	}
	if(f::mncost(S, T) != -lf) return false;
	assert(f::flow == cn);
	if(!build) return true;
	using f::to; using f::es; using f::nx; using f::fl;
	for(i = 0; i < cn; i++)
		for(int e = es[i]; e != -1; e = nx[e]) {
			if(fl[e] != 1) continue;
			printf("%d %d ", inv[to[e]].i, inv[to[e]].j);
			int t = 0;
			for(int f = es[to[e] + 1]; f != -1; f = nx[f]) {
				if(fl[f] != 1) continue;
				if(to[f] != T) t = to[f] - TO + 1;
			}
			printf("%d\n", t);
		}
}

int main() {
	int i, mn, a, b;
	scanf("%d %d", &n, &m);
	scanf("%d", &tn);
	for(i = 0; i < tn; i++) scanf("%d %d %d", &t[i].i, &t[i].j, &tp[i]), oc.insert(t[i]);
	scanf("%d", &cn);
	for(i = 0; i < cn; i++) scanf("%d %d %d", &c[i].i, &c[i].j, &cv[i]);
	scanf("%d", &mn);
	for(i = 0; i < mn; i++) scanf("%d %d", &a, &b), oc.insert(pii(a, b));

	for(i = 0; i < tn; i++) tr[i] = reach(t[i], 2, true);
	for(i = 0; i < cn; i++) cr[i] = reach(c[i], cv[i] - 1);

	i = cn;
	for(auto &e : mp) { e.snd = i; inv[i] = e.fst; i += 2; }
	
	int mi = 0;
	for(i = 1; i < (1 << tn); i++) {
		if(!solve(i)) continue;
		if(__builtin_popcount(i) > __builtin_popcount(mi))
			mi = i;
	}
	printf("%d\n", __builtin_popcount(mi));
	solve(mi, true);
}
