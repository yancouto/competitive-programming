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

struct no {
	// all, no left, no right, no right or left
	ll a, l, r, lr;
	int il, ir;
	inline int sz() { return ir - il + 1; }
	no() : a(1), l(1), r(1), lr(1), il(-1), ir(-1) {}
};
const int N = 812345;
ll nx[N], pr[N], sl[N];

no join(no &a, no &b) {
	if(a.il == -1) return b;
	if(b.il == -1) return a;
	no c;
	c.il = a.il;
	c.ir = b.ir;
	ll np = mod(nx[a.ir] * pr[b.il]);
	c.a = mod(a.a * b.a);
	if(a.sz() > 0 && b.sz() > 0) c.a = mod(c.a + np * mod(a.r * b.l));

	c.l = mod(a.l * b.a);
	if(a.sz() > 1 && b.sz() > 0) c.l = mod(c.l + np * mod(a.lr * b.l));

	c.r = mod(a.a * b.r);
	if(a.sz() > 0 && b.sz() > 1) c.r = mod(c.r + np * mod(a.r * b.lr));

	c.lr = mod(a.l * b.r);
	if(a.sz() > 1 && b.sz() > 1) c.lr = mod(c.lr + np * mod(a.lr * b.lr));

	return c;
}

no tr[4 * N];

void upd(int i, int l, int r, int p) {
	if(l == r) {
		tr[i] = no();
		tr[i].il = tr[i].ir = p;
		tr[i].a = sl[p];
		return;
	}
	int m = (l + r) / 2;
	if(p <= m) upd(2 * i, l, m, p);
	else upd(2 * i + 1, m + 1, r, p);
	tr[i] = join(tr[2*i], tr[2*i + 1]);
}

ll w[N], d[N], s[N], z[N];

int main() {
	int i, n, m;
	ll aw, bw, ad, bd, as, bs;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		scanf("%lld %lld %lld", &w[0], &aw, &bw);
		scanf("%lld %lld %lld", &d[0], &ad, &bd);
		scanf("%lld %lld %lld", &s[0], &as, &bs);
		for(i = 1; i < m; i++) w[i] = ((aw * w[i - 1] + bw) % ll(n)) + 1ll;
		for(i = 1; i < m; i++) d[i] = ((ad * d[i - 1] + bd) % 3ll);
		for(i = 0; i < m; i++) z[i] = max(1ll, min<ll>(n, w[i] + d[i] - 1ll));
		for(i = 1; i < m; i++) s[i] = ((as * s[i - 1] + bs) % 1000000000ll) + 1;


		for(i = 0; i < n; i++) sl[i] = 1, nx[i] = pr[i] = 0;
		for(i = 0; i < n; i++) upd(1, 0, n - 1, i);
		assert(tr[1].a == 1);

		ll ans = 0;
		for(i = 0; i < m; i++) {
			//printf("(%lld, %lld) += %lld\n", w[i], z[i], s[i]);
			z[i]--; w[i]--;
			if(z[i] > w[i]) nx[w[i]] = mod(nx[w[i]] + s[i]);
			else if(z[i] < w[i]) pr[w[i]] = mod(pr[w[i]] + s[i]);
			else sl[w[i]] = mod(sl[w[i]] + s[i]);
			upd(1, 0, n - 1, w[i]);
			//printf("cur %lld\n", tr[1].a);
			ans += tr[1].a;
		}
		printf("Case #%d: %lld\n", tt, mod(ans));
	}
}
