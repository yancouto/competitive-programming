#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood;
cood eps = 1e-8;

cood pi = acos(-1.);

struct vec {
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	cood operator ^ (vec o)
	{ return x*o.y - y*o.x; }
	cood operator * (vec o)
	{ return x*o.x + y*o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	
	cood cross (vec a, vec b)
	{ return (b-a)^((*this)-a); }
	int ccw (vec a, vec b)
	{ cood o = cross(a,b); return (eps < o) - (o < -eps); }

	cood inner (vec a, vec b)
	{ return (a-(*this)) * (b-(*this)); }
	int dir (vec a, vec b)
	{ cood o = inner(a,b); return (eps < o) - (o < -eps); }

	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
	vec rot90 ()
	{ return vec(-y, x); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

struct lin {
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	lin parll (vec p)
	{ return lin(a, b, a*p.x + b*p.y); }

	lin perpn ()
	{ return lin(-b, a, c); }

	vec inter (lin o) {
		cood d = a*o.b - o.a*b;
		if (d < eps && -eps < d) assert(false);
		return vec((o.b*c - b*o.c) / d, (a*o.c - o.a*c) / d);
	}
};
void printa (vec a, vec b, vec c, vec d) {
	for (vec x : {a,b,c,d}) {
		if (x.x == 0 && x.y == 0)
			printf("0 0\n");
		else
			printf("%.20f %.20f\n", x.x, x.y);
	}
	exit(0);
}


void printa (lin a, lin b, lin c, lin d) {
	printa(a.inter(b), b.inter(c), c.inter(d), d.inter(a));
}

vec v[4];

double solve (double ang, bool resp = 0) {
	lin a(v[0], v[0] + vec(1,0).rotate(ang));
	lin c = a.parll(v[2]);
	lin b = a.perpn().parll(v[1]);
	lin d = a.perpn().parll(v[3]);
	
	vec cen = a.inter(b);
	vec m = a.inter(d);
	vec h = b.inter(c);

	if (resp)
		printa(cen, h, c.inter(d), m);

	return cen.sq(m) - cen.sq(h);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("four.in", "r", stdin);
	freopen("four.out", "w", stdout);
#endif

	for (int i = 0; i < 4; i++) {
		scanf("%lf %lf", &v[i].x, &v[i].y);
	}

	sort(v, v+4, [] (vec a, vec b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	});

	if (v[0].ccw(v[1],v[2]) == 0 && v[0].ccw(v[1],v[3]) == 0 && v[0].ccw(v[2],v[3]) == 0) { // 4 alin
		printa(v[3], v[0], v[0] + (v[3]-v[0]).rot90().rot90().rot90(), v[3] + (v[0]-v[3]).rot90());
	}

	sort(v+1, v+4, [] (vec a, vec b) {
		return a.ccw(v[0],b) == -1;
	});

	cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << endl;

	if (v[2].ccw(v[1],v[3]) == 1) { // degen
		printa(vec(0,0), vec(0,0), vec(0,0), vec(0,0));
	}

	// 3 alin

	// resto
	double lo = atan2(v[3].y,v[3].x);
	double hi = atan2(v[1].y,v[1].x) - pi;
	if (hi < lo) hi += 2.*pi;

	int ts = 60;

	while (ts--) {
		double md = (lo + hi)*.5;
		if (solve(md) > 0)
			lo = md;
		else
			hi = md;
	}

	if (abs(solve(lo)) < eps)
		solve(lo,1);
	else
		printa(vec(0,0), vec(0,0), vec(0,0), vec(0,0));
}

