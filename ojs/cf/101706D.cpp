#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// XXX marks risky behaviour and TODO marks untested functions
typedef double cood; cood eps = 1e-8; cood inf = 1./0.;
const double pi = acos(-1.);
inline ll sq (ll x) { return x*x; }
inline double sq (double x) { return x*x; }
struct vec { // vector
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return vec(x - o.x, y - o.y); }
	inline vec operator + (vec o) { return vec(x + o.x, y + o.y); }
	inline vec operator * (cood o) { return vec(x * o, y * o); }
	inline vec operator / (cood o) { return vec(x / o, y / o); }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a|cos(angle)
	inline double angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline double nr (vec o = vec()) { return sqrt(sq(o)); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); } // projects this onto line ab
	inline vec rotate (double a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)

	inline bool operator == (const vec & o) const { return abs(x-o.x) <= eps && abs(y-o.y) <= eps; }
	inline bool operator <= (const vec & o) const { throw 1; return (x != o.x)?(x < o.x):(y >= o.y); } // lex compare (inc x, dec y)
	inline bool operator < (const vec & o) const { return (x != o.x)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle strict compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties, this is the first
	bool compare (vec a, vec b) { 
		if (((*this) < a) != ((*this) < b)) return (*this) < b;
		int o = ccw(a,b); if (o) return o > 0;
		return (a == (*this) && !(a == b)) || a.dir((*this),b) < 0;
	}

	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	double dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : double(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	double dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
};
struct lin { // line
	cood a, b, c; // a*x + b*y = c
	lin () {} lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}
	inline lin parll (vec p) { return lin{a, b, a*p.x + b * p.y}; }
	inline lin perp () { return lin{-b, a, c}; }
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (-eps <= d && d <= eps) throw 1; // parallel
		return vec((o.b * c - b * o.c) / d, (a * o.c - o.a * c) / d);
	}
	bool contains (vec v) { return abs(a*v.x + b*v.y - c) <= eps; }
	vec at_x (cood x) { return vec(x,(c-a*x)/b); }
	vec at_y (cood y) { return vec((c-b*y)/a,y); }
};

int main() {
	vec a, b, c;
	scanf("%lf %lf", &a.x, &a.y);
	scanf("%lf %lf", &b.x, &b.y);
	scanf("%lf %lf", &c.x, &c.y);
	vec d1 = (b - a) / ((b - a).nr()) + (c - a) / ((c - a).nr());
	vec d2 = (a - b) / ((b - a).nr()) + (c - b) / ((c - b).nr());
	vec C = lin(a, a + d1).inter(lin(b, b + d2));
	printf("%.10f %.10f %.10f\n", C.x, C.y, sqrt(C.dist2_seg(a, b)));
}
