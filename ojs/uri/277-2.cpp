#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int N = 312345;
typedef long long ll;

ll tr[4 * N];
ll ans[N], a[N], val[N];

void build(int i, int l, int r) {
	if(l == r) return (void) (tr[i] = ans[l]);
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}

ll query(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return LLONG_MIN;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(query(2 * i, l, m, ql, qr), query(2 * i + 1, m + 1, r, ql, qr));
}

int nx[N];

int main() {
	int i, n, q, l, r;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) scanf("%lld", &a[i]);
	ans[0] = a[0]; val[0] = a[0];
	for(i = 1; i < n; i++)
		if(a[i] == a[i - 1]) {
			val[i] = max(0ll, val[i - 1] - 1ll);
			ans[i] = ans[i - 1] + val[i];
		} else {
			ans[i] = val[i] = a[i];
		}
	nx[n - 1] = n - 1;
	for(i = n - 2; i >= 0; i--)
		if(a[i] == a[i + 1])
			nx[i] = nx[i + 1];
		else
			nx[i] = i;
	build(1, 0, n - 1);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &l, &r); l--; r--;
		ll ret;
		ll sz = min<ll>(min<ll>(nx[l], r) - l + 1, a[l]);
		ret = ((2ll * a[l] - sz + 1ll) * sz) / 2ll;
		if(nx[l] < r) {
			int nl = nx[l] + 1;
			ret = max(ret, query(1, 0, n - 1, nl, r));
		}
		printf("%lld\n", ret);
	}
}
