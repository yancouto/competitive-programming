#include <cstdio>
#include <algorithm>
#include <climits>
#include <unordered_map>
using namespace std;
const int MAX = 200009;
int n;

inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }
int tree[MAX << 2], lazy[MAX << 2];
void build_tree(int i, int from, int to) {
	lazy[i] = 0;
	tree[i] = 0;
	if(from != to) {
		int mid = (from + to) / 2;
		build_tree(l(i), from, mid);
		build_tree(r(i), mid + 1, to);
	}
}

void unlaze(int i, int f, int t) {
	if(!lazy[i]) return;
	tree[i] += lazy[i];
	if(f != t) {
		lazy[l(i)] += lazy[i];
		lazy[r(i)] += lazy[i];
	}
	lazy[i] = 0;
}

void update_tree(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return;
	if(from >= ql && to <= qr) {
		lazy[i] = x;
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	update_tree(l(i), from, mid, ql, qr, x);
	update_tree(r(i), mid + 1, to, ql, qr, x);
	tree[i] = min(tree[l(i)], tree[r(i)]);
}

int query_tree(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(qr < from || ql > to) return INT_MAX;
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return min(query_tree(l(i), from, mid, ql, qr), query_tree(r(i), mid + 1, to, ql, qr));
}

int main() {
	int t, x;
	scanf("%d", &t);
	while(t--) {
		unordered_map<int, int> m1, m2;
		scanf("%d", &n);
		build_tree(1, 0, n);
		bool boring = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if(boring) continue;
			if(!m1.count(x)) {
				update_tree(1, 0, n, 0, i - 1, 1);
				m2[x] = i; m1[x] = -1;
			} else{
				update_tree(1, 0, n, m1[x] + 1, m2[x] - 1, -1);
				m1[x] = m2[x];
				if(m1[x] != i - 1)
					update_tree(1, 0, n, m1[x] + 1, i - 1, 1);
				m2[x] = i;
			}
			if(query_tree(1, 0, n, 0, i - 1) == 0) boring = true;
		}
		if(boring) puts("boring");
		else puts("non-boring");
	}
	return 0;
}