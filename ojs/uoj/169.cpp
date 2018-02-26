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

struct dat {
	ll mn, mx, snd;
};

inline dat join(dat a, dat b) {
	dat c;
	c.mn = min(a.mn, b.mn);
	c.mx = max(a.mx, b.mx);
	if(a.mn == b.mn)
		c.snd = min(a.snd, b.snd);
	else
		c.snd = max(a.mn, b.mn);
	return c;
}

const int N = 512345;

dat tr[N << 2];

struct laz {
	ll add, smn;
	reset() {
		add = 0;
		smn = LLONG_MAX;
	}
	join(laz p) {
		add += p.add;
	}
	apply(dat &d) {
		d.mn += add;
		d.mx += add;
		if(d.snd != LLONG_MAX)
			d.snd += add;
	}
};

laz lz[N << 2];

void build(int i, int l, int r) {
	lz[i].reset();
	if(l == r) {
		tr[i].mx = tr[i].mn = A[l];
		tr[i].snd = LLONG_MAX;
		return;
	}
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

inline void unlaze(int i, int l, int r) {
	lz[i].apply(tr[i]);
	if(l != r)
		lz[2 * i].join(lz[i]),
		lz[2 * i + 1].join(lz[i]);
	lz[i].reset();
}

void add(int i, int l, int r, int ql, int qr, ll x) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i].add = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

void smax(int i, int l, int r, int ql, int qr, ll x) {
	unlaze(i, l, r);
	if(l > qr || r < ql || tr[i].mn >= x) return;
	if(l >= ql && r <= qr && tr[i].snd >= x) {
		lz[i].smn = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}


int main() {
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%d", &A[i]);
	build(1, 0, n - 1);
	while(m--) {
		int t, l, r; ll x;
		scanf("%d %d %d", &t, &l, &r); l--; r--;
		if(t == 1) {
			scanf("%lld", &x);
			add(1, 0, n - 1, l, r, x);
		} else if(t == 2) {
			scanf("%lld", &x);
			smax(1, 0, n - 1, l, r, x);
		} else if(t == 3) {
			get(1, 0, n - 1, l, r);
		} else {
		}
	}
}
