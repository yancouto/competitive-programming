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

ll ans = LLONG_MAX;

const int N = 312345;

int n; ll d;
ll v[2][N], vl[2][N], vr[2][N], p[N][2], lc[2][N][20];
int best[10];

inline ll dist(int g, ll x) {
	int i = upper_bound(v[g], v[g] + n, x) - v[g];
	return (i? ll(i) * x - vl[g][i - 1] : 0ll) + (i < n? vr[g][i] - ll(n - i) * x : 0ll);
}

inline ll query(int g, int l, int r) {
	int e = 31 - __builtin_clz(r - l + 1);
	return min(lc[g][l][e], lc[g][r - (1 << e) + 1][e]);
}
ll xpyl = LLONG_MIN, xpyr = LLONG_MAX;
ll xmyl = LLONG_MIN, xmyr = LLONG_MAX;

void fix(int g, ll x) {
	ll l = LLONG_MIN, r = LLONG_MAX;
	if(g) {
		l = max(xpyl - x, x + xmyl);
		r = min(xpyr - x, x + xmyr);
	} else {
		l = max(xpyl - x, x - xmyr);
		r = min(xpyr - x, x - xmyl);
	}
	if(l > r) return;
	ll gx = dist(g, x);
	ans = min(ans, gx + dist(!g, l));
	ans = min(ans, gx + dist(!g, r));
	int L = lower_bound(v[!g], v[!g] + n, l) - v[!g];
	int R = int(upper_bound(v[!g], v[!g] + n, r) - v[!g]) - 1;
	if(L <= R) ans = min(ans, gx + query(!g, L, R));
}

void create(ll xpy, ll xmy) {
	for(ll a = 0; a < 2; a++) {
		for(ll b = 0; b < 2; b++) {
			ll x = (xpy + xmy + a) / 2ll;
			ll y = (xpy - xmy + b) / 2ll;
			if(x + y >= xpyl && x + y <= xpyr && x - y >= xmyl && x - y <= xmyr)
				ans = min(ans, dist(0, x) + dist(1, y));
		}
	}
}

void corners() {
	for(int i = 0; i < n; i++) {
		xpyl = max(xpyl, p[i][0] + p[i][1] - d);
		xpyr = min(xpyr, p[i][0] + p[i][1] + d);
		xmyl = max(xmyl, p[i][0] - p[i][1] - d);
		xmyr = min(xmyr, p[i][0] - p[i][1] + d);
	}
	if(xpyl > xpyr || xmyl > xmyr) { puts("impossible"); exit(0); }
	create(xpyl, xmyl);
	create(xpyl, xmyr);
	create(xpyr, xmyl);
	create(xpyr, xmyr);
}

int main() {
	int i, j, g;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld", &p[i][0], &p[i][1]);
		v[0][i] = p[i][0];
		v[1][i] = p[i][1];
	}
	scanf("%lld", &d);
	sort(v[0], v[0] + n);
	sort(v[1], v[1] + n);
	for(g = 0; g < 2; g++) {
		vl[g][0] = v[g][0]; vr[g][n - 1] = v[g][n - 1];
		for(i = 1; i < n; i++) vl[g][i] = vl[g][i - 1] + v[g][i];
		for(i = n - 2; i >= 0; i--) vr[g][i] = vr[g][i + 1] + v[g][i];
		for(i = n - 1; i >= 0; i--) {
			lc[g][i][0] = dist(g, v[g][i]);
			for(j = 1; i + (1 << j) - 1 < n; j++)
				lc[g][i][j] = min(lc[g][i][j - 1], lc[g][i + (1 << (j - 1))][j - 1]);
		}
	}
	corners();
	for(g = 0; g < 2; g++)
		for(i = 0; i < n; i++)
			fix(g, p[i][g]);
	printf("%lld\n", ans);
}
