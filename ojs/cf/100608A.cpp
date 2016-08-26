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
	bool T;
	long double ang;
	ptn() : T(false) {}
	ptn(num a, num b) : x(a), y(b), T(false) {}
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
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	void calc(ptn p) { ang = atan2(x - p.x, y - p.y); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<ll> pti;
typedef point<double> ptd;

const double pi = acos(-1);

temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }

const int N = 8123;

pti d[N], f[N], t[N], v[2*N];
int ts[N];

bool ok(pti t1, pti t2, pti f) {
	return cross(t1, t2, f) > 0;
}

ll sum[N], sum2[N];

#ifdef ONLINEJUDGE
#	define LLD "%I64d"
#else
#	define LLD "%lld"
#endif

int main() {
#ifdef ONLINE_JUDGE
	freopen("ambitious.in", "r", stdin);
	freopen("ambitious.out", "w", stdout);
#endif
	int i, j, k, D, F, T, sn, tn;
	while(scanf("%d", &D) != EOF && D) {
		for(i = 0; i < D; i++)
			scanf(LLD LLD, &d[i].x, &d[i].y);
		scanf("%d", &F);
		for(i = 0; i < F; i++)
			scanf(LLD LLD, &f[i].x, &f[i].y);
		scanf("%d", &T);
		for(i = 0; i < T; i++)
			scanf(LLD LLD, &t[i].x, &t[i].y), t[i].T = true;
		ll tot = 0;
		for(i = 0; i < F; i++) {
			for(j = 0; j < D; j++)
				v[j] = d[j];
			for(j = 0; j < T; j++)
				v[j + D] = t[j];
			for(j = 0; j < D + T; j++)
				v[j].calc(f[i]);
			sort(v, v + T + D, [](pti a, pti b) { return a.ang < b.ang; });
			for(j = T + D; j < 2*(T + D); j++)
				v[j] = v[j - (T + D)],
				v[j].ang = v[j - (T + D)].ang + pi * 2.;
			tn = 0;
			for(j = 0; j < 2*(T + D); j++)
				if(v[j].T)
					ts[tn++] = j;
			for(j = 1; j < 2*T; j++)
				sum[j] = sum[j - 1] + (ts[j] - ts[j - 1] - 1);
			int l = 0, r = -1;
			ll cur = 0;
			for(l = 0; l < T; l++) {
				if(r < l) cur = 0, r = l;
				while(r + 1 < 2*T && v[ts[r+1]].ang - v[ts[l]].ang < pi) {
					r++;
					cur += sum[r] - sum[l];
				}
				tot += cur;
				cur -= ll(ts[l + 1] - ts[l] - 1) * ll(r - l);
			}
		}
		printf(LLD"\n", tot);
	}
}
