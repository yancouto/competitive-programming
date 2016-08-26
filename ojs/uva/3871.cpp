// não ia funcionar
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
const int MAX = 100009;
int t[MAX], h[MAX]

inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }
struct ts {
	int h, v;
	ts() {}
	ts(int a, int b) : h(a), v(b) {}
	bool operator < (ts o) const { return (h + v) < (o.h + o.v); }
}
ts tree[MAX << 2];
void build_tree(int i, int from, int to) {
	tree[i] = ts(0, INT_MAX);
	if(from == to) return;
	int mid = (from + to) / 2;
	build_tree(l(i), from, mid);
	build_tree(r(i), mid + 1, to);
}

ts query_tree(int i, int from, int to, int ql, int qr) {
	if(to < ql || from > qr) return ts(0, INT_MAX);
	if(from >= ql && to <= qr) return tree[i];
	int mid = (from + to) / 2;
	return min(query_tree(l(i), from, mid, ql, qr),
	           query_tree(r(i), mid + 1, to, ql, qr));
}

void set_v(int i, int from, int to, int ind, int val) {
	if(from == to) { tree[i].v = val; return; }
	int mid = (from + to) / 2;
	if(ind <= mid) set_2(l(i), from, mid, ind, val);
	else set_2(r(i), mid + 1, to, ind, val);
	tree[i] = min(tree[l(i)], tree[r(i)]);
}

void set_h(int i, int i) {}  



map<int, int> tton, nton;
void add(int i) {
	nton[tton[t[i]]]--;
	nton[++tton[t[i]]]++;
}
void rem(int i) {
	int &x = tton[t[i]];
	nton[x]--; if(nton[x] == 0) nton.erase(x);
	nton[--x]++;
}

int main() {
	for_tests(tn, tc) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &t[i], &h[i]);
		int r = n - 1;
		for(i = n - 1; i >= 0; i--) {
			add(i);
			while(true) {
				auto it = nton.end(); --it;
				if(it->fst <= 1) break;
				rem(r--);				
			}
		}
	}
}
