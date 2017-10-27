#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1123456;
int tr[N << 2];
int a[N], l[N], r[N], p[N], ans[N];

void build(int i, int l, int r) {
	tr[i] = N;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

void upd(int i, int l, int r, int p, int x) {
	if(l == r) return (void)(tr[i] = x);
	int m = (l + r) / 2;
	if(p <= m) upd(2 * i, l, m, p, x);
	else upd(2 * i + 1, m + 1, r, p, x);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}

int go(int i, int l, int r, int lm) {
	if(l == r) return l;
	int m = (l + r) / 2;
	if(tr[2 * i] > lm) return go(2 * i, l, m, lm);
	return go(2 * i + 1, m + 1, r, lm);
}

int main () {
	int i, n, q;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	scanf("%d", &q);
	for(i = 0; i < q; i++) scanf("%d %d", &l[i], &r[i]), l[i]--, r[i]--, p[i] = i;
	sort(p, p + q, [](int i, int j) { return l[i] > l[j]; });
	int qn = 0;
	build(1, 0, N - 1);
	for(i = n - 1; i >= 0; i--) {
		upd(1, 0, N - 1, a[i], i);
		for(; qn < q && l[p[qn]] == i; qn++) {
			ans[p[qn]] = go(1, 0, N - 1, r[p[qn]]);
		}
	}
	for(i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
