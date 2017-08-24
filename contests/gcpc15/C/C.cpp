#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

typedef long double cood;
cood eps = 1e-8;

const cood pi = acos(-1.);

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	cood nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (cood a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// divide the plane relative to anc
	// 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
	bool haLfplane (vec anc = vec(1,0)) {
		int l = sd(vec(), anc);
		if (l == 0)
			return (x < -eps);
		return (l == 1);
	}

	// ordering (ccw angle from anc, distance to origin)
	// is this < o?
	// PRECISION : ok with double if norm in [-1e4,1e3]
	bool compare (vec o, vec anc = vec(1,0)) {
		bool s[2] = {haLfplane(anc), o.haLfplane(anc)};
		if (s[0] != s[1])
			return s[0] < s[1];

		int l = sd(o, vec());
		if (l == 0)
			return sq() - o.sq() < -eps;
		return (l == -1);
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}

const int N = 203;

int n;
vec v[N];
cood alph;
cood arr, trig;

vec getpt (int i, cood s) {
	int a = i/2, b;
	if (i&1)
		b = (a + 1)%n;
	else
		b = (a + n - 1)%n;
	return v[b] + (v[a] - v[b])*((s-1)/s);
}

cood solve (cood s) {
	cood rs = 0;
	for (int i = 0; i < n; i++)
		rs += abs(v[i].ar(getpt(i*2,s), getpt(i*2+1,s)));
	return rs;
}

int main () {
	cin >> alph >> n;
	//scanf("%Lf %d", &alph, &n);

	for (int i = 0; i < n; i++)
		cin >> v[i].x >> v[i].y;
		//scanf("%Lf %Lf", &v[i].x, &v[i].y);

	for (int i = 2; i < n; i++)
		arr += abs(v[0].ar(v[i-1], v[i]));

	for (int i = 0; i < n; i++)
		trig += abs(v[i].ar(v[(i+n-1)%n], v[(i+1)%n]));

	printf("%.20f\n", (double) sqrt(trig/((1.-alph)*arr)));
}
