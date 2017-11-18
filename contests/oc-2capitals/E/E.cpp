#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

typedef double cood;
const eps = 1e-8;
const double pi = acos(-1.);

struct vec {
	cood x, y;
	vec () : x(0),y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	
	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a)*y, sin(a)*x + cos(a)*y); }
};

struct lin {
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a*s.x + b*s.y) {}

	lin parll (vec p)
	{ return lin(a,b,a*p.x + b*p.y); }
	lin perp ()
	{ return lin(-b,a,c); }

	vec inter (lin o) {
		cood d = a*o.b - o.a*b;
		return vec((o.b * c - b*o.c)/d, (a*o.c - o.a*c)/d);
	}
}

int where (vec p, lin a, lin b) {
	vec u = a.perp().parll(p).inter(a);
	vec v = b.perp().parll(p).inter(b);

	return p.dir(u,v);
}

const int N = 60;

int n;
vec v[N];
double alph;

struct answ {
	vec r, s, t, u;
	
	answ (lin a, lin b, lin c, lin d) {
		double d = 0;
		r = a.inter(b);
		t = a.inter(d);
	}
};

int main() {
	srand(time(NULL)); rand(); rand();
	scanf("%d", &n);
	alph = (double(rand()*2.*pi)/RAND_MAX);

	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &v[i].x, &v[i].y);
		v[i] = v[i].rotate(alph);
	}

	answ res;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (k == i || k == j) continue;

				lin a(v[i],v[j]);
				lin b = a.parll(v[k]);
				lin c = a.perp();
				lin d = c;
				bool ok = 0;
				
				for (int l = 0; l < n; l++) {
					if (where(v[l],a,b) == 0) {
						continue;
					} else {
						if (!ok) {
							c = d = c.parll(v[l]);
							ok = 1;
						} else if (where(v[l],c,d) == -1) {
							c = c.parll(v[l]);
						} else if (where(v[l],c,d) == 1) {
							d = d.parll(v[l]);
						}
					}
				}

				res = min(res, answ(a,b,c,d));
			}
		}
	}

	for (vec v : {res.r, res.s, res.t, res.u}) {
		v = v.rotate(-alph);
		printf("%.20f %.20f\n", v.x, v.y);
	}
}
