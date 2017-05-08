#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// D: h[i] + i
// U: h[i] - i
struct no {
	int mnX, mxD, mxU;
};

inline no join(no a, no b) { return {min(a.mnX, b.mnX), max(a.mxD, b.mxD), max(a.mxU, b.mxU)}; }

const int M = 112345 * 5;

no tr[M];

// mxD >= x
int bbrD(int i, int l, int r, int ql, int x) {
	if(r < ql) return INT_MAX;
	if(l == r) return tr[i].mxD >= x? l : INT_MAX;
	int m = (l + r) / 2;
	if(l < ql) {
		int z = bbrD(2 * i, l, m, ql, x);
		if(z != INT_MAX) return z;
		else return bbrD(2 * i + 1, m + 1, r, ql, x);
	}
	if(tr[2*i].mxD >= x) return bbrD(2 * i, l, m, ql, x);
	else return bbrD(2 * i + 1, m + 1, r, ql, x);
}
// mnX <= x
int bbrX(int i, int l, int r, int ql, int x) {
	if(r < ql) return INT_MAX;
	if(l == r) return tr[i].mnX <= x? l : INT_MAX;
	int m = (l + r) / 2;
	if(l < ql) {
		int z = bbrX(2 * i, l, m, ql, x);
		if(z != INT_MAX) return z;
		else return bbrX(2 * i + 1, m + 1, r, ql, x);
	}
	if(tr[2*i].mnX <= x) return bbrX(2 * i, l, m, ql, x);
	else return bbrX(2 * i + 1, m + 1, r, ql, x);
}
// mxU >= x
int bblU(int i, int l, int r, int qr, int x) {
	if(l > qr) return INT_MAX;
	if(l == r) return tr[i].mxU >= x? l : INT_MAX;
	int m = (l + r) / 2;
	if(r > qr) {
		int z = bblU(2 * i + 1, m + 1, r, qr, x);
		if(z != INT_MAX) return z;
		else return bblU(2 * i, l, m, qr, x);
	}
	if(tr[2*i+1].mxU >= x) return bblU(2 * i + 1, m + 1, r, qr, x);
	else return bblU(2 * i, l, m, qr, x);
}
// mnX <= x
int bblX(int i, int l, int r, int qr, int x) {
	if(l > qr) return INT_MAX;
	if(l == r) return tr[i].mnX <= x? l : INT_MAX;
	int m = (l + r) / 2;
	if(r > qr) {
		int z = bblX(2 * i + 1, m + 1, r, qr, x);
		if(z != INT_MAX) return z;
		else return bblX(2 * i, l, m, qr, x);
	}
	if(tr[2*i+1].mnX <= x) return bblX(2 * i + 1, m + 1, r, qr, x);
	else return bblX(2 * i, l, m, qr, x);
}

void set_(int i, int l, int r, int p, no x) {
	if(l == r) return (void)(tr[i] = x);
	int m = (l + r) / 2;
	if(p <= m) set_(2 * i, l, m, p, x);
	else set_(2 * i + 1, m + 1, r, p, x);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

no query(int i, int l, int r, int ql, int qr) {
	if(r < ql || l > qr) return {INT_MAX, INT_MIN, INT_MIN};
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return join(query(2 * i, l, m, ql, qr), query(2 * i + 1, m + 1, r, ql, qr));
}
const int N = 112345;
int x[N], col[N], x2[N], h[N];

void build(int i, int l, int r) {
	if(l == r) return (void) (tr[i] = {x[l], 0 + i, 0 - i});
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}


int main() {
	int i, n, m, k;
	scanf("%d %d", &n, &m); m++;
	for(i = 0; i < n; i++) scanf("%d", &x[i]);
	scanf("%d", &k);
	build(1, 0, n - 1);
	ll cur = accumulate(x, x + n, 0ll);
	for(i = 0; i < k; i++) {
		scanf("%d %d", &col[i], &x2[i]);
		int l, r;
		l = bblU(1, 0, n - 1, col[i], m - col[i]);
		if(l == INT_MAX) l = -1;
		l++;
		r = bbrD(1, 0, n - 1, col[i], m + col[i]);
		if(r == INT_MAX) r = n;
		r--;
		//printf("[%d, %d]\n", l, r);
		int X = query(1, 0, n - 1, l, r).mnX;
		int xl = bblX(1, 0, n - 1, col[i], X);
		if(xl == INT_MAX || xl < l) xl = -3 * n;
		int xr = bbrX(1, 0, n - 1, col[i], X);
		if(xr == INT_MAX || xr > r) xr = 3 * n;
		if(xr - col[i] < col[i] - xl) swap(xl, xr);
		assert(X == x[xl]);
		cur -= X;
		cur += x2[i];
		h[xl]++;
		x[xl] = x2[i];
		set_(1, 0, n - 1, xl, {x[xl], h[xl] + xl, h[xl] - xl});
		printf("%lld\n", cur);
	}
}
