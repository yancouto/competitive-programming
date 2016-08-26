#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000000;
typedef pair<long long, long long> pii;
#define fst first
#define snd second

pii tree[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }

void set_tree(int i, int from, int to, int x, int val) {
	if(from == to) { tree[i] = (val>0)?pii(val, 0) : pii(0, val); return; }
	int mid = (from + to) / 2;
	if(x <= mid) set_tree(l(i), from, mid, x, val);
	else set_tree(r(i), mid + 1, to, x, val);
	pii ll = tree[l(i)], rr = tree[r(i)];
	if(ll.fst > 0) {
		rr.snd += ll.fst;
		if(rr.snd > 0) {
			rr.fst += rr.snd;
			rr.snd = 0;
		}
	}
	rr.snd += ll.snd;
	tree[i] = rr;
}

int main() {
	int i, n, c, d, M, h, m;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d.%d %d:%d", &c, &d, &M, &h, &m);
		int t = m + h * 65 + 35 * 27 * 65 * M + d * 65 * 27;
		set_tree(1, 0, MAX - 1, t, c);
		printf("%lld\n", tree[1].snd);
	}
	return 0;
}
