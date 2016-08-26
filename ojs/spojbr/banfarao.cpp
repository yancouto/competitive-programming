#include <bits/stdc++.h>
using namespace std;
#define sum first
#define sz second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
struct obj {
	pii best, left, right, all;
	obj() {}
	obj(int x) : best(x, 1), left(x, 1), right(x, 1), all(x, 1) {}
} tr[4*N];
pii operator+(pii a, pii b) { return pii(a.sum + b.sum, a.sz + b.sz); }

obj join(obj a, obj b) {
	if(a.all.sum == INT_MIN) return b;
	if(b.all.sum == INT_MIN) return a;
	a.best = max(max(a.best, b.best), a.right + b.left);
	a.left = max(a.left, a.all + b.left);
	a.right = max(b.right, b.all + a.right);
	a.all = a.all + b.all;
	return a;
}

int a[N];

void build(int i, int l, int r) {
	if(l == r) return (void) (tr[i] = obj(a[l]));
	int m = (l + r) / 2;
	build(2*i, l, m);
	build(2*i + 1, m + 1, r);
	tr[i] = join(tr[2*i], tr[2*i+1]);
}

obj query(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return obj(INT_MIN);
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return join(query(2*i, l, m, ql, qr), query(2*i+1, m + 1, r, ql, qr));
}

int main() {
	int i, n, l, r;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		build(1, 0, n - 1);
		for_tests(q, qq) {
			scanf("%d %d", &l, &r); l--; r--;
			pii a = query(1, 0, n - 1, l, r).best;
			printf("%d %d\n", a.sum, a.sz);
		}
	}
}
