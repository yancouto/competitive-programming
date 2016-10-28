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

int tr[4 * 112345], a[112345];

void build(int i, int l, int r) {
	tr[i] = -1;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

void upd(int i, int l, int r, int x, int v) {
	if(l == r) return (void) (tr[i] = v);
	int m = (l + r) / 2;
	if(x <= m) upd(2 * i, l, m, x, v);
	else upd(2 * i + 1, m + 1, r, x, v);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}

int query(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return -1;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return max(query(2 * i, l, m, ql, qr), query(2 * i + 1, m + 1, r, ql, qr));
}
set<int> oc[1123456];

int main() {
	int i, n, r, k, x; char op;
	while(scanf("%d %d", &n, &r) != EOF) {
		build(1, 0, n - 1);
		for(i = 0; i < n; i++) {
			scanf("%d", &x); a[i] = x;
			if(!oc[x].empty())
				upd(1, 0, n - 1, i, *oc[x].rbegin());
			oc[x].insert(i);
		}
		for(i = 0; i < r; i++) {
			scanf(" %c %d", &op, &k); k--;
			if(op == 'C') {
				scanf("%d", &x);
				if(a[k] == x) continue;
				auto it = oc[a[k]].find(k);
				if(next(it) != oc[a[k]].end()) {
					int z = *next(it);
					if(it != oc[a[k]].begin()) upd(1, 0, n - 1, z, *prev(it));
					else upd(1, 0, n - 1, z, -1);
				}
				oc[a[k]].erase(it); a[k] = x;
				it = oc[x].lower_bound(k);
				if(it != oc[x].end())
					upd(1, 0, n - 1, *it, k);
				if(it != oc[x].begin())
					upd(1, 0, n - 1, k, *prev(it));
				else upd(1, 0, n - 1, k, -1);
				oc[x].insert(k);
			} else {
				int l = 0, r = k;
				while(l < r) {
					int m = (l + r) / 2;
					//printf("(%d, %d) = %d\n", m, k, query(1, 0, n - 1, m, k));
					if(query(1, 0, n - 1, m, k) >= m) l = m + 1;
					else r = m;
				}
				//printf("can until %d bc %d < %d\n", l, query(1, 0, n - 1, l, k), l);
				printf("%d\n", k - l + 1); //+1?
			}
		}
		for(i = 0; i < n; i++) oc[a[i]].clear();
	}
}
