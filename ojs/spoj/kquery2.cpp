#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 31234, M = 11234567;
const int lg = 14;
int T[M][2], val[M], en = 1;

struct ord_set {
	const int root;
	ord_set() : root(en++) {}
	void insert(int x) {
		int r = root; val[r]++;
		for(int i = lg - 1; i >= 0; i--) {
			int b = ((x >> i) & 1);
			if(!T[r][b]) T[r][b] = en++;
			assert(T[r][b]);
			r = T[r][b];
			val[r]++;
		}
	}
	inline int size() { return val[root]; }
	void erase(int x) {
		int r = root; val[r]--;
		for(int i = lg - 1; i >= 0; i--) {
			int b = ((x >> i) & 1);
			assert(T[r][b]);
			r = T[r][b];
			val[r]--;
		}
	}
	int order_of_key(int x) {
		int r = root;
		int ans = 0;
		for(int i = lg - 1; i >= 0; i--) {
			int b = ((x >> i) & 1);
			if(b == 1 && T[r][0]) ans += val[T[r][0]];
			if(T[r][b]) r = T[r][b];
			else break;
		}
		return ans;
	}
};


int a[N];
ord_set tr[N * 4];
void build(int i, int l, int r) {
	if(l == r) { tr[i].insert(a[l]); return; }
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	for(int j = l; j <= r; j++) tr[i].insert(a[j]);
}

inline void upd(int i, int l, int r, int p, int v) {
	while(true) {
		tr[i].erase(a[p]);
		tr[i].insert(v);
		if(l == r) return;
		int m = (l + r) / 2;
		if(p <= m) i *= 2, r = m;
		else i = 2 * i + 1, l = m + 1;
	}
}

int query(int i, int l, int r, int ql, int qr, int x) {
	if(r < ql || l > qr) return 0;
	if(l >= ql && r <= qr) return tr[i].size() - tr[i].order_of_key(x + 1);
	int m = (l + r) / 2;
	return query(2 * i, l, m, ql, qr, x) + query(2 * i + 1, m + 1, r, ql, qr, x);
}

inline int get(int &x) {
	static char c;
	while(isspace(c = getchar()));
	x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + (c - '0');
}

inline void prn(int x) {
	if(!x) { putchar('0'); putchar('\n'); return; }
	int y = 0, ct = 0;
	while(x) ct++, y = (y << 3) + (y << 1) + (x % 10), x /= 10;
	while(ct--) putchar((y % 10) + '0'), y /= 10;
	putchar('\n');
}

int main() {
	int i, n, op, l, r, k;
	get(n);
	for(i = 0; i < n; i++) get(a[i]);
	build(1, 0, n - 1);
	for_tests(q, qq) {
		get(op); get(l); get(r);
		if(op == 0) {
			upd(1, 0, n - 1, l - 1, r);
			a[l - 1] = r;
		} else {
			get(k);
			prn(query(1, 0, n - 1, l - 1, r - 1, k));
		}
	}
}
