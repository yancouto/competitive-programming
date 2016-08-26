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
const int N = 200009;

vector<int> adj[N];

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1) {
		if(p & 1) r = mod(r * x);
		x = mod(x * x);
	}
	return r;
}

inline ll inv(ll x) { return fexp(x, modn - 2); }

inline int L(int i) { return i << 1; }
inline int R(int i) { return L(i) + 1; }

struct segv {
	segv() {}
	segv(int nn) : n(nn), tr(new ll[nn]), lazys(new ll[4*nn] - 1), lazym(new ll[4*nn] - 1) {
		memset(tr, 0, sizeof(ll) * n);
		memset(lazys + 1, 0, sizeof(ll) * 4 * n);
		for(int i = 1; i <= 4*n; i++) lazym[i] = 1;
	}
	int n;
	ll *tr, *lazys, *lazym;
	void unlaze(int i, int l, int r) {
		if(lazys[i] == 0 && lazym[i] == 1) return;
		if(l == r) tr[l] = mod(tr[l] * lazym[i] + lazys[i]);
		else {
			for(int j = L(i); j <= R(i); j++) {
				lazys[j] = mod(lazys[j] * lazym[i] + lazys[i]);
				lazym[j] = mod(lazym[j] * lazym[i]);
			}
		}
		lazym[i] = 1;
		lazys[i] = 0;
	}
	ll get(int i, int l, int r, int x) {
		unlaze(i, l, r);
		if(l == r) return tr[l];
		int m = (l + r) / 2;
		if(x <= m) return get(L(i), l, m, x);
		else return get(R(i), m + 1, r, x);
	}
	inline ll get(int x) { return get(1, 0, n - 1, x); }
	void op(int i, int l, int r, int ql, int qr, ll m, ll s) {
		unlaze(i, l, r);
		if(l > qr || r < ql) return;
		if(l >= ql && r <= qr) {
			lazys[i] = s;
			lazym[i] = m;
			return unlaze(i, l, r);
		}
		int mm = (l + r) / 2;
		op(L(i), l, mm, ql, qr, m, s);
		op(R(i), mm + 1, r, ql, qr, m, s);
	}
	inline void op(int ql, int qr, ll m, ll s) { op(1, 0, n - 1, ql, qr, m, s); }
};
struct segx {
	segx() {}
	segx(int nn) : n(nn), tr(new ll[4*nn] - 1) { build(1, 0, n - 1); }
	int n;
	ll *tr;
	void build(int i, int l, int r) {
		tr[i] = 1;
		if(l == r) return;
		int m = (l + r) / 2;
		build(L(i), l, m);
		build(R(i), m + 1, r);
	}
	ll get(int i, int l, int r, int ql, int qr) {
		if(l > qr || r < ql) return 1;
		if(l >= ql && r <= qr) return tr[i];
		int m = (l + r) / 2;
		return mod(get(L(i), l, m, ql, qr) * get(R(i), m + 1, r, ql, qr));
	}
	inline ll get(int ql, int qr) { return get(1, 0, n - 1, ql, qr); }
	void set(int i, int l, int r, int x, ll val) {
		if(l == r) return (void)(tr[i] = val);
		int m = (l + r) / 2;
		if(x <= m) set(L(i), l, m, x, val);
		else set(R(i), m + 1, r, x, val);
		tr[i] = mod(tr[L(i)] * tr[R(i)]);
	}
	inline void set(int x, ll val) { set(1, 0, n - 1, x, val); }
};

segv val[N]; segx X[N];
int so[N], ch[N], vp[N], vc[N], cs[N];
int S[N], pai[N];

int dfs(int u) {
	int &f = so[u];
	f = 1;
	for(int v : adj[u])
		f += dfs(v);
	return f;
}

int cur = 0;
void hld(int u) {
	vc[u] = cur;
	vp[u] = cs[cur]++;
	if(vp[u] == 0) ch[cur] = u;
	if(adj[u].empty()) {
		val[cur] = segv(cs[cur]);
		X[cur] = segx(cs[cur]);
		return;
	}
	int bi = adj[u].front();
	for(int v : adj[u])
		if(so[v] > so[bi])
			bi = v;
	hld(bi);
	for(int v : adj[u])
		if(v != bi) {
			cur++;
			hld(v);
		}
}
int n;
void deb() {
	for(int i = 0; i < n; i++) {
		assert(S[i] == X[vc[i]].get(vp[i], vp[i]));
		//printf(" X[0..%d] = %I64d\n", i, X[vc[i]].get(vp[i], cs[vc[i]] - 1));
		//printf("  val[%d] = %I64d\n", i, val[vc[i]].get(vp[i]));
		printf("power[%d] = %I64d\n", i, mod(X[vc[i]].get(vp[i], cs[vc[i]] - 1) * val[vc[i]].get(vp[i])));
	}
	puts("--------");
}

int qt[N], qu[N], qv[N];
int main() {
	n = 1; int i, v0, q;
	scanf("%d %d", &v0, &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &qt[i], &qu[i]); qu[i]--;
		if(qt[i] == 1) {
			scanf("%d", &qv[i]);
			pai[n] = qu[i];
			adj[qu[i]].pb(n++);
		}
	}
	for(i = 0; i < n; i++) S[i] = 1;
	dfs(0);
	hld(0);
	val[vc[0]].op(0, 0, 1, ll(v0));
	int nn = 1;
	//printf("prepared\n");
	for(i = 0; i < q; i++) {
		//deb();
		if(qt[i] == 2) {
			int c = vc[qu[i]];
			int p = vp[qu[i]];
			int cn = cs[c];
			//printf("u: %d c: %d p: %d cn: %d\n", qu[i], c, p, cn);
			//printf("%I64d\n", val[c].get(p));
			//printf("*%I64d=\n", X[c].get(p, cn - 1));
			printf("%I64d\n", mod(val[c].get(p) * X[c].get(p, cn - 1)));
		} else {
			int u = qu[i];
			int c = vc[u];
			int p = vp[u];
			int cn = cs[c];
			val[vc[nn]].op(vp[nn], vp[nn], 1, ll(qv[i]));
			ll diff = mod(ll(S[u]) * ll(qv[i]) + val[c].get(p) + ll(qv[i]));
			//printf("diff: %I64d\n", diff);
			while(true) {
				//printf("here\n");
				c = vc[u];
				p = vp[u];
				cn = cs[c];
				ll proc = diff;
				if(p < cn - 1) proc = mod(diff * inv(X[c].get(p + 1, cn - 1)));
				if(qu[i] == u) proc = mod(proc * inv(S[u]));
				//printf("proc %I64d\n", proc);
				val[c].op(0, p, 1, proc);
				if(vc[u] == 0) break;
				//printf("u: %d c: %d p: %d cn: %d\n", u, c, p, cn);
				diff = mod(diff * X[c].get(0, p));
				if(u == qu[i]) diff = mod(diff * inv(S[u]));
				//printf("new diff %I64d\n", diff);
				u = pai[ch[c]];
			}
			u = qu[i];
			c = vc[u];
			p = vp[u];
			cn = cs[c];
			val[c].op(0, p, mod(ll(S[u]) * inv(S[u] + 1)), 0);
			S[u]++; nn++;
			X[c].set(p, S[u]);
		}
	}
}
