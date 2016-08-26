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

#define double long double
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
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<int> pti;
typedef point<double> ptd;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
const double pi2 = 2. * acos(-1);
const int N = 112345;
int a[N], A[N];
ptd ans[N], S[N];

double deg(double l, double r) {
	double h = ((double)sqrt((2. * r - l) * (2. * r + l))) / 2.;
	return 2. * atan2(l / 2., h);
}

int n;
bool ok2(double r) {
	double mx = deg(a[0], r);
	double ang = 0;
	for(int i = 1; i < n && ang <= mx + .1; i++) {
		double al = deg(a[i], r);
		ang += al;
	}
	return ang <= mx;
}
bool ok(double r) {
	double ang = 0;
	for(int i = 0; i < n && ang <= pi2 + .1; i++) {
		double al = deg(a[i], r);
		ang += al;
	}
	return ang <= pi2;
}

int main(int argn, char **args) {
	if(argn > 1) srand(atoi(args[1]));
	int i;
	clock_t c = clock();
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &A[i]);
		//A[i] = (rand() % 100000) + 1;
	}
	int j = max_element(A, A + n) - A;
	if(2 * A[j] >= accumulate(A, A + n, 0ll)) { puts("Impossible"); return 0; }
	for(i = 0; i < n; i++)
		a[i] = A[(i + j) % n];
	if(ok(a[0] / 2.)) {
		double l = a[0] / 2., r = 1e10;
		while((double)(clock() - c) / CLOCKS_PER_SEC < 4.7) {
			double m = (l + r) / 2.;
			if(ok2(m)) l = m;
			else r = m;
		}
		r = (l + r) / 2.;
		S[0] = ptd(-a[0] / 2., 0);
		S[1] = ptd(a[0] / 2., 0);
		ptd ori(r, 0.);
		double h = ((double)sqrt((2. * r - a[0]) * (2. * r + a[0]))) / 2.;
		double ang = atan2(h, a[0] / 2.);
		ori = ori.rotate(ang);
		for(i = 2; i < n; i++) {
			//double s = a[i-1] / (2. * r);
			//ang += 2. * acos(sqrt(1. - s * s));
			ori = ori.rotate(deg(a[i - 1], r));
			S[i] = ori - ptd(0, h);
		}
	} else {
		double l = a[0] / 2., r = 1e10;
		while((double)(clock() - c) / CLOCKS_PER_SEC < 4.7) {
			double m = (l + r) / 2;
			if(ok(m)) r = m;
			else l = m;
		}
		r = (l + r) / 2.;
		ptd ori(r, 0.);
		//double ang = 0;
		for(i = 0; i < n; i++) {
			S[i] = ori;
			ori = ori.rotate(deg(a[i], r));
			//ang += deg(a[i], r);
		}
	}
	for(i = 0; i < n; i++)
		ans[(i + j) % n] = S[i];
	ans[n] = ans[0];
	for(i = 0; i < n; i++) {
		assert(abs(ans[i].x) <= 2e9 + 1 && abs(ans[i].y) <= 2e9 + 1);
		//printf("%.10Lf\n", sqrt(ans[i].dist_sqr(ans[i + 1])));
		//printf("%.10Lf\n", abs(sqrt(ans[i].dist_sqr(ans[i + 1])) - A[i]));
		//assert(abs(sqrt(ans[i].dist_sqr(ans[i + 1])) - A[i]) <= 1e-4);
	}
	for(i = 0; i < n; i++) printf("%.10Lf %.10Lf\n", ans[i].x, ans[i].y);
}
