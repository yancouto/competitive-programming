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

const int N = 512345;
const int M = N * 50;
int a[N];

int tr[M], L[M], R[M];

int build(int l, int r) {
	int i = en++;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

inline int copy(int i) {
	L[en] = L[i];
	R[en] = R[i];
	tr[en] = tr[i];
	return en++;
}

int add1(int i, int l, int r, int p) {
	int j = copy(i);
	if(l == r) { tr[j]++; return j; }
	int m = (l + r) / 2;
	if(p <= m) L[j] = add1(L[j], l, m, p);
	else R[j] = add1(R[j], m + 1, r, p);
	tr[j] = min(tr[L[j]], tr[R[j]]);
}

int query(int il, int ir, int l, int r) {
	if(l == r) return l;
}

int mex(int l, int r) {
	
}

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 1; i <= n; i++) scanf("%d", &a[i]);
	if(k > n) {
		ll ans = 1;
		for(i = 0; i < n - 1; i++) ans = mod(ans * 2ll);
		printf("%lld\n", ans);
		return 0;
	}
	for(i = 1; i <= n; i++) a[i] = min(a[i], n + 10);
	seg[0] = build(0, N - 1);
	for(i = 1; i <= n; i++)
		seg[i] = add1(seg[i - 1], 0, N - 1, a[i]);
}
