// WRONG
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
	num norm() const { return sqrt(dist_sqr(ptn(0, 0))); }
	ptn normalized() const { return *this / norm(); }
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<double> ptd;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }


// sqr dist de c pro segmento [a, b]
temp double dist_seg_sqr(ptn a, ptn b, ptn c) {
	if((b - a) * (c - b) > 0) return b.dist_sqr(c);
	if((a - b) * (c - a) > 0) return a.dist_sqr(c);
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}

const double eps = 1e-9;

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a*s.x + b*s.y) {}
	line pass(ptn p) { return line(a, b, a*p.x + b*p.y); }
	bool parallel(const line &o) const { return a * o.b - o.a * b == 0; }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(abs(d) <= eps) return point<double>(1e9, 1e9); // fudeu
		return point<double>((o.b * c - b * o.c)/d, (a * o.c - o.a * c)/d);
	}
};
typedef line<double> lnd;

const int N = 51234;

ptd p[N], v[N], np[N], d[N];
lnd l[N];

double mn_dist(ptd a, int n) {
	double mn = 1/0.;
	for(int i = 0; i < n; i++)
		mn = min(mn, dist_seg_sqr(p[i], p[i + 1], a));
	return mn;
}

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
	printf("y = %.10f vs\ny = %.10f\n", 3. - 2. * sqrt(2), sqrt(2) - 1.);
	printf("%.10f\n", sqrt(mn_dist(ptd(1, 3. - 2. * sqrt(2)), n)));
	printf("%.10f\n", sqrt(mn_dist(ptd(1, sqrt(2) - 1.), n)));
	if(cross(p[0], p[1], p[2]) < 0) reverse(p, p + n);
	p[n] = p[0];
	p[n + 1] = p[1];
	for(i = 0; i < n; i++)
		assert(cross(p[i], p[i + 1], p[i + 2]) > 0);
	for(i = 0; i < n; i++) {
		v[i] = p[i + 1] - p[i];
		v[i] = ptd(v[i].y, -v[i].x).normalized();
		//if(cross(p[i], p[i + 1], v[i]) < 0) v[i] = ptd(0, 0) - v[i];
	}
	v[n] = v[0];
	for(i = 1; i <= n; i++)
		d[i] = (p[i + 1] - p[i]).normalized() + (p[i - 1] - p[i]).normalized();
	d[0] = d[n];
	for(i = 1; i < n; i++)
		assert((p[i] - p[i - 1]) * d[i - 1] > 0);
	//double mn = 1/0.;
	//for(i = 0; i < n; i++) {
	//	double l = 0, r = 1e8;
	//	int j = 0;
	//	while(++j < 50) {
	//		double m = (l + r) / 2.;
	//		np[i] = p[i] + d[i] * m;
	//		np[i + 1] = p[i + 1] + d[i + 1] * m;
	//		if((np[i + 1] - np[i]) * d[i] < 0) r = m;
	//		else l = m;
	//	}
	//	printf("ans %d = %.5f\n", i, (l + r) / 2.);
	//	mn = min(mn, (l + r) / 2.);
	//}
	//printf("%.10f\n", mn);
	//for(i = 0; i <= n; i++)
	//	np[i] = p[i] + d[i] * mn;
	//for(i = 0; i < n - 1; i++)
	//	assert(abs(cross(np[i], np[i + 1], np[i + 2])) <= 1e-5);
	//ptd a = *min_element(np, np + n), b = *max_element(np, np + n);
	//for(i = 0; i < 40; i++) {
	//	ptd m1 = (a*2. + b) / 3.;
	//	ptd m2 = (a + b*2.) / 3.;
	//	double r1 = mn_dist(m1, n), r2 = mn_dist(m2, n);
	//	if(r1 < r2) a = m1;
	//	else b = m2;
	//}
	double mn = 1/0.;
	for(i = 1; i < n; i++) {
		ptd P = p[0] - p[i], D = d[i] - d[0]; 
		mn = min(mn, P.x / D.x);
		mn = min(mn, P.y / D.y);
	}
	printf("%.10f\n", mn);
	//printf("%.10f\n", mn_dist(best, n));
}
