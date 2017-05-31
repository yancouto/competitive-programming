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
ll p[N][2], v[2][N], vl[2][N], vr[2][N], va[2][N], tr[2][4 * N];
int n;

void build(int g, int i, int l, int r) {
	if(l == r) return (void) (tr[g][i] = va[g][l]);
	int m = (l + r) / 2;
	build(g, 2 * i, l, m);
	build(g, 2 * i + 1, m + 1, r);
	tr[g][i] = min(tr[g][2 * i], tr[g][2 * i + 1]);
}

ll query(int g, int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return LLONG_MAX;
	if(l >= ql && r <= qr) return tr[g][i];
	int m = (l + r) / 2;
	return min(query(g, 2 * i, l, m, ql, qr), query(g, 2 * i + 1, m + 1, r, ql, qr));
}

inline ll query(int g, int l, int r) { return query(g, 1, 0, n - 1, l, r); }

ll solve(int g, ll x) {
	int i = upper_bound(v[g], v[g] + n, x) - v[g];
	ll d = 0;
	if(i) d += ll(i) * x - vl[g][i - 1];
	if(i < n) d += vr[g][i] - ll(n - i) * x;
	return d;
}

int mv[4]; ll mx[4];
ll d;

ll mn = LLONG_MAX;
void go(int g, ll x) {
	ll l = LLONG_MIN, r = LLONG_MAX;
	int j;
	for(j = 0; j < 4; j++) {
		ll dd = abs(x - p[mv[j]][g]);
		if(dd > d) break;
		l = max(l, p[mv[j]][!g] - (d - dd));
		r = min(r, p[mv[j]][!g] + (d - dd));
	}
	if(j < 4 || r < l) return;
	ll gx = solve(g, x);
	mn = min(mn, gx + solve(!g, l));
	mn = min(mn, gx + solve(!g, r));
	int L = lower_bound(v[!g], v[!g] + n, l) - v[!g];
	int R = int(upper_bound(v[!g], v[!g] + n, r) - v[!g]) - 1;
	if(L <= R && L < n) mn = min(mn, gx + query(!g, L, R));
}

void create(ll xpy, ll xmy) {
	ll x = (xpy + xmy) / 2ll;
	ll y = xpy - x;
	mn = min(mn, solve(0, x) + solve(1, y));
}

int main() {
	int i, j, g;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld", &p[i][0], &p[i][1]);
		v[0][i] = p[i][0];
		v[1][i] = p[i][1];
	}
	sort(v[0], v[0] + n);
	sort(v[1], v[1] + n);
	for(g = 0; g < 2; g++)
		for(i = 0; i < n; i++)
			vl[g][i] = (i? vl[g][i - 1] : 0) + v[g][i];
	for(g = 0; g < 2; g++)
		for(i = n - 1; i >= 0; i--)
			vr[g][i] = (i < n - 1? vr[g][i + 1] : 0) + v[g][i];
	for(g = 0; g < 2; g++)
		for(i = 0; i < n; i++)
			va[g][i] = (v[g][i] * ll(i + 1ll) - vl[g][i]) + (vr[g][i] - ll(n - i) * v[g][i]);
	build(0, 1, 0, n - 1);
	build(1, 1, 0, n - 1);
	scanf("%lld", &d);
	for(j = 0; j < 4; j++)
		for(i = 0; i < n; i++) {
			ll v = p[i][0] * ((j & 1)? 1 : -1) + p[i][1] * ((j & 2)? 1 : -1);
			if(i == 0 || v > mx[j]) mx[j] = v, mv[j] = i;
		}
	ll xpyl = LLONG_MIN, xpyr = LLONG_MAX;
	ll xmyl = LLONG_MIN, xmyr = LLONG_MAX;
	for(j = 0; j < 4; j++) {
		xmyl = max(xmyl, p[mv[j]][0] - p[mv[j]][1] - d);
		xmyr = min(xmyr, p[mv[j]][0] - p[mv[j]][1] + d);
		xpyl = max(xpyl, p[mv[j]][0] + p[mv[j]][1] - d);
		xpyr = min(xpyr, p[mv[j]][0] + p[mv[j]][1] + d);
	}
	if(xpyl > xpyr || xmyl > xmyr) { puts("impossible"); return 0; }
	create(xpyl, xmyl);
	create(xpyl, xmyr);
	create(xpyr, xmyl);
	create(xpyr, xmyr);
	for(g = 0; g < 2; g++)
		for(i = 0; i < n; i++)
			go(g, p[i][g]);
	if(mn == LLONG_MAX) puts("impossible");
	else printf("%lld\n", mn);
}
