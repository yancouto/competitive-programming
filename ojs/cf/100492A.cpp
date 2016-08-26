#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#define temp template<typename num>
#define ptn point<num>
temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<ll> pti;
temp inline num cross(ptn a, ptn b, ptn c) { return (b - a) ^ (c - a); }

temp int sign(num x) { return (x > 0) - (x < 0); }

int convex_hull(pti p[], pti st[], int n) {
	int sn = 0;
	for(int i = 0; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], p[i]) >= 0)
			sn--;
		st[sn++] = p[i];
	}
	int k = sn;
	for(int i = n - 2; i >= 0; i--) {
		while(sn > k && cross(st[sn - 2], st[sn - 1], p[i]) >= 0)
			sn--;
			st[sn++] = p[i];
	}
	return --sn;
	//st[0..sn-1] tem o convex hull dos pontos de p -- horario eu acho
}

#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 212345;
pti p[N], cv[N], oncv[N], K[N], st[N];
vector<pti> pts[N];

int bins(int l, int r, int off, pti q) {
	if(cross(cv[off], cv[2*r + off], q) <= 0) return 2 * r + off;
	r--;
	while(l < r) {
		int m = (l + r + 1) / 2;
		int rm = 2*m + off;
		if(cross(cv[off], cv[rm], q) < 0) l = m;
		else r = m - 1;
	}
	return 2*l + off;
}

void proc(pti q, int o) {
	if(cross(cv[o], cv[o + 2], q) >= 0) pts[o].pb(q);
}

ll mdc(ll a, ll b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

void ex(ll tot, ll n) {
	ll k = mdc(tot, n);
	printf(LLD "/" LLD "\n", tot / k, n / k);
	exit(0);
}

pti o[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("average.in", "r", stdin);
	freopen("average.out", "w", stdout);
#endif
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf(LLD LLD, &p[i].x, &p[i].y);
	sort(p, p + n);
	for(i = 0; i < n; i++) o[i] = p[i];
	int cn = convex_hull(p, cv, n);
	for(i = 0; i < cn; i++) oncv[i] = cv[i];
	cv[cn] = cv[0];
	cv[cn + 1] = cv[1];
	cv[cn + 2] = cv[2];
	sort(oncv, oncv + cn);
	j = 0;
	// two pointers em vez de BB?
	for(i = 0; i < n; i++)
		if(!binary_search(oncv, oncv + cn, p[i]))
			p[j++] = p[i];
	n = j;
	if(cn <= 5) {
		ll tot = 0;
		for(i = 0; i < cn; i++) {
			int sn = 0;
			for(j = 0 ; j < n + cn; j++)
				if(o[j].x != cv[i].x || o[j].y != cv[i].y)
					K[sn++] = o[j];
			int g = convex_hull(K, st, sn);
			tot += g;
		}
		ex(tot + ll(n) * ll(cn), n + cn);
	}
	//ordenar por angulo em vez de BB?
	for(i = 0; i < n; i++) {
		int o1 = bins(0, (cn/2) - 1, 0, p[i]);
		int o2 = bins(0, (cn/2) - 1, 1, p[i]);
		proc(p[i], o1);
		proc(p[i], o2);
		if(cn & 1) proc(p[i], cn - 1);
	}
	ll tot = ll(n) * ll(cn);
	for(i = 0; i < cn; i++) {
		int sn = 0;
		for(pti p : pts[i])
			K[sn++] = p;
		K[sn++] = cv[i + 2];
		for(int k = sn - 1; k > 0 && K[k] < K[k - 1]; k--) swap(K[k], K[k-1]);
		K[sn++] = cv[i];
		for(int k = sn - 1; k > 0 && K[k] < K[k - 1]; k--) swap(K[k], K[k-1]);
		tot += convex_hull(K, st, sn) - 2 + cn - 1;
	}
	ex(tot, n + cn);
}
