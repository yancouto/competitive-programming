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

const int MAX = 250003;
ll tree[MAX << 2], lazyr[MAX << 2], lazyl[MAX << 2], lazys[MAX << 2];
int lr[MAX << 2], rr[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }

void unlazel(int i, int from, int to) {
	ll &x = lazyl[i];
	if(!x) return;
	//printf("ling %lld|%d on (%d, %d) = %lld\n", x, lr[i], from, to, tree[i]);
	tree[i] += ((2ll*x + ll(to - from) * ll(lr[i])) * ll(to - from + 1)) / 2ll;
	//printf("tree[%d] = %lld\n", i, tree[i]);
	if(from != to) {
		lazyl[l(i)] += x;
		lr[l(i)] += lr[i];
		int mid = (from + to) / 2;
		lazyl[r(i)] += ll(mid + 1 - from) * ll(lr[i]) + x;
		lr[r(i)] += lr[i];
	}
	x = 0; lr[i] = 0;
}

void unlazer(int i, int from, int to) {
	ll &x = lazyr[i];
	if(!x) return;
	//printf("ring %lld|%d on (%d, %d) = %lld\n", x, lr[i], from, to, tree[i]);
	tree[i] += ((2ll*x + ll(to - from) * ll(rr[i])) * ll(to - from + 1)) / 2ll;
	//printf("tree[%d] = %lld\n", i, tree[i]);
	if(from != to) {
		lazyr[r(i)] += x;
		rr[r(i)] += rr[i];
		int mid = (from + to) / 2;
		lazyr[l(i)] += ll(to - mid) * ll(rr[i]) + x;
		rr[l(i)] += rr[i];
	}
	x = 0; rr[i] = 0;
}

int seen[MAX << 2];
void unlazes(int i, int from, int to) {
	if(!seen[i]) return;
	ll &x = lazys[i];
	tree[i] = ll(to - from + 1) * x;
	if(from != to) {
		lazys[l(i)] = lazys[r(i)] = x;
		seen[l(i)] = seen[r(i)] = 1;
		lazyr[l(i)] = lazyr[r(i)] = lazyl[l(i)] = lazyl[r(i)] = 0;
		lr[l(i)] = lr[r(i)] = rr[l(i)] = rr[r(i)] = 0;
	}
	seen[i] = 0;
}

void unlaze(int i, int from, int to) {
	unlazes(i, from, to);
	unlazel(i, from, to);
	unlazer(i, from, to);
}

ll get(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return 0;
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return get(l(i), from, mid, ql, qr) + get(r(i), mid + 1, to, ql, qr);
}

void add(int i, int from, int to, int ql, int qr, int op, int x) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		if(op == 0) {
			lazyl[i] = (from - ql + 1);
			lr[i] = 1;
		} else if(op == 1) {
			lazyr[i] = (qr - to + 1);
			rr[i] = 1;
		} else {
			lazys[i] = x;
			seen[i] = 1;
		}
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	add(l(i), from, mid, ql, qr, op, x);
	add(r(i), mid + 1, to, ql, qr, op, x);
	tree[i] = tree[l(i)] + tree[r(i)];
}



int main() {
	int i, n, a, b, x; char op;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf(" %c %d %d", &op, &a, &b); a--; b--;
		if(op == 'A') add(1, 0, MAX - 1, a, b, 0, -1);
		else if(op == 'B') add(1, 0, MAX - 1, a, b, 1, -1);
		else if(op == 'S') printf("%lld\n", get(1, 0, MAX - 1, a, b));
		else {
			scanf("%d", &x);
			add(1, 0, MAX - 1, a, b, 2, x);
		}
	}
}
