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
const int N = 100009;
inline int L(int i) { return i << 1; }
inline int R(int i) { return L(i) + 1; }
ll ts[N << 2], lazy[N << 2];
int a[N];
void build(int i, int le, int ri) {
	if(le == ri) {
		ts[i] = a[le];
		return;
	}
	int mi = (le + ri) / 2;
	build(L(i), le, mi);
	build(R(i), mi + 1, ri);
	ts[i] = ts[L(i)] + ts[R(i)];
}

void unlaze(int i, int le, int ri) {
	if(!lazy[i]) return;
	ts[i] += ll(ri - le + 1) * lazy[i];
	if(le != ri) lazy[L(i)] += lazy[i], lazy[R(i)] += lazy[i];
	lazy[i] = 0;
}

void add(int i, int le, int ri, int ql, int qr, ll val) {
	unlaze(i, le, ri);
	if(le > qr|| ri < ql) return;
	if(le >= ql && ri <= qr) {
		lazy[i] = val;
		unlaze(i, le, ri);
		return;
	}
	int mi = (le + ri) / 2;
	add(L(i), le, mi, ql, qr, val);
	add(R(i), mi + 1, ri, ql, qr, val);
	ts[i] = ts[L(i)] + ts[R(i)];
}

void flush(int i, int le, int ri) {
	unlaze(i, le, ri);
	if(le == ri) {
		printf("%I64d ", ts[i]);
		return;
	}
	int mi = (le + ri) / 2;
	flush(L(i), le, mi);
	flush(R(i), mi + 1, ri);
}


int acc[N], le[N], ri[N], d[N];
int main() {
	int i, j, n, m, k, x, y;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	build(1, 0, n - 1);
	for(i = 0; i < m; i++)
		scanf("%d %d %d", &le[i], &ri[i], &d[i]);
	for(i = 0; i < k; i++) {
		scanf("%d %d", &x, &y); x--; y--;
		acc[x]++; acc[y + 1]--;
	}
	int s = 0;
	for(i = 0; i < m; i++) {
		s += acc[i]; le[i]--; ri[i]--;
		add(1, 0, n - 1, le[i], ri[i], ll(d[i]) * ll(s));
	}
	flush(1, 0, n - 1);
	putchar('\n');
}
