#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 112345;
const int L = 10;
int a[N];

struct data {
	int sz;
	int xall;
	ll tot;
	int q1l, q1r;
	int q0l() { return sz - q1l; }
	int q0r() { return sz - q1r; }
};

data tr[L][4 * N];

data join(data a, data b) {
	data c = {a.sz + b.sz, a.xall ^ b.xall, a.tot + b.tot, 0, 0};
	c.tot += ll(a.q1l) * ll(b.q0r());
	c.tot += ll(a.q0l()) * ll(b.q1r);
	c.q1l = b.q1l + (b.xall? a.q0l() : a.q1l);
	c.q1r = a.q1r + (a.xall? b.q0r() : b.q1r);
	return c;
}

void build(int b, int i, int l, int r) {
	//if(l == r) printf("[%d] %d %d\n", l, 1, (a[l] >> b) & 1);
	if(l == r) return (void) (tr[b][i] = {1, (a[l] >> b) & 1, (a[l] >> b) & 1, (a[l] >> b) & 1, (a[l] >> b) & 1});
	int m = (l + r) / 2;
	build(b, 2 * i, l, m);
	build(b, 2 * i + 1, m + 1, r);
	tr[b][i] = join(tr[b][2 * i], tr[b][2 * i + 1]);
	//printf("%d[%d,%d]: sz %d xall %d tot %lld q1l %d q1r %d\n", b, l, r, tr[b][i].sz, tr[b][i].xall, tr[b][i].tot, tr[b][i].q1l, tr[b][i].q1r);
}

void upd(int b, int i, int l, int r, int p, int x) {
	if(l == r) return (void) (tr[b][i] = {1, x, x, x, x});
	int m = (l + r) / 2;
	if(p <= m) upd(b, 2 * i, l, m, p, x);
	else upd(b, 2 * i + 1, m + 1, r, p, x);
	tr[b][i] = join(tr[b][2 * i], tr[b][2 * i + 1]);
}

data query(int b, int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return {0, 0, 0, 0, 0};
	if(l >= ql && r <= qr) return tr[b][i];
	int m = (l + r) / 2;
	return join(query(b, 2 * i, l, m, ql, qr), query(b, 2 * i + 1, m + 1, r, ql, qr));
}

int n;

int main() {
	int i, j, k, m;
	rd(n);
	rd(m);
	for(i = 0; i < n; i++) rd(a[i]);
	for(k = 0; k < L; k++) build(k, 1, 0, n - 1);
	for(i = 0; i < m; i++) {
		int a, b, op;
		rd(op); rd(a); rd(b); a--;
		if(op == 1) {
			for(k = 0; k < L; k++) upd(k, 1, 0, n - 1, a, (b >> k) & 1);
		} else {
			b--;
			ll tot = 0;
			for(k = 0; k < L; k++)
				tot += ll(1 << k) * (query(k, 1, 0, n - 1, a, b).tot % 4001ll);
			printf("%d\n", int(tot % 4001));
		}
	}
}
