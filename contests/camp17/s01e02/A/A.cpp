#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 23;
const double pi = acos(-1.);

ll l[N];
ll r;
int n;

template<typename cood> struct vect {
	cood x,y;

	vect<cood> () {}
	vect<cood> (cood a, cood b) : x(a), y(b) {}
	vect<cood> (cood a) : x(a), y(a) {}

	inline vect<double> operator / (double a) const
	{ return vect<double>(double(x)/a, double(y)/a); }
	inline vect<double> operator * (double a) const
	{ return vect<double>(double(x)*a, double(y)*a); }
	inline vect<double> operator + (const vect<double> & ot) const
	{ return vect<double>(x + ot.x, y + ot.y); }
	inline vect<double> operator - (const vect<double> & ot) const
	{ return vect<double>(x - ot.x, y - ot.y); }

	inline cood operator * (const vect<cood> & ot) const
	{ return x * ot.x + y * ot.y; }

	inline vect<double> rotate(double ang) const
	{ return vect<double>(cos(ang) * x - sin(ang) * y, sin(ang) * x + cos(ang) * y); }
	inline cood sq (const vect<cood> & ot = 0) const
	{ return ((*this)-ot)*((*this)-ot); }
	inline cood norm (const vect<cood> & ot = 0) const
	{ return sqrt(sq(ot)); }
};

const double eps = 1e-8;

int main () {
	scanf("%d", &n);

	double r = 0.;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &l[i]);
		r += l[i];
	}

	vect<double> v;
	scanf("%lf %lf", &v.x, &v.y);
	vect<double> o(0,0);
	vect<double> d = (o - (v / (v.norm())));

	if (v.x == 0 && v.y == 0)
		d = vect<double>(1, 0);

	bool ok = 0;
	for (int i = 0; i < n; i++) {
		if (!ok) {
			vect<double> nx = (o + (d*l[i]));
			r -= l[i];
			if (nx.norm(v) < r) {
				o = nx;
			} else {
				double lo = 0.;
				double hi = pi;
				
				int mil = 1000;
				while (mil--) {
					double an = .5*(hi + lo);
					
					vect<double> cd = (o + (d.rotate(an)*l[i]));
					if (cd.norm(v) < r) {
						hi = an;
					} else {
						lo = an;
					}
				}

				o = (o + (d.rotate(lo)*l[i]));

				d = (v - o);
				d = (d / (d.norm()));
				ok = 1;
			}
		} else {
			o = (o + (d*l[i]));
		}
		printf("%.20f %.20f\n", o.x, o.y);
	}

}
