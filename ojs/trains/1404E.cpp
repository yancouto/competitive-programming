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
#define less asdasdasdasdfg

const int TN = 3200000, SN = 3200000, MR = 1009000000, N = 100009;

int sz[TN], x[TN], y[TN], tL[TN], tR[TN];

inline int calc(int u) {
	if(!u) return 0;
	sz[u] = sz[tL[u]] + 1 + sz[tR[u]];
	return u;
}

void split(int u, int z, int &l, int &r) {
	if(!u) return (void)(l = r = 0);
	if(x[u] < z) split(tR[u], z, l, r), tR[u] = l, l = u;
	else split(tL[u], z, l, r), tL[u] = r, r = u;
	calc(u);
}

int merge(int l, int r) {
	if(!l || !r) return max(l, r);
	int u;
	if(y[l] > y[r]) tR[l] = merge(tR[l], r), u = l;
	else tL[r] = merge(l, tL[r]), u = r;
	return calc(u);
}

int sn = 1, tn = 1;
inline int tre_node(int val) { sz[sn] = 1; x[sn] = val; return sn++; }
inline int seg_node(int x=0) { if(!x) x = tn++; return x; }

inline int less(int u, int r) {
	int tot = 0;
	while(u)
		if(x[u] < r) tot += sz[tL[u]] + 1, u = tR[u];
		else u = tL[u];
	return tot;
}

int sL[SN], sR[SN], st[SN];

inline int keth(int i, int l, int r, int k, int ra) {
	while(true) {
		if(l == r) return l;
		int m = (l + r) / 2;
		int ol = less(st[sL[i]], ra);
		if(ol > k) i = sL[i], r = m;
		else i = sR[i], l = m + 1, k -= ol;
	}
}

inline int del_mn(int u) {
	if(!tL[u]) return tR[u];
	int b = u;
	while(tL[tL[u]]) {
		sz[u]--;
		u = tL[u];
	}
	tL[u] = tR[tL[u]];
	sz[u]--;
	return b;
}

inline void add(int i, int l, int r, int val, int ra) {
	while(true) {
		int t1, t2; split(st[i], ra, t1, t2);
		st[i] = merge(merge(t1, tre_node(ra)), t2);
		if(l == r) return;
		int m = (l + r) / 2;
		if(val <= m) i = sL[i] = seg_node(sL[i]), r = m;
		else i= sR[i] = seg_node(sR[i]), l = m + 1;
	}
}
inline void rem(int i, int l, int r, int val, int ra) {
	while(true) {
		int t1, t2; split(st[i], ra, t1, t2);
		st[i] = merge(t1, del_mn(t2));
		if(l == r) return;
		int m = (l + r) / 2;
		if(val <= m) i = sL[i], r = m;
		else i = sR[i], l = m + 1;
	}
}

vector<pii> adj[N];
ll r[N]; int b[N], c[N];

void dfs(int u, int p, int ra, int g, ll cur) {
	if(u) {
		int k = less(st[1], ra);
		if(k == 0) r[u] = g;
		else r[u] = keth(1, 0, MR, (k - 1) / 2, ra) + 1;
		add(1, 0, MR, r[u], ra);
	}
	r[u] += cur;
	for(pii e : adj[u])
		if(e.fst != p)
			dfs(e.fst, u, ::b[e.snd], ::c[e.snd], r[u]);
	if(u) rem(1, 0, MR, r[u] - cur, ra);
}

int main() {
	freopen("paths.in", "r", stdin);
	freopen("paths.out", "w", stdout);
	int i, u, v, n;
	for(i = 0; i < TN; i++) y[i] = i;
	random_shuffle(y, y + TN);
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d %d", &u, &v, &b[i], &c[i]);
		adj[u].pb(pii(v, i));
		adj[v].pb(pii(u, i));
	}
	seg_node();
	dfs(0, 0, -1, -1, 0);
	for(i = 1; i <= n; i++)
		printf("%lld ", r[i]);
	putchar('\n');
}
