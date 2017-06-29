#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 212345;

ll tr[N << 2], a[N];

void build(int i, int l, int r) {
	if(l == r) return (void) (tr[i] = a[l]);
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}


// first element with index >= ql and value <= x
int nx(int i, int l, int r, int ql, ll x) {
	if(tr[i] > x) return INT_MAX;
	if(r < ql) return INT_MAX;
	if(l == r) return l;
	int m = (l + r) / 2;
	int j = nx(2 * i, l, m, ql, x);
	if(j != INT_MAX) return j;
	return nx(2 * i + 1, m + 1, r, ql, x);
}

int main () {
	int n, Q, i, l, r; ll v;
	scanf("%d %d", &n, &Q);
	for(i = 0; i < n; i++) scanf("%lld", &a[i]);
	build(1, 0, n - 1);
	for(i = 0; i < Q; i++) {
		scanf("%lld %d %d", &v, &l, &r); l--; r--;
		while(l <= r) {
			int nl = nx(1, 0, n - 1, l, v);
			if(nl > r) break;
			v %= a[nl];
			l = nl;
		}
		printf("%lld\n", v);
	}
}
