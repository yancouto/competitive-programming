#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int MAX = 100009;
const int modn = 1000000007;
inline ull mod(ull u) { return u % modn; }
int n, q;
ull tree[MAX << 2];
ull lazy_set[MAX << 2], lazy_add[MAX << 2], lazy_mult[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }

void build_tree(int i, int from, int to) {
	ull &t = tree[i];
	if(from == to) {
		scanf("%llu", &t);
		return;
	}
	int mid = (from + to) / 2;
	build_tree(l(i), from, mid);
	build_tree(r(i), mid + 1, to);
	tree[i] = mod(tree[l(i)] + tree[r(i)]);
}

void unlaze(int i, int from, int to) {
	if(!lazy_set[i] && !lazy_add[i] && !lazy_mult[i]) return;
	if(lazy_set[i]) {
		tree[i] = mod(lazy_set[i] * (to - from + 1));
		if(from != to)
			for(int j = l(i); j <= r(i); j++)
				lazy_set[j] = lazy_set[i];
	} else {
		ull mult = max(lazy_mult[i], 1ull); 
		tree[i] = mod(mod(tree[i] * mult) + mod(lazy_add[i] * (to - from + 1)));
		if(from != to)
			for(int j = l(i); j <= r(i); j++) {
				if(lazy_set[j])
					lazy_set[j] = mod(mod(lazy_set[j] * mult) + lazy_add[i]);
				else {
					lazy_mult[j] = mod(max(lazy_mult[j], 1ull) * mult);
					lazy_add[j] = mod(mod(lazy_add[j] * mult) + lazy_add[i]);
				}
			}
	}
	lazy_add[i] = lazy_set[i] = lazy_mult[i] = 0;
}

ull query_tree(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return 0;
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return mod(query_tree(l(i), from, mid, ql, qr) + query_tree(r(i), mid + 1, to, ql, qr));
}

void add_tree(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return;
	if(from >= ql && to <= qr) {
		lazy_add[i] = x;
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;	
	add_tree(l(i), from, mid, ql, qr, x);
	add_tree(r(i), mid + 1, to, ql, qr, x);
	tree[i] = mod(tree[l(i)] + tree[r(i)]);
}

void mult_tree(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return;
	if(from >= ql && to <= qr) {
		lazy_mult[i] = x;
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;	
	mult_tree(l(i), from, mid, ql, qr, x);
	mult_tree(r(i), mid + 1, to, ql, qr, x);
	tree[i] = mod(tree[l(i)] + tree[r(i)]);
}

void set_tree(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return;
	if(from >= ql && to <= qr) {
		lazy_set[i] = x;
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;	
	set_tree(l(i), from, mid, ql, qr, x);
	set_tree(r(i), mid + 1, to, ql, qr, x);
	tree[i] = mod(tree[l(i)] + tree[r(i)]);
}

int main() {
	int i, op, x, y, v;
	scanf("%d %d", &n, &q);
	build_tree(1, 0, n - 1);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d", &op, &x, &y); x--; y--;
		if(op != 4) scanf("%d", &v);
		if(op == 1) add_tree(1, 0, n - 1, x, y, v);
		else if(op == 2) mult_tree(1, 0, n - 1, x, y, v);
		else if(op == 3) set_tree(1, 0, n - 1, x, y, v);
		else printf("%llu\n", query_tree(1, 0, n - 1, x, y));
	}
	return 0;
}