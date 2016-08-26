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
int tc[MAX], tn[MAX], tp[MAX], lc[MAX << 2], ln[MAX << 2], lp[MAX << 2];
ll ts[MAX << 2], ls[MAX << 3];
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }

void build_tree(int i, int from, int to) {
	lc[i] = ln[i] = lp[i] = -1;
	ts[i] = 0; ls[i] = 0;
	if(from == to) {
		tc[from] = from + 1;
		tn[from] = from + 1;
		tp[from] = from;
		return;
	}
	int mid = (from + to) / 2;
	build_tree(l(i), from, mid);
	build_tree(r(i), mid + 1, to);
}

void unlaze(int i, int from, int to, int lz[], int t[]) {
	if(lz[i] == -1) return;
	if(from == to)
		t[from] = lz[i];
	else
		lz[l(i)] = lz[r(i)] = lz[i];
	lz[i] = -1;
}

inline void unlaze_c(int i, int from, int to) { unlaze(i, from, to, lc, tc); }
inline void unlaze_n(int i, int from, int to) { unlaze(i, from, to, ln, tn); }
inline void unlaze_p(int i, int from, int to) { unlaze(i, from, to, lp, tp); }

int query_ncp(int i, int from, int to, int xn, int xc, int xp) {
	unlaze_c(i, from, to);
	unlaze_n(i, from, to);
	unlaze_p(i, from, to);
	if(from == to) {
		if(xn != -1) return tn[from];
		if(xc != -1) return tc[from];
		return tp[from];
	}
	int mid = (from + to) / 2;
	if(xn * xc * xp <= mid) return query_ncp(l(i), from, mid, xn, xc, xp);
	else return query_ncp(r(i), mid + 1, to, xn, xc, xp);
}

void set_ncp(int i, int from, int to, int ql, int qr, int xn, int xc, int xp) {
	unlaze_c(i, from, to);
	unlaze_n(i, from, to);
	unlaze_p(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		if(xc != -1) {
			lc[i] = xc;
			unlaze_c(i, from, to);
		} else if(xn != -1) {
			ln[i] = xn;
			unlaze_n(i, from, to);
		} else {
			lp[i] = xp;
			unlaze_p(i, from, to);
		}
		return;
	}
	int mid = (from + to) / 2;
	set_ncp(l(i), from, mid, ql, qr, xn, xc, xp);
	set_ncp(r(i), mid + 1, to, ql, qr, xn, xc, xp);
}

void unlaze_s(int i, int from, int to) {
	if(!ls[i]) return;
	ts[i] += ll(to - from + 1) * ls[i];
	if(from != to) {
		ls[l(i)] += ls[i];
		ls[r(i)] += ls[i];
	}
	ls[i] = 0;
}

ll query_s(int i, int from, int to, int ql, int qr) {
	unlaze_s(i, from, to);
	if(from > qr || to < ql) return 0;
	if(from >= ql && to <= qr) return ts[i];
	int mid = (from + to) / 2;
	return query_s(l(i), from, mid, ql, qr) +
	       query_s(r(i), mid + 1, to, ql, qr);
}

void add_s(int i, int from, int to, int ql, int qr, ll x) {
	unlaze_s(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		ls[i] = x;
		unlaze_s(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	add_s(l(i), from, mid, ql, qr, x);
	add_s(r(i), mid + 1, to, ql, qr, x);
	ts[i] = ts[l(i)] + ts[r(i)];
}




int main() {
	int i, n, m, op, ql, qr, x;
	scanf("%d %d", &n, &m);
	build_tree(1, 0, n - 1);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &op, &ql, &qr); ql--; qr--;
		if(op == 1) {
			scanf("%d", &x);
			int oql = ql;
			while(ql <= qr) {
				int c = query_ncp(1, 0, n - 1, -1, ql, -1);
				int nxt = query_ncp(1, 0, n - 1, ql, -1, -1);
				int prv = query_ncp(1, 0, n - 1, -1, -1, ql);
				if(oql > prv) {
					set_ncp(1, 0, n - 1, prv, oql - 1, oql, -1, -1);
				}
				if(nxt > qr) {
					set_ncp(1, 0, n - 1, qr + 1, nxt, -1, -1, qr + 1);
				}
				add_s(1, 0, n - 1, ql, min(nxt - 1, qr), abs(c - x));
				ql = nxt;
			}
			set_ncp(1, 0, n - 1, oql, qr, -1, x, -1);
			set_ncp(1, 0, n - 1, oql, qr, qr + 1, -1, -1);
			set_ncp(1, 0, n - 1, oql, qr, -1, -1, oql);
		} else
			printf("%lld\n", query_s(1, 0, n - 1, ql, qr));
	}
}
