#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 100009;
int k;
int spa[MAX];
int tree[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }
void build_tree(int i, int from, int to) {
	if(from == to) {
		tree[i] = spa[from] = k;
		return;
	}
	int mid = (from + to) / 2;
	build_tree(l(i), from, mid);
	build_tree(r(i), mid + 1, to);
	tree[i] = max(tree[l(i)], tree[r(i)]);
}
void update_tree(int i, int from, int to, int where, int x) {
	if(from == to) {
		tree[i] = spa[from] = spa[from] - x;
		return;
	}
	int mid = (from + to) / 2;
	if(where <= mid) update_tree(l(i), from, mid, where, x);
	else update_tree(r(i), mid + 1, to, where, x);
	tree[i] = max(tree[l(i)], tree[r(i)]);
}
int query_tree(int i, int from, int to, int ql, int qr) {
	if(qr < from || ql > to) return -1;
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return max(query_tree(l(i), from, mid, ql, qr),
	           query_tree(r(i), mid + 1, to, ql, qr));
}

int first_geq(int v) {
	int from = 0, to = MAX - 1;
	while(from < to) {
		int mid = (from + to) / 2;
		int val = query_tree(1, 0, MAX - 1, 0, mid);
		if(val < v) from = mid + 1;
		else to = mid;
	}
	return from;
}

void add(int n, int v) {
	while(n) {
		int i = first_geq(v);
		int t = min(spa[i] / v, n);
		update_tree(1, 0, MAX - 1, i, v * t);
		n -= t;
	}
}

int main() {
	int t, tot, i, r, v;
	char c;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &k, &tot);
		int cat = 0;
		build_tree(1, 0, MAX - 1);
		while(cat < tot) {
			scanf(" %c", &c);
			if(c == 'b') {
				scanf("%d %d", &r, &v);
				add(r, v);
				cat += r;
			} else {
				ungetc(c, stdin);
				scanf("%d", &v);
				add(1, v);
				cat++;
			}
		}
		int w = 0;
		for(i = 0; spa[i] < k; i++)
			w += spa[i];
		printf("%d %d\n", i, w);
	}
	return 0;
}