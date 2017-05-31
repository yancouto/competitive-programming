#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 100009;
int n, q;
int a[MAX], b[MAX];
int tree[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }
int build_tree(int ind, int from, int to) {
	int &t = tree[ind];
	if(from == to) 
		return t = b[from];
	int mid = (from + to) / 2;
	int ll = build_tree(l(ind), from, mid);
	int rr = build_tree(r(ind), mid + 1, to);
	return t = max(ll, rr);
}
int query_tree(int ind, int from, int to, int ql, int qr) {
	if(qr < from || ql > to) return -1;
	if(from >= ql && to <= qr)
		return tree[ind];
	int mid = (from + to) / 2;
	int ll = query_tree(l(ind), from, mid, ql, qr);
	int rr = query_tree(r(ind), mid + 1, to, ql, qr);
	return max(ll, rr);
}

int main() {
	while(true) {
		int i , j = 0, x, y;
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%d %d", &q, &a[0]);
		b[0] = 1; int prev = a[0];
		a[0] = 0;
		for(i = 1; i < n; i++) {
			scanf("%d", &a[i]);
			if(a[i] != prev) b[++j] = 0;
			prev = a[i];
			b[j]++; a[i] = j;
		}
		build_tree(1, 0, j);
		for(i = 0; i < q; i++) {
			scanf("%d %d", &x, &y); x--; y--;
			int mid = query_tree(1, 0, j, a[x] + 1, a[y] - 1);
			int left = min<int>((upper_bound(a, a + n, a[x]) - a), y + 1) - x;
			int right =  y - max<int>((lower_bound(a, a + n, a[y]) - a), x) + 1;
			printf("%d\n", max(left, max(mid, right)));
		}
	}
}