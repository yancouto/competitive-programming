#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int S = 360000;
const int N = 100123;

struct ans {
	int d; int i, j;
	bool operator < (const ans & o) const { return d < o.d; }
};

int n;
int q;
set<int> s;
priority_queue<ans> bst;

typedef long double cood; cood eps = 1e-8; cood inf = 1./0.; // risky: XXX, untested: TODO
const cood pi = acos(-1.);
template<typename T> inline T sq(T x) { return x*x; }
struct vec {
	cood x, y;
	vec () : x(0), y(0) {} vec (cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y - o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y}; }
	inline vec operator * (cood o) { return {x * o, y * o}; }
	inline vec operator / (cood o) { return {x / o, y / o}; }
	inline cood operator ^ (vec o) { return x * o.y - y * o.x; }
	inline cood operator * (vec o) { return x * o.x + y * o.y; }
	inline cood cross (vec a, vec b) { return ((*this)-a) ^ ((*this)-b); } // |(this)a||(this)b|sen(angle)
	inline cood inner (vec a, vec b) { return ((*this)-a) * ((*this)-b); } // |(this)a||(this)b|cos(angle)
	inline cood angle (vec a, vec b) { return atan2(cross(a,b),inner(a,b)); } // ccw angle from (this)a to (this)b in range [-pi,pi]
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); } // this is to the (1 left, 0 over, -1 right) of ab
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); } // a(this) is to the (1 same, 0 none, -1 opposite) direction of ab
	inline cood sq (vec o = vec()) { return inner(o,o); }
	inline cood nr (vec o = vec()) { return sqrt(sq(o)); } //$
	inline vec operator ~ () { return (*this)/nr(); }
	inline vec proj (vec a, vec b) { return a + (b-a)*(a.inner((*this),b) / a.sq(b)); } // projects this onto line ab
	inline vec rotate (cood a) { return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); } // ccw by a radians
	inline vec rot90 () { return vec(-y,x); } // rotate(pi/2)$
	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; } // tips included
	cood dist2_lin (vec a, vec b) { return a.sq(b) <= eps ? sq(a) : cood(::sq(cross(a,b)))/a.sq(b); } // see cir.has_inter_lin
	cood dist2_seg (vec a, vec b) { return a.dir((*this),b) == (b.dir((*this),a)) ? dist2_lin(a,b) : min(sq(a),sq(b)); }
	inline bool operator == (const vec & o) const { return abs(x-o.x) <= eps && abs(y-o.y) <= eps; }
	inline bool operator < (const vec & o) const { return (abs(x-o.x)>eps)?(x < o.x):(y > o.y); } // lex compare (inc x, dec y)
	// full ccw angle strict compare beginning upwards (this+(0,1)) around (*this)
	// incresing distance on ties, this is the first
	bool compare (vec a, vec b) { 
		if ((*this < a) != (*this < b)) return *this < b;
		int o = ccw(a,b); return o?o>0:((a == *this && !(a == b)) || a.dir(*this,b) < 0);
	}
}; //$
struct cir { // circle
	vec c; cood r;
	cir () {} cir (vec v, cood d) : c(v), r(d) {}
	inline bool contains (vec w) { return c.sq(w) <= sq(r) + eps; } // border included
	inline bool border (vec w) { return abs(c.sq(w) - sq(r)) <= eps; }
	inline bool has_inter (cir o) { return c.sq(o.c) <= sq(r + o.r) + eps; } // borders included
	inline bool has_border_inter (cir o) { return has_inter(o) && c.sq(o.c) + eps >= sq(r - o.r); }
	inline bool has_inter_lin (vec a, vec b) { return a.sq(b) <= eps ? contains(a) : sq(c.cross(a,b)) <= sq(r)*a.sq(b) + eps; } // borders included XXX overflow
	inline bool has_inter_seg (vec a, vec b) { return has_inter_lin(a,b) && (contains(a) || contains(b) || a.dir(c,b)*b.dir(c,a) != -1); } // borders and tips included XXX overflow
	inline cood arc_area (vec a, vec b) { return c.angle(a,b)*r*r/2; } // smallest arc, ccw positive
	inline cood arc_len (vec a, vec b) { return c.angle(a,b)*r; } // smallest arc, ccw positive
	pair<vec,vec> tan (vec v) { // XXX low precision
		if (contains(v) && !border(v)) throw 0;
		cood d2 = c.sq(v); cood s = sqrt(d2 - r*r); s = (s==s)?s:0;
		cood al = atan2(r,s); vec t = (~(c-v));
		return pair<vec,vec>(v + t.rotate(al)*s, v + t.rotate(-al)*s);
	}
}; 

cir inn, out;

cood calcula (cood d) {
	vec a(out.r,0);
	vec b = a.rotate(d*2.*pi/cood(S));
	
	if (!inn.has_inter_lin(a,b)) return a.nr(b);
	else {
		pair<vec,vec> ps = inn.tan(a);
		pair<vec,vec> pt = inn.tan(b);
		cood res = 1./0.;
		for (vec s : {ps.first, ps.second}) {
			for (vec t : {pt.first, pt.second}) {
				res = min(res, a.nr(s) + abs(inn.arc_len(s,t)) + b.nr(t));
			}
		}
		return res;
	}
}

cood get () {
	while (true) {
		ans c = bst.top();
		if (s.count(c.i) && s.count(c.j)) 
			return calcula(c.d);
		else
			bst.pop();
	}
	assert(false);
}

void add (int x, int y) {
	int c = min(abs(x-y), S-abs(x-y));
	bst.push({ c, x, y });
}

void go (int x) {
	int y = (x+S/2)%S;
	auto it = s.lower_bound(y);
	if (it == s.end()) add(x,*s.begin());
	else add(x,*it);
	if (it == s.begin()) add(x,*prev(s.end()));
	else add(x,*prev(it));
}

int main () {
	scanf("%Lf %Lf", &out.r, &inn.r);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) { int a; scanf("%d", &a); s.insert(a); }
	for (int x : s) { go(x); }
	scanf("%d", &q);
	printf("%.20f\n", (double) get());
	while (q--) {
		int t, x;
		scanf("%d %d", &t, &x);
		if (t == 1) {
			s.insert(x);
			go(x);
		} else {
			s.erase(x);
			auto it = s.lower_bound(x);
			if (it == s.end()) go(*s.begin());
			else go(*it);
			if (it == s.begin()) go(*prev(s.end()));
			else go(*prev(it));
		}
		printf("%.20f\n", (double) get());
	}
}
