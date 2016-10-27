// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

#include <cmath>
#include <bits/stdc++.h>
#define temp template<typename num>
#define ptn point<num>
using namespace std;
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
	num norm () const { return ( x*x + y*y ); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<int> pti;
typedef point<double> ptd;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
// o ponto c esta no segmento [a, b]?
temp inline bool between_seg(ptn a, ptn b, ptn c) { return cross(a, b, c) == 0 && ((b - c) * (a - c) <= 0); }
// sqr dist de c pro segmento [a, b]
temp double dist_seg_sqr(ptn a, ptn b, ptn c) {
	if((b - a) * (c - b) > 0) return b.dist_sqr(c);
	if((a - b) * (c - a) > 0) return a.dist_sqr(c);
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}
temp int sign(num x) { return (x > 0) - (x < 0); }
// [a, b] intersecta [c, d]?
temp bool inter_seg(ptn a, ptn b, ptn c, ptn d) {
	if(between_seg(a, b, c) || between_seg(a, b, d) || between_seg(c, d, a) || between_seg(c, d, b)) return true;
	if((sign(cross(a, b, c)) * sign(cross(a, b, d)) == -1) && (sign(cross(c, d, a)) * sign(cross(c, d, b)) == -1)) return true;
	return false;
}

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a*s.x + b*s.y) {}
	line pass(ptn p) { return line(a, b, a*p.x + b*p.y); }
	bool parallel(const line &o) const { return a * o.b - o.a * b == 0; }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(d == 0) return point<double>(0, 0); // fudeu
		return point<double>((o.b * c - b * o.c)/d, (a * o.c - o.a * c)/d);
	}
};
typedef line<int> lni;
typedef line<double> lnd;

const int N = 57;
const double eps = 1e-8;

ptd circ[N];
double rad[N];
double w, h;
ptd sid[4];
int n;
int ts;

bool isin (int i, ptd A, double f) {
	double r = f + rad[i];
	double d = A.dist_sqr(circ[i]);

	if (d - r*r < -eps) return 1;
	return 0;
}

bool isok (ptd A, double f) {
	if (f - A.y > eps) return 0;
	if (A.y - h + f > eps) return 0;
	if (f - A.x > eps) return 0;
	if (A.x - w + f > eps) return 0;

	for (int i = 0; i < n; i++)
		if (isin(i, A, f)) return 0;
	return 1;
}

ptd int_cir (int k, int i, int j, double f) {
	ptd A = circ[i];
	ptd B = circ[j];

	double ra = rad[i]+f;
	double rb = rad[j]+f;

	ptd D = B-A;
	double d = sqrt(D.norm());

	if (d - ra - rb > eps) return ptd(f, f);

	D = D / d;
	
	ptd OD = ptd(-D.y, D.x);
	
	double l = .5*((ra*ra - rb*rb)/d + d);
	ptd M = A + (B-A)*l;
	
	double h = sqrt(fabs(ra*ra - l*l));

	if (k)
		return M + OD*h;
	else
		return M - OD*h;
}

ptd ret_hor (int k, int i, double y, double f) {
	ptd A = circ[i];
	double r = rad[i] + f;
	double d = fabs(A.y - y);
	double h = sqrt(r*r - d*d);

	if (k)
		return ptd(A.x + h, y);
	else
		return ptd(A.x - h, y);
}

ptd ret_ver (int k, int i, double x, double f) {
	ptd A = circ[i];
	double r = rad[i] + f;
	double d = fabs(A.x - x);
	double h = sqrt(r*r - d*d);
	
	if (k)
		return ptd(x, A.y + h);
	else
		return ptd(x, A.y - h);
}


bool solve (double f) {
	// esq sup
	if (isok(ptd(f, f), f)) return 1;

	// bordas c/ circ
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 2; k++) {
			if (isok(ret_hor(k, i, f, f), f)) return 1;
			if (isok(ret_hor(k, i, h-f, f), f)) return 1;
			if (isok(ret_ver(k, i, f, f), f)) return 1;
			if (isok(ret_ver(k, i, w-f, f), f)) return 1;
		}
	}

	// circ c/ circ
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < 2; k++) {
				if (isok(int_cir(k, i, j, f), f)) return 1;
			}
		}
	}

	return 0;
}

int main () {
	scanf("%d", &ts);
	
	while (ts--) {
		scanf("%lf %lf", &w, &h);

		sid[0] = ptd(0, 0);
		sid[1] = ptd(w, 0);
		sid[2] = ptd(w, h);
		sid[3] = ptd(0, h);

		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &circ[i].x, &circ[i].y);
			scanf("%lf", &rad[i]);
		}

		double lo = 0;
		double hi = min(w, h);

		while (hi - lo > eps) {
			double mid = .5*(hi + lo);

			if (solve(mid))
				lo = mid;
			else
				hi = mid;
		}

		printf("%.20f\n", lo);
	}

}
