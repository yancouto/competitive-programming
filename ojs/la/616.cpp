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
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
typedef point<ll> pti;
typedef point<double> ptd;
const int N = 209;
typedef long double ld;
pti v[N], p[N], o;
int pp[N], ls; ld val[N];
const ll inf = 10000000000000000ll;

ll memo2[N][N];
ll ar(int i, int j) {
	ll &r = memo2[i][j];
	if(r != -1) return r;
	int st[N], sn = 1;
	for(int k = i; k <= j; k++) {
		if(k < j && cross(o, v[k], v[k + 1]) > 0) return inf;
		while(sn > 2 && cross(v[k], v[st[sn-1]], v[st[sn-2]]) < 0)
			sn--;
		st[sn++] = k;
	}
	ll ans = 0;
	for(int k = 1; k < sn - 1; k++)
		ans += cross(o, v[st[k]], v[st[k + 1]]);
	return r = abs(ans);
}

ll memo[N][N/4];
ll solve(int i, int b) {
	if(i == ls) return b? inf : 0ll;
	if(b == 0) return inf;
	ll &r = memo[i][b];
	if(r != -1) return r;
	r = inf;
	for(int j = i + 1; j < ls; j++)
		r = min(r, ar(i, j) + solve(j + 1, b - 1));
	return r;
}

int qd(pti p) {
	if(p.x > 0 && p.y > 0) return 0;
	else if (p.x > 0) return 1;
	else if(p.y < 0) return 2;
	else return 3;
}

bool les(int i, int j) {
	pti a = p[i] - o, b = p[i] - o;
	int qa = qd(a), qb = qd(b);
	if(qa != qb) return qa < qb;
	return cross(o, p[i], p[j]) < 0;
}

int main() {
	int i, n, b;
	while(scanf("%d %d", &b, &n) != EOF && b) {
		n--;
		scanf("%lld %lld", &o.x, &o.y);
		for(i = 0; i < n; i++) {
			scanf("%lld %lld", &p[i].x, &p[i].y);
			val[i] = atan2(ld(p[i].y - o.y), ld(p[i].x - o.x));
			pp[i] = i;
		}
		//sort(pp, pp + n, [](int i, int j) { return val[i] < val[j]; });
		sort(pp, pp + n, les);
		for(i = 0; i < 2 * n; i++)
			v[i] = p[pp[i % n]];
		ll ans = LLONG_MAX;
		memset(memo2, -1, sizeof memo2);
		for(i = 0; i < n; i++) {
			memset(memo, -1, sizeof memo);
			ls = i + n;
			ans = min(ans, solve(i, b));
		}
		assert(ans != inf);
		printf("%.2f\n", ans / 2.);
	}
}
