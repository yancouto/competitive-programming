#include <algorithm>
#include <climits>
#include <cassert>
#include <cstdio>
#include <cctype>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int M = 4123456;
int tr[M], lz[M], seen[M], tempo;

inline void unlaze(int i, int l, int r) {
	if(seen[i] < tempo) {
		seen[i] = tempo;
		if(l != r)
			tr[2 * i] = tr[2 * i + 1] = 0;
	}
}

void upd(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	if(l > qr || r < ql || tr[i]) return;
	if(l >= ql && r <= qr) {
		tr[i] = 1;
		return;
	}
	int m = (l + r) / 2;
	upd(2 * i, l, m, ql, qr);
	upd(2 * i + 1, m + 1, r, ql, qr);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}

int get(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	if(l > qr || r < ql || tr[i]) return 1;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return min(get(2 * i, l, m, ql, qr), get(2 * i + 1, m + 1, r, ql, qr));
}

const int N = 112345;
int l[N], r[N], a[N], n, cn;
int seen2[N], st[N], sn, ql[N], qr[N], ql2[N], qr2[N];

inline bool ok(int q) {
	tr[1] = 0;
	tempo++;
	sn = 0;
	for(int i = 0; i < q; i++) {
		if(seen2[a[i]] < tempo) {
			seen2[a[i]] = tempo;
			qr2[a[i]] = ql[a[i]] = INT_MIN;
			ql2[a[i]] = qr[a[i]] = INT_MAX;
		}
		ql[a[i]] = max(ql[a[i]], l[i]);
		ql2[a[i]] = min(ql2[a[i]], l[i]);
		qr[a[i]] = min(qr[a[i]], r[i]);
		qr2[a[i]] = max(qr2[a[i]], r[i]);
		if(ql[a[i]] > qr[a[i]]) return false;
	}
	int i, j;
	for(i = cn - 1; i >= 0; i--) {
		if(seen2[i] < tempo) continue;
		if(get(1, 0, cn - 1, ql[i], qr[i])) return false;
		upd(1, 0, cn - 1, ql2[i], qr2[i]);
	}
	return true;
}

int b[N], c[N];


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

int main() {
	int i, q;
	rd(n); rd(q);
	for(i = 0; i < q; i++)
		rd(l[i]), rd(r[i]), rd(a[i]), b[i] = a[i], c[cn++] = l[i], c[cn++] = r[i], c[cn++] = max(1, l[i] - 1), c[cn++] = min(n, r[i] + 1);
	sort(b, b + q);
	sort(c, c + cn);
	int bn = unique(b, b + q) - b;
	cn = unique(c, c + cn) - c;
	for(i = 0; i < q; i++) {
		l[i] = lower_bound(c, c + cn, l[i]) - c;
		r[i] = lower_bound(c, c + cn, r[i]) - c;
		a[i] = int(lower_bound(b, b + bn, a[i]) - b) + 1;
	}
	if(ok(q)) { puts("0"); return 0; }
	int l = 1, r = q;
	while(l < r) {
		int m = (l + r) / 2;
		if(!ok(m)) r = m;
		else l = m + 1;
	}
	printf("%d\n", l);
}
