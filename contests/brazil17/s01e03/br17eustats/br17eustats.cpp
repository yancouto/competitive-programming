#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 312345;

vector<int> v[N], tr[N << 2];

void build(int i, int l, int r) {
	//if(l == r) { printf("%d = %d\n", i, l); }
	if(l == r) { tr[i] = v[l]; return; }
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	int L = 0, R = 0;
	while(L != tr[2 * i].size() || R != tr[2 * i + 1].size()) {
		if(L != int(tr[2 * i].size()) && (R == int(tr[2 * i + 1].size()) || tr[2 * i][L] < tr[2 * i + 1][R]))
			tr[i].pb(tr[2 * i][L++]);
		else
			tr[i].pb(tr[2 * i + 1][R++]);
	}
	//tr[i].resize(tr[2 * i].size() + tr[2 * i + 1].size());
	//merge(tr[2 * i].begin(), tr[2 * i].end(), tr[2 * i + 1].begin(), tr[2 * i + 1].end(), tr[i].begin());
	//for(int x : tr[2 * i]) printf("%d ", x);
	//printf("+");
	//for(int x : tr[2 * i + 1]) printf(" %d", x);
	//printf(" =\n");
	//for(int x : tr[i]) printf("%d ", x);
	//printf("\n");
}

int query(int i, int l, int r, int ql, int qr, int low, int up) {
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr)
		return upper_bound(tr[i].begin(), tr[i].end(), up) - lower_bound(tr[i].begin(), tr[i].end(), low);
	int m = (l + r) / 2;
	return query(2 * i, l, m, ql, qr, low, up) + query(2 * i + 1, m + 1, r, ql, qr, low, up);
}


int x[N], y[N], cx[N], cy[N], w[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
		cx[i] = x[i]; cy[i] = y[i];
	}
	sort(cx, cx + n);
	int cxn = unique(cx, cx + n) - cx;
	sort(cy, cy + n);
	int cyn = unique(cy, cy + n) - cy;
	for(i = 0; i < n; i++) {
		x[i] = lower_bound(cx, cx + cxn, x[i]) - cx;
		y[i] = lower_bound(cy, cy + cyn, y[i]) - cy;
		v[x[i]].pb(y[i]);
	}
	for(i = 0; i < cxn; i++) sort(v[i].begin(), v[i].end());
	build(1, 0, cxn - 1);
	int q, a, b, c, d, e, f, g, h;
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d %d %d", &e, &f, &g, &h);
		a = e ^ (i - 4 < 0? 0 : w[i - 4]);
		b = f ^ (i - 3 < 0? 0 : w[i - 3]);
		c = g ^ (i - 2 < 0? 0 : w[i - 2]);
		d = h ^ (i - 1 < 0? 0 : w[i - 1]);
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		a = lower_bound(cx, cx + cxn, a) - cx;
		b = int(upper_bound(cx, cx + cxn, b) - cx) - 1;
		if(a > b) { puts("0"); continue; }
		c = lower_bound(cy, cy + cyn, c) - cy;
		d = int(upper_bound(cy, cy + cyn, d) - cy) - 1;
		if(c > d) { puts("0"); continue; }
		printf("%d\n", (w[i] = query(1, 0, cxn - 1, a, b, c, d)));
	}
}
