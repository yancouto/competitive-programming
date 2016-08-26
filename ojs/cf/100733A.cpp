#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
template<typename num> struct point {
	num x, y;
	point() {}
	point(num a, num b) : x(a), y(b) {}
	point operator + (point o) const { return point(x + o.x, y + o.y); }
	point operator - (point o) const { return point(x - o.x, y - o.y); }
	num operator * (point o) const { return x * o.x + y * o.y; }
	num operator ^ (point o) const { return x * o.y - y * o.x; }
	point operator * (num i) const { return point(x * i, y * i); }
	point operator / (num i) const { return point(x / i, y / i); }
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num distSqr(point o) const { return (*this - o) * (*this - o); }
	bool operator < (point o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<double> pointd;

pointd ps[40];
const double PI = 3.141592653589793238462;
int main() {
	int n, i, r[2];
	scanf("%d %d %d", &n, &r[0], &r[1]); n *= 2;
	for(i = 0; i < n; i++) {
		ps[i] = pointd(r[i&1], 0);
		ps[i] = ps[i].rotate(2. * i * PI / n);
	}
	double ar = 0;
	for(i = 1; i < n - 1; i++) {
		pointd p1 = ps[i+1] - ps[0], p2 = ps[i] - ps[0];
		ar += p1 ^ p2;
	}
	printf("%.10f\n", fabs(ar) / 2);
	return 0;
}
