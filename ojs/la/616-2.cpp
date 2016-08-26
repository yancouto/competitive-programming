#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
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
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num distSqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) {
	return (c - a) ^ (b - a);
}
typedef point<ll> pti;
typedef point<double> ptd;
const int N = 212;
const ll inf = 1e16;

pti p[N], v[N], o;
int pp[N]; double val[N];

ll memo2[N][N];
ll ar(int i, int j) {
	ll &r = memo2[i][j];
	if(r != -1) return r;
	int n = j - i + 2;
	p[0] = o;
	for(int k = i; k <= j; k++)
		p[k - i + 1] = v[k];
	sort(p, p + n);
	pti st[N]; int sn = 0;
	for(int i = 0; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], p[i]) < 0)
			sn--;
		st[sn++] = p[i];
	}
	int k = sn;
	for(int i = n - 2; i >= 0; i--) {
		while(sn > k && cross(st[sn - 2], st[sn - 1], p[i]) < 0)
			sn--;
		st[sn++] = p[i];
	}
	sn--;
	r = 0;
	for(i = 1; i < sn - 1; i++)
		r += cross(st[0], st[i], st[i + 1]);
	return r = abs(r);
}

int ls;
ll memo[N][N/4];
ll solve(int i, int b) {
	if(i == ls) return b? inf : 0;
	if(b == 0) return inf;
	ll &r = memo[i][b];
	if(r != -1) return r;
	r = inf;
	for(int j = i + 1; j < ls; j++)
		r = min(r, solve(j + 1, b - 1) + ar(i, j));
	return r;
}

int main() {
	int i, n, b;
	while(scanf("%d %d", &b, &n) != EOF && b) {
		n--;
		scanf("%lld %lld", &o.x, &o.y);
		for(i = 0; i < n; i++) {
			scanf("%lld %lld", &p[i].x, &p[i].y);
			pti k = p[i] - o;
			val[i] = atan2(k.y, k.x);
			pp[i] = i;
		}
		sort(pp, pp + n, [](int i, int j) { return val[i] < val[j]; });
		for(i = 0; i < 2*n; i++)
			v[i] = p[pp[i%n]];
		memset(memo2, -1, sizeof memo2);
		ll ans = inf;
		for(i = 0; i < n; i++) {
			memset(memo, -1, sizeof memo);
			ls = i + n;
			ans = min(ans, solve(i, b));
		}
		if(ans & 1) printf("%lld.50\n", ans / 2ll);
		else printf("%lld.00\n", ans / 2ll);
	}
}
