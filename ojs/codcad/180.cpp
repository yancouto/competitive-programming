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

const int N = 112345;
int a[N], b[N], seg[N];
const int M = 11234567;
int L[M], R[M], tr[M], en = 1;

inline int copy(int x) {
	L[en] = L[x]; R[en] = R[x]; tr[en] = tr[x];
	return en++;
}

int add1(int i, int l, int r, int p) {
	int j = copy(i);
	tr[j]++;
	if(l == r) return j;
	int m = (l + r) / 2;
	if(p <= m) L[j] = add1(L[j], l, m, p);
	else R[j] = add1(R[j], m + 1, r, p);
	//printf("%d:%d,%d: (%d, %d) = %d\n", j, L[j], R[j], l, r, tr[j]);
	return j;
}

int query(int il, int ir, int l, int r, int k) {
	assert(tr[ir] - tr[il] >= k);
	assert(il  || ir);
	if(l == r) return b[l];
	int m = (l + r) / 2;
	//printf("[%d][%d](%d,%d) %d - %d >= %d\n", L[il], L[ir], l, m, tr[L[ir]], tr[L[il]], k);
	if(tr[L[ir]] - tr[L[il]] >= k) return query(L[il], L[ir], l, m, k);
	else return query(R[il], R[ir], m + 1, r, k - (tr[L[ir]] - tr[L[il]]));
}

int main() {
	int i, n, q;
	scanf("%d %d", &n, &q);
	for(i = 1; i <= n; i++) scanf("%d", &a[i]), b[i - 1] = a[i];
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	for(i = 1; i <= n; i++) a[i] = lower_bound(b, b + bn, a[i]) - b;
	seg[0] = 0;
	for(i = 1; i <= n; i++)
		seg[i] = add1(seg[i - 1], 0, bn - 1, a[i]);
	int a, b, k; char op;
	for(i = 0; i < q; i++) {
		scanf(" %c %d", &op, &a);
		if(op == 'Q') {
			scanf("%d %d", &b, &k);
			printf("%d\n", query(seg[a - 1], seg[b], 0, bn - 1, k));
		} else {
			swap(::a[a], ::a[a + 1]);
			seg[a] = add1(seg[a - 1], 0, bn - 1, ::a[a]);
		}
	}
}
