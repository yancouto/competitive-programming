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
const int N = 512345;

int tr[4 * N];

void build(int i, int l, int r) {
	tr[i] = 1e8;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

int query(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return 1e8;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return min(query(2 * i, l, m, ql, qr), query(2 * i + 1, m + 1, r, ql, qr));
}

void go(int i, int l, int r, int x, int val) {
	tr[i] = min(tr[i], val);
	if(l == r) return;
	int m = (l + r) / 2;
	if(x <= m) go(2 * i, l, m, x, val);
	else go(2 * i + 1, m + 1, r, x, val);
}

int l[N], r[N], pd[N];

int main() {
	scanf("%*d");
	int i, n, m;
	bool f = true;
	while(scanf("%d %d", &n, &m) != EOF) {
		if(!f) putchar('\n');
		else f = false;
		for(i = 0; i < m; i++)
			scanf("%d %d", &l[i], &r[i]);
		int mn = INT_MAX;
		build(1, 0, n);
		for(i = m - 1; i >= 0; i--) {
			if(r[i] == n) pd[i] = 1;
			else pd[i] = query(1, 0, n, l[i], r[i]) + 1;
			go(1, 0, n, l[i], pd[i]);
			if(l[i] == 1) mn = min(mn, pd[i]);
		}
		printf("%d\n", mn);
	}
}
