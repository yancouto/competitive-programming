#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pf push_front
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 612345;
int nx[N];
ll dp[N];

ll tr[N], lz[N];
void build(int i, int l, int r) {
	tr[i] = lz[i] = 0;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

void unlaze(int i, int l, int r) {
	tr[i] += lz[i];
	if(l != r) lz[2 * i] += lz[i], lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, ll x) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}

ll min(int i, int l, int r, int ql, int qr) {
	if(ql > qr) return LLONG_MAX;
	unlaze(i, l, r);
	if(l > qr || r < ql) return LLONG_MAX;
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	return min(min(2 * i, l, m, ql, qr), min(2 * i + 1, m + 1, r, ql, qr));
}

ll t[N], h[N];

int main() {
	int i, n;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%lld %lld", &t[i], &h[i]), nx[t[i]] = -1;
		build(1, 0, n - 1);
		dp[n - 1] = h[n - 1];
		add(1, 0, n - 1, n - 1, n - 1, h[n - 1]);
		nx[t[n - 1]] = n - 1;
		int mx = n - 1;
		deque<pii> hs;
		hs.pf(pii(h[n - 1], n - 1));
		for(i = n - 2; i >= 0; i--) {
			int r = i;
			while(!hs.empty() && h[i] >= hs.front().fst) {
				add(1, 0, n - 1, r + 1, hs.front().snd, h[i] - hs.front().fst);
				r = hs.front().snd;
				hs.pop_front();
			}
			if(nx[t[i]] != -1) mx = min(mx, nx[t[i]] - 1);
			nx[t[i]] = i;
			dp[i] = min(dp[i + 1] + h[i], min(1, 0, n - 1, i + 1, mx));
			add(1, 0, n - 1, i, i, dp[i + 1] + h[i]);
			hs.pf(pii(h[i], r));
		}
		printf("Case %d: %lld\n", tt, dp[0]);
	}
}
