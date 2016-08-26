#include <cstdio>
#include <algorithm>
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
#include <cmath>
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
pointd ps[20], vs[20];
double v;
int p[20];

int main() {
	int i, n;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%lf", &v);
		for(i = 0; i < n; i++) {
			p[i] = i; double a;
			scanf("%lf %lf %lf %lf", &ps[i].x, &ps[i].y, &vs[i].x, &a);
			vs[i].y = 0; vs[i] = vs[i].rotate(a);
		}
		double t_min = 10000000;
		do {
			double t = 0, ret = 0;
			pointd pos(0, 0);
			for(i = 0; i < n; i++) {
				int j = p[i];
				double tl = t, tr = 2000000;
				while(tr - tl > 1e-5) {
					double tm = (tl + tr) / 2;
					if((pos.distSqr(ps[j] + vs[j] * tm) / (v*v) <= (tm - t) * (tm - t))) tr = tm;
					else tl = tm;
				}
				t = (tl + tr) / 2;
				pos = ps[j] + vs[j] * t;
				ret = max(ret, t + sqrt(pointd(0, 0).distSqr(pos) / (vs[j] * vs[j])));
			}
			t_min = min(t_min, ret);
		} while(next_permutation(p, p + n));
		printf("%d\n", (int)(t_min + 0.5));
	}
}
