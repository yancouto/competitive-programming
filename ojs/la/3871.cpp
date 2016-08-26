#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 100009;
int n;
int p2[MAX];
int t[MAX], h[MAX][25];
inline int mx_h(int s, int e) {
	int sz = 31 - __builtin_clz(e - s + 1);
	return max(h[s][sz], h[e - (1 << sz) + 1][sz]);
}

struct tr {
	int h, p;
	tr() {}
	tr(int a, int b) : h(a), p(b) {}
	bool operator < (tr o) const { return (h + p) < (o.h + o.p); }
};
struct pp {
	tr t;
	int p;
	pp() {}
	pp(int a, int b) : t(a, b), p(b) {}
};

pp tree[MAX << 2];
int lazy[MAX << 2];

pp join(pp a, pp b) {
	pp c;
	c.p = min(a.p, b.p);
	c.t = min(a.t, b.t);
	return c;
}
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }

void build_tree(int i, int from, int to) {
	pp &t = tree[i]; t.t = tr(0, INT_MAX); t.p = INT_MAX; lazy[i] = 0;
	if(from == to) return;
	int m = (from + to) / 2;
	build_tree(l(i), from, m);
	build_tree(r(i), m + 1, to);
}

void unlaze(int i, int from, int to) {
	if(!lazy[i]) return;
	pp &p = tree[i];
	p.t.h = lazy[i];
	p.t.p = p.p;
	if(from != to)
		lazy[l(i)] = lazy[r(i)] = lazy[i];
	lazy[i] = 0;
}

pp query_tree(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return pp(0, INT_MAX);
	if(from >= ql && to <= qr) return tree[i];
	int m = (from + to) / 2;
	return join(query_tree(l(i), from, m, ql, qr), query_tree(r(i), m + 1, to, ql, qr));
}

void set_p(int i, int from, int to, int x, int val) {
	unlaze(i, from, to);
	if(from == to) {
		tree[i].p = val;
		tree[i].t.p = val;
		return;
	}
	int m = (from + to) / 2;
	if(x <= m) set_p(l(i), from, m, x, val);
	else set_p(r(i), m + 1, to, x, val);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}

void set_t(int i, int from, int to, int ql, int qr, int val) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		lazy[i] = val;
		unlaze(i, from, to);
		return;
	}
	int m = (from + to) / 2;
	set_t(l(i), from, m, ql, qr, val);
	set_t(r(i), m + 1, to, ql, qr, val);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}

map<int, int> ct;
map<int, int> oc;

void add(int i) {
	ct[oc[i]]--;
	ct[++oc[i]]++;
}

void rem(int i) {
	ct[oc[i]]--; if(ct[oc[i]] == 0) ct.erase(oc[i]);
	ct[--oc[i]]++;
}

int main() {
	int i, j = -1;
	for_tests(tn, tc) {
		ct.clear(); oc.clear();
		scanf("%d", &n);
		build_tree(1, 0, n - 1);
		for(i = 0; i < n; i++)
			scanf("%d %d", &t[i], &h[i][0]);
		for(i = 1; i < 25; i++)
			for(j = 0; j < n; j++) {
				if(j + (1 << (i - 1)) >= n) { h[j][i] = h[j][i - 1]; continue; }
				h[j][i] = max(h[j][i - 1], h[j + (1 << (i - 1))][i - 1]);
			}
		ct[0] = 0; set_p(1, 0, n - 1, n - 1, 0);
		int qr = n - 1, resp;
		for(i = n - 1; i >= 0; i--) {
			add(t[i]);
			while(true) {
				map<int, int>::iterator it = ct.end(); --it;
				if(it->fst > 1) rem(t[qr--]);
				else break;
			}
			int l1 = i, r1 = qr;
			while(l1 < r1) {
				int m = (l1 + r1 + 1) / 2;
				if(mx_h(i, m) == h[i][0]) l1 = m;
				else r1 = m - 1;
			}
			set_t(1, 0, n - 1, i, l1, h[i][0]); 
			pp p = query_tree(1, 0, n - 1, i, qr);
			if(i > 0) set_p(1, 0, n - 1, i - 1, p.t.p + p.t.h);
			else resp = p.t.h + p.t.p;
		}
		printf("Case %d: %d\n", tc, resp);
	}
	return 0;
}
