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

const int M = 5123456;
int en = 1;
int L[M], R[M], tr[M];

int build(int l, int r) {
	int i = en++;
	L[i] = R[i] = tr[i] = 0;
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

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
	return j;
}

int get(int i, int l, int r, int ql, int qr) {
	if(ql > r || qr < l) return 0;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return get(L[i], l, m, ql, qr) + get(R[i], m + 1, r, ql, qr);
}

const int N = 112345;
int a[N], seg[N], nx[N], b[N];

int main() {
	int i, n, q, l, r, k;
	for_tests(t, tt) {
		en = 1;
		scanf("%d %d", &n, &q);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		nx[n - 1] = 1;
		for(i = n - 2; i >= 0; i--)
			if(a[i] != a[i + 1])
				nx[i] = 1;
			else
				nx[i] = nx[i + 1] + 1;
		for(i = n - 1; i > 0; i--)
			if(a[i] == a[i - 1])
				b[i] = 0;
			else
				b[i] = nx[i];
		b[0] = nx[0];
		//for(i = 0; i < n; i++) printf("%d%c", b[i], " \n"[i == n - 1]);
		seg[0] = build(0, n);
		for(i = 0; i < n; i++)
			if(b[i])
				seg[i + 1] = add1(seg[i], 0, n, b[i]);
			else
				seg[i + 1] = seg[i];
		for(i = 0; i < q; i++) {
			scanf("%d %d %d", &l, &r, &k); r -= k - 1; l--; r--;
			int ans = 0;
			if(nx[l] >= k) ans++;
			l += nx[l];
			if(l <= r)
				ans += get(seg[r + 1], 0, n, k, n) - get(seg[l], 0, n, k, n);
			printf("%d\n", ans);
		}
	}
}
