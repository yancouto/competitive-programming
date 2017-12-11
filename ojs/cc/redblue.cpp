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


typedef ll cood;
cood eps = 0;
// tests for double were made with eps = 1e-8

double eps_d = 1e-8; // necessary even in integer geometry, should be eps otherwise

const double pi = acos(-1.);

inline ll sq (ll x)
{ return x*x; }
inline double sq (double x)
{ return x*x; }

struct vec { // vector
	// === BASIC ===
	cood x, y;
	bool red;
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

	// positive is (*this)b is clockwise from (*this)a
	double angle (vec a, vec b)
	{ return atan2((a-(*this))^(b-(*this)), (a-(*this))*(b-(*this))); }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(sq(o)); }

	cood cross (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int ccw (vec a, vec b) // which side is this from ab? (1 left, 0 over, -1 right)
	{ cood o = cross(a, b); return (eps < o) - (o < -eps); } 

	int dir (vec a, vec b) // direction of (this)a relative to (this)b (-1 opposite, 0 none, 1 same)
	{ cood o = ((*this) - a)*((*this) - b); return (eps < o) - (o < -eps); }

	cood inner (vec s, vec t) // (p-s)*(t-s) where p = this projected on st
	{ return ((*this) - s) * (t - s); }
	vec proj (vec s, vec t) // projection of this point over line st
	{ return s + (t - s)*(inner(s,t) / t.sq(s)); }

	vec rotate (double a) // rotate ccw by a (fails with ll)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }
	vec rot90 () // rotate pi/2 ccw
	{ return vec(-y, x); }

	// === ADVANCED ===
	// ordering that defines the compare method
	// used only there, change it accordingly
	// sorts increasing on y and, then increasing on x
	bool operator < (const vec & o) const {
		if (y != o.y)
			return y < o.y;
		return x < o.x;
	}

	// full ordering (ccw angle from this+(1,0), distance to this)
	// is a < b?
	// PRECISION : ok with double if norm in [-1e9,5e3]
	bool compare (vec a, vec b) {
		if (((*this) < a) != ((*this) < b))
			return (*this) < a;
		int o = ccw(a,b);
		if (o) return o > 0;
		return a.dir((*this),b) < 0;
	}

};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x << ", " << o.y << ')'; }

vec p[11234];

int main() {
	for_tests(tn, tt) {
		int i, j, n, m;
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			scanf("%lld %lld", &p[i].x, &p[i].y), p[i].red = true;
		for(i = 0; i < m; i++)
			scanf("%lld %lld", &p[i + n].x, &p[i + n].y), p[i + n].red = false;
		int best = INT_MAX;
		for(i = 0; i < n + m; i++) {
			vector<vec> v;
			for(j = 0; j < n + m; j++)
				if(i != j)
					v.pb(p[j]);
			sort(v.begin(), v.end(), [i](vec a, vec b) { return p[i].compare(a, b); });
			int r = -1;
			int cr = p[i].red, cb = !p[i].red;
			for(j = 0; j < v.size() && v[j].y >= p[i].y; j++) {
				while(r + 1 < v.size() && v[r + 1].ccw(p[i], v[j]) >= 0) {
					r++;
					cr += v[r].red;
					cb += !v[r].red;
				}
				best = min(best, (cr - p[i].red - v[j].red) + (m - cb));
				best = min(best, (cb - !p[i].red - !v[j].red) + (n - cr));
				cr -= v[j].red;
				cb -= !v[j].red;
			}
		}
		printf("%d\n", best);
	}
}
