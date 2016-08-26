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
	inline ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	inline ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	inline num operator * (ptn o) const { return x * o.x + y * o.y; }
	inline num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	inline num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
};
typedef point<ll> pti;
// sqr dist de c pro segmento [a, b]
temp inline bool dist_seg_ok1(ptn a, ptn b, ptn c, float mult=1.) {
	pti ba(b.x - a.x, b.y - a.y), ca(c.x - a.x, c.y - a.y), cb(c.x - b.x, c.y - b.y);
	if(ba * cb > 0) return (cb * cb) <= mult * mult;
	if(ba * ca < 0) return (ca * ca) <= mult * mult;
	ll d = ba ^ ca;
	if(mult != 1) return d * d <= (ba * ba) * mult * mult;
	else return d * d < (ba * ba);
}

temp inline bool dist_seg_ok2(ptn a, ptn b, ptn c, float mult=1.) {
	pti ba(b.x - a.x, b.y - a.y), ca(c.x - a.x, c.y - a.y);
	ll d = ba ^ ca;
	if(mult != 1) return d * d <= (ba * ba) * mult * mult;
	else return d * d < (ba * ba);
}

float r[506][506];
pti a, b;

int main() {
	int x, y, n, i, q;
	while(scanf("%d", &n) != EOF) {
		for(x = 1; x <= 500; x++)
			for(y = 1; y <= 500; y++)
				r[x][y] = 0.;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			scanf("%f", &r[x][y]);
		}
		scanf("%d", &q);
		while(q--) {
			scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);
			if(a.x > b.x) swap(a, b);
			y = a.y; x = a.x;
			int tot = 0;
			int u = y, d = y;
			while(u <= 500 && dist_seg_ok1(a, b, pti(x, u + 1))) u++;
			while(d >= 0 && dist_seg_ok1(a, b, pti(x, d - 1))) d--;
			y = d;
			while(d <= u) tot += (r[x][d] != 0 && dist_seg_ok1(a, b, pti(x, d), r[x][d])), d++;
			if(a.x != b.x) {
				for(x = a.x + 1; x < b.x; x++) {
					while(y <= 500 && !dist_seg_ok2(a, b, pti(x, y))) y++;
					u = y, d = y;
					while(u <= 500 && dist_seg_ok2(a, b, pti(x, u + 1))) u++;
					while(d >= 0 && dist_seg_ok2(a, b, pti(x, d - 1))) d--;
					y = d;
					while(d <= u) tot += (r[x][d] != 0 && dist_seg_ok2(a, b, pti(x, d), r[x][d])), d++;
				}
				y = b.y;
				u = y, d = y;
				while(u <= 500 && dist_seg_ok1(a, b, pti(x, u + 1))) u++;
				while(d >= 0 && dist_seg_ok1(a, b, pti(x, d - 1))) d--;
				while(d <= u) tot += (r[x][d] != 0 && dist_seg_ok1(a, b, pti(x, d), r[x][d])), d++;
			}
			printf("%d\n", tot);
		}
	}
}
